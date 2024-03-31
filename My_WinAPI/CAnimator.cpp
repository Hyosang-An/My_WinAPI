#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"
#include "CPathMgr.h"

CAnimator::CAnimator() :
    m_CurAnimation(nullptr),
    m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
    Safe_Del_Map(m_mapAnimation);
}

void CAnimator::finaltick()
{
    if (m_CurAnimation != nullptr)
    {
        if (m_CurAnimation->IsFinished() && m_bRepeat)
        {
            m_CurAnimation->Reset();
        }

        m_CurAnimation->finaltick();
    }
}

void CAnimator::render()
{
    if (m_CurAnimation != nullptr)
        m_CurAnimation->render();
}

CAnimation* CAnimator::CreateAnimation(const wstring& _AnimName, CTexture* _Atlas, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS)
{
    // ������ �̸��� Animation�� �̹� Animator�� �ִ� ���
    CAnimation* pAnim = FindAnimation(_AnimName);
    assert(pAnim == nullptr);

    // Animation ��ü ����
    pAnim = new CAnimation;
    pAnim->Create(_Atlas, _StartPos, _SliceSize, _FrameCount, _FPS);
    pAnim->SetName(_AnimName);
    pAnim->m_Animator = this;
    
    m_mapAnimation.insert(make_pair(_AnimName, pAnim));

    return pAnim;
}

CAnimation* CAnimator::FindAnimation(const wstring& _AnimName)
{
    const auto& iter = m_mapAnimation.find(_AnimName);
    if (iter == m_mapAnimation.end())
        return nullptr;

    return iter->second;
}

void CAnimator::LoadAnimation(wstring _strRelativeFilePath)
{
    // _strRelativeFilePath�� �� �տ� "\\"�� ������, "."�� �տ� �߰��Ͽ� ��� ��η� ����ϴ�.
    if (!_strRelativeFilePath.empty() && _strRelativeFilePath[0] == L'\\') {
        _strRelativeFilePath = L"." + _strRelativeFilePath;
    }

    CAnimation* pAnim = new CAnimation;
    if FAILED(pAnim->Load(_strRelativeFilePath))
    {
        delete pAnim;
        LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� �ε� ����");
        return;
    }

    if (FindAnimation(pAnim->GetName()) != nullptr)
    {
        wstring str = L"�ߺ��� �ִϸ��̼� �̸� : " + pAnim->GetName();
        LOG(LOG_TYPE::DBG_ERROR, str.c_str());
        delete pAnim;
        return;
    }

    pAnim->m_Animator = this;
    m_mapAnimation.insert(make_pair(pAnim->GetName(), pAnim));
}

void CAnimator::Play(const wstring& _AnimName, bool _Repeat, bool _RepeatReverse)
{
    // bool _RepeatReverse �� ����Ʈ �Ķ���� false

    auto anim = FindAnimation(_AnimName);

    if (anim == nullptr)
    {
        LOG(LOG_TYPE::DBG_ERROR, L"Play�� �ִϸ��̼��� ã�� �� ����");
        return;
    }
    
    // �ִϸ��̼� �պ� ��� ���� ����
    if (_RepeatReverse)
        anim->m_bRepeatReverse = true;

    // ���� ������� �ִϸ��̼��̸� �׳� ����
    if (anim == m_CurAnimation)
        return;

    m_CurAnimation = anim;

    m_CurAnimation->Reset();
    m_bRepeat = _Repeat;
}

void CAnimator::PlayFromFrame(const wstring& _AnimName, bool _Repeat, int _frameIdx)
{
    auto anim = FindAnimation(_AnimName);

    if (anim == nullptr)
    {
        LOG(LOG_TYPE::DBG_ERROR, L"Play�� �ִϸ��̼��� ã�� �� ����");
        return;
    }

    // ���� ������� �ִϸ��̼��̸� �׳� ����
    if (anim == m_CurAnimation)
        return;

    m_CurAnimation = anim;

    //m_CurAnimation->Reset();

    anim->m_frameElapsedTime = 0;
    anim->m_CurFrameIdx = _frameIdx;
    anim->m_bFinished = false;
    anim->m_bPlayingForward = true;

    m_bRepeat = _Repeat;
}



// ====================================================================================================================================


#include <filesystem>
#include <fstream>
#include "libs/json.hpp"
#include <iostream>

namespace fs = std::filesystem;
using json = nlohmann::json;

void CAnimator::CreateAnimationByJSON(std::wstring strRelativeJsonFilePath, int _FPS)
{
    // relativeFolderPath�� �� �տ� "\\"�� ������, "."�� �տ� �߰��Ͽ� ��� ��η� ����ϴ�.
    if (!strRelativeJsonFilePath.empty() && strRelativeJsonFilePath[0] == L'\\') {
        strRelativeJsonFilePath = L"." + strRelativeJsonFilePath;
    }

    // ���� ��� ����
    fs::path contents_path = CPathMgr::GetInstance().GetContentsPath();
    fs::path JsonFilePath = contents_path / strRelativeJsonFilePath;

    // JSON ���� ����
    std::ifstream jsonFile(JsonFilePath);
    if (!jsonFile.is_open())
    {
        std::wstring message = L"Failed to open JSON file: " + JsonFilePath.wstring();
        MessageBox(NULL, message.c_str(), L"Error", MB_ICONERROR | MB_OK);
        return;
    }

    json j;
    jsonFile >> j;

    // ��Ʋ�� �ؽ��� �ε�
    // JSON ���Ͽ��� �ؽ��� ���� �̸��� �о�ɴϴ�.
    //auto tmpAtlasTextureName = j["meta"]["image"].get<std::string>();
    //std::wstring atlasTextureName(tmpAtlasTextureName.begin(), tmpAtlasTextureName.end());

    // ��Ʋ�� �ؽ��ĸ� �ҷ����� ���ο� ����� ����մϴ�.
    // Json���� ��ο��� .json�� �����ϰ� .png �߰�.
    fs::path RelativeJsonFilePath = strRelativeJsonFilePath;
    wstring strRelativeAtlasFilePath = (RelativeJsonFilePath.parent_path() / RelativeJsonFilePath.stem()).wstring() + L".png";

    wstring strAtlasTextureName = RelativeJsonFilePath.stem().wstring() + L"_Atlas";
    CTexture* pAtlas = CAssetMgr::GetInstance().LoadTexture(strAtlasTextureName, strRelativeAtlasFilePath);

    if (pAtlas == nullptr)
    {
        std::wstring message = L"Failed to load atlas texture: " + strAtlasTextureName;
        MessageBox(NULL, message.c_str(), L"Error", MB_ICONERROR | MB_OK);
        return;
    }

    // CAnimation ��ü ����
    CAnimation* pAnim = new CAnimation();
    pAnim->SetAtlasTexture(pAtlas); // ��Ʋ�� �ؽ��� ����

    // JSON���� ��������Ʈ ���� �ε� �� ó��
    float frameDuration = 1.0f / static_cast<float>(_FPS);
    for (const auto& sprite : j["frames"])
    {
        const auto& filename = sprite["filename"].get<std::string>();
        const auto& frame = sprite["frame"];

        Vec2 startPos(frame["x"], frame["y"]);
        Vec2 sliceSize(frame["w"], frame["h"]);

        // ���� �ִϸ��̼� ������ ���� �� �ʱ�ȭ
        pAnim->CreateAnimationFrame(startPos, sliceSize, frameDuration);
    }

    // �ִϸ��̼� �̸� ���� �� Animator�� �ִϸ��̼� �߰�
    pAnim->SetName(RelativeJsonFilePath.stem().wstring()); // json �� png ���� �̸��� �ִϸ��̼� �̸����� ���
    pAnim->m_Animator = this;
    m_mapAnimation.insert(std::make_pair(pAnim->GetName(), pAnim));



    // �ش� ������ .anim ������ ���ٸ� ���� (����� ����)
    wstring strRelativeFolderPath = RelativeJsonFilePath.parent_path().wstring();
    wstring strRelativeAnimPath = strRelativeFolderPath + L"\\" + pAnim->GetName() + L".anim";
    fs::path AnimPath = CPathMgr::GetInstance().GetContentsPath();
    AnimPath /= strRelativeAnimPath;

    std::wifstream inFile(AnimPath);
    if (!inFile.is_open())
        pAnim->Save(RelativeJsonFilePath.parent_path().wstring());
}