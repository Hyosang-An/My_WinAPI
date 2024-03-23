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
    // 동일한 이름의 Animation이 이미 Animator에 있는 경우
    CAnimation* pAnim = FindAnimation(_AnimName);
    assert(pAnim == nullptr);

    // Animation 객체 생성
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
    // _strRelativeFilePath의 맨 앞에 "\\"가 있으면, "."을 앞에 추가하여 상대 경로로 만듭니다.
    if (!_strRelativeFilePath.empty() && _strRelativeFilePath[0] == L'\\') {
        _strRelativeFilePath = L"." + _strRelativeFilePath;
    }

    CAnimation* pAnim = new CAnimation;
    if FAILED(pAnim->Load(_strRelativeFilePath))
    {
        delete pAnim;
        LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 로드 실패");
        return;
    }

    if (FindAnimation(pAnim->GetName()) != nullptr)
    {
        delete pAnim;
        LOG(LOG_TYPE::DBG_ERROR, L"중복된 애니메이션 이름");
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
        LOG(LOG_TYPE::DBG_ERROR, L"Play할 애니메이션을 찾을 수 없음");
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

void CAnimator::CreateAnimationFromJSON(std::wstring relativeFolderPath, int _FPS)
{
    // relativeFolderPath의 맨 앞에 "\\"가 있으면, "."을 앞에 추가하여 상대 경로로 만듭니다.
    if (!relativeFolderPath.empty() && relativeFolderPath[0] == L'\\') {
        relativeFolderPath = L"." + relativeFolderPath;
    }

    // 파일 경로 구성
    fs::path contents_path = CPathMgr::GetInstance().GetContentsPath();
    fs::path folderPath = contents_path / relativeFolderPath;
    fs::path folderName = folderPath.filename();
    fs::path jsonFilePath = folderPath / (folderName.wstring() + L".json");

    // JSON 파일 열기
    std::ifstream jsonFile(jsonFilePath);
    if (!jsonFile.is_open())
    {
        std::wstring message = L"Failed to open JSON file: " + jsonFilePath.wstring();
        MessageBox(NULL, message.c_str(), L"Error", MB_ICONERROR | MB_OK);
        return;
    }

    json j;
    jsonFile >> j;

    // 아틀라스 텍스쳐 로드
    // JSON 파일에서 텍스쳐 파일 이름을 읽어옵니다.
    auto tmpAtlasTextureName = j["meta"]["image"].get<std::string>();
    std::wstring atlasTextureName(tmpAtlasTextureName.begin(), tmpAtlasTextureName.end());

    // 아틀라스 텍스쳐를 불러오는 새로운 방식을 사용합니다.
    wstring strAtlasTextureName = folderName.wstring() + L"_Atlas";    
    wstring strRelativePngPath = relativeFolderPath + L"\\" + folderName.wstring() + L".png";
    CTexture* pAtlas = CAssetMgr::GetInstance().LoadTexture(strAtlasTextureName, strRelativePngPath);

    if (pAtlas == nullptr)
    {
        std::wstring message = L"Failed to load atlas texture: " + atlasTextureName;
        MessageBox(NULL, message.c_str(), L"Error", MB_ICONERROR | MB_OK);
        return;
    }

    // CAnimation 객체 생성
    CAnimation* pAnim = new CAnimation();
    pAnim->SetAtlasTexture(pAtlas); // 아틀라스 텍스쳐 설정

    // JSON에서 스프라이트 정보 로드 및 처리
    float frameDuration = 1.0f / static_cast<float>(_FPS);
    for (const auto& sprite : j["frames"])
    {
        const auto& filename = sprite["filename"].get<std::string>();
        const auto& frame = sprite["frame"];

        Vec2 startPos(frame["x"], frame["y"]);
        Vec2 sliceSize(frame["w"], frame["h"]);

        // 개별 애니메이션 프레임 생성 및 초기화
        pAnim->CreateAnimationFrame(startPos, sliceSize, frameDuration);
    }

    // 애니메이션 이름 설정 및 Animator에 애니메이션 추가
    pAnim->SetName(folderName.wstring()); // 폴더 이름을 애니메이션 이름으로 사용
    pAnim->m_Animator = this;
    m_mapAnimation.insert(std::make_pair(pAnim->GetName(), pAnim));
}