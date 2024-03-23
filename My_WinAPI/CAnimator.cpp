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

//CAnimation* CAnimator::CreateAnimation(const wstring& _AnimName, wstring _strRelativeFolderPath, int _FPS)
//{
//    // ������ �̸��� Animation�� �̹� Animator�� �ִ� ���
//    CAnimation* pAnim = FindAnimation(_AnimName);
//    assert(pAnim == nullptr);
//
//    // Animation ��ü ����
//    pAnim = new CAnimation;
//    pAnim->Create(_strRelativeFolderPath, _FPS);
//    pAnim->SetName(_AnimName);
//    pAnim->m_Animator = this;
//
//    m_mapAnimation.insert(make_pair(_AnimName, pAnim));
//
//    return pAnim;
//}



CAnimation* CAnimator::FindAnimation(const wstring& _AnimName)
{
    const auto& iter = m_mapAnimation.find(_AnimName);
    if (iter == m_mapAnimation.end())
        return nullptr;

    return iter->second;
}

void CAnimator::LoadAnimation(wstring _strRelativeFilePath)
{
    // _strRelativeFilePath�� �� �տ� "\"�� ������ �߰�
    if (!_strRelativeFilePath.empty() && _strRelativeFilePath[0] != L'\\')
    {
        _strRelativeFilePath = L"\\" + _strRelativeFilePath;
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
        delete pAnim;
        LOG(LOG_TYPE::DBG_ERROR, L"�ߺ��� �ִϸ��̼� �̸�");
        return;
    }

    pAnim->m_Animator = this;
    m_mapAnimation.insert(make_pair(pAnim->GetName(), pAnim));
}

void CAnimator::LoadAnimation2(wstring _strRelativeFilePath)
{
    // _strRelativeFilePath�� �� �տ� "\\"�� ������, "."�� �տ� �߰��Ͽ� ��� ��η� ����ϴ�.
    if (!_strRelativeFilePath.empty() && _strRelativeFilePath[0] == L'\\') {
        _strRelativeFilePath = L"." + _strRelativeFilePath;
    }

    CAnimation* pAnim = new CAnimation;
    if FAILED(pAnim->Load2(_strRelativeFilePath))
    {
        delete pAnim;
        LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� �ε� ����");
        return;
    }

    if (FindAnimation(pAnim->GetName()) != nullptr)
    {
        delete pAnim;
        LOG(LOG_TYPE::DBG_ERROR, L"�ߺ��� �ִϸ��̼� �̸�");
        return;
    }

    pAnim->m_Animator = this;
    m_mapAnimation.insert(make_pair(pAnim->GetName(), pAnim));
}

void CAnimator::Play(const wstring& _AnimName, bool _Repeat)
{
    auto foundAnim = FindAnimation(_AnimName);

    if (foundAnim == nullptr)
    {
        LOG(LOG_TYPE::DBG_ERROR, L"Play�� �ִϸ��̼��� ã�� �� ����");
        return;
    }

    if (foundAnim == m_CurAnimation)
        return;

    m_CurAnimation = foundAnim;

    m_CurAnimation->Reset();
    m_bRepeat = _Repeat;
}



// ====================================================================================================================================


#include <filesystem>
#include <fstream>
#include "libs/json.hpp"
#include <iostream>


namespace fs = std::filesystem;
using json = nlohmann::json;

//void CAnimator::LoadAnimationFromJSON(const std::wstring& relativeFolderPath, int _FPS)
//{
//    // ���� ��� ����
//    fs::path folderPath = fs::current_path() / relativeFolderPath;
//    fs::path folderName = folderPath.filename();
//    fs::path jsonFilePath = folderPath / (folderName.wstring() + L".json");
//
//    // JSON ���� ����
//    std::ifstream jsonFile(jsonFilePath);
//    if (!jsonFile.is_open())
//    {
//        // ���� �޽����� MessageBox�� ǥ��
//        std::wstring message = L"Failed to open JSON file: " + jsonFilePath.wstring();
//        MessageBox(NULL, message.c_str(), L"Error", MB_ICONERROR | MB_OK);
//        return;
//    }
//
//    json j;
//    jsonFile >> j;
//
//    // ��Ʋ�� �ؽ��� �ε�
//    fs::path atlasPath = folderPath / j["meta"]["image"].get<std::string>();
//    CTexture* atlasTexture = new CTexture();
//    if (FAILED(atlasTexture->Load(atlasPath.wstring())))
//    {
//        // ���� �޽����� MessageBox�� ǥ��
//        std::wstring message = L"Failed to load atlas texture: " + atlasPath.wstring();
//        MessageBox(NULL, message.c_str(), L"Error", MB_ICONERROR | MB_OK);
//        delete atlasTexture;
//        return;
//    }
//
//    // JSON���� ��������Ʈ ���� �ε� �� ó��
//    for (const auto& sprite : j["frames"])
//    {
//        const auto& filename = sprite["filename"].get<std::string>();
//        const auto& frame = sprite["frame"];
//
//        Vec2 startPos(frame["x"], frame["y"]);
//        Vec2 sliceSize(frame["w"], frame["h"]);
//        // ���⼭ FPS�� JSON�� ���ԵǾ� ���� �����Ƿ�, ����Ʈ ���� ����ϰų� �ٸ� ������� �����ؾ� �մϴ�.
//        int fps = _FPS;
//        float frameDuration = 1.f / float(fps);
//        // CAnimation ��ü ���� �� �ʱ�ȭ
//        CAnimation* pAnim = new CAnimation();
//        // ������ ī��Ʈ�� 1�� ����, ���� ���ӿ����� ������ ������ �����ؾ� �� �� ����
//        pAnim->CreateAnimationFrame(startPos, sliceSize, frameDuration);
//        pAnim->SetName(std::wstring(filename.begin(), filename.end())); // std::string�� std::wstring���� ��ȯ
//        pAnim->m_Animator = this;
//
//        // ������ �ִϸ��̼��� Animator�� �߰�
//        m_mapAnimation.insert(std::make_pair(pAnim->GetName(), pAnim));
//    }
//}

void CAnimator::CreateAnimationFromJSON(const std::wstring& relativeFolderPath, int _FPS)
{
    // ���� ��� ����
    fs::path contents_path = CPathMgr::GetInstance().GetContentsPath();
    fs::path folderPath = contents_path / relativeFolderPath;
    fs::path folderName = folderPath.filename();
    fs::path jsonFilePath = folderPath / (folderName.wstring() + L".json");

    // JSON ���� ����
    std::ifstream jsonFile(jsonFilePath);
    if (!jsonFile.is_open())
    {
        std::wstring message = L"Failed to open JSON file: " + jsonFilePath.wstring();
        MessageBox(NULL, message.c_str(), L"Error", MB_ICONERROR | MB_OK);
        return;
    }

    json j;
    jsonFile >> j;

    // ��Ʋ�� �ؽ��� �ε�
    // JSON ���Ͽ��� �ؽ��� ���� �̸��� �о�ɴϴ�.
    auto tmpAtlasTextureName = j["meta"]["image"].get<std::string>();
    std::wstring atlasTextureName(tmpAtlasTextureName.begin(), tmpAtlasTextureName.end());

    // ��Ʋ�� �ؽ��ĸ� �ҷ����� ���ο� ����� ����մϴ�.
    wstring strAtlasTextureName = folderName.wstring() + L"_Atlas";    
    wstring strRelativePngPath = relativeFolderPath + L"\\" + folderName.wstring() + L".png";
    CTexture* pAtlas = CAssetMgr::GetInstance().LoadTexture(strAtlasTextureName, strRelativePngPath);

    if (pAtlas == nullptr)
    {
        std::wstring message = L"Failed to load atlas texture: " + atlasTextureName;
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
    pAnim->SetName(folderName.wstring()); // ���� �̸��� �ִϸ��̼� �̸����� ���
    pAnim->m_Animator = this;
    m_mapAnimation.insert(std::make_pair(pAnim->GetName(), pAnim));
}