#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"

CAssetMgr::CAssetMgr()
{
}

CAssetMgr::~CAssetMgr()
{
	Safe_Del_Map(m_mapTexture);
	Safe_Del_Map(m_mapSound);
}

void CAssetMgr::init()
{
}

CTexture* CAssetMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 등록된 텍스쳐가 이미 있으면 있는 것 반환
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
		return pTex;

	// 텍스쳐가 없으면 생성 및 등록 후 반환
	wstring strFilePath = CPathMgr::GetInstance().GetContentsPath();
	strFilePath += (L"\\" + _strRelativePath);

	pTex = new CTexture;
	if (FAILED(pTex->Load(strFilePath)))
	{
		MessageBox(nullptr, strFilePath.c_str(), L"텍스쳐 로딩 실패", MB_OK);
		delete pTex;

		return nullptr;
	}

	m_mapTexture.insert(make_pair(_strKey, pTex));

	pTex->m_strKey = _strKey;
	pTex->m_strRelativePath = _strRelativePath;

	return pTex;
}

CTexture* CAssetMgr::FindTexture(const wstring& _strKey)
{
	auto iter = m_mapTexture.find(_strKey);
	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second;
}

CTexture* CAssetMgr::CreateTexture(const wstring& _strKey, UINT _width, UINT _height)
{
	assert(FindTexture(_strKey) == nullptr);

	CTexture* pTex = new CTexture;
	if (FAILED(pTex->Create(_width, _height)))
	{
		MessageBox(nullptr, _strKey.c_str(), L"텍스쳐 생성 실패", MB_OK);
		delete pTex;
		return nullptr;
	}

	m_mapTexture.insert(make_pair(_strKey, pTex));
	pTex->m_strKey = _strKey;

	return pTex;
}

CSound* CAssetMgr::LoadSound(const wstring& _Key, const wstring& _strRelativePath)
{
	// 이미 해당 키로 등록된 사운드가 있으면 해당 sound return
	CSound* pSound = FindSound(_Key);
	if (nullptr != pSound)
	{
		return pSound;
	}

	// Full Path 로 만들기
	wstring strFilePath = CPathMgr::GetInstance().GetContentsPath();
	strFilePath += (L"\\" + _strRelativePath);

	// 사운드 객체 생성
	// 사운드 로딩
	pSound = new CSound;
	if (FAILED(pSound->Load(strFilePath)))
	{
		MessageBox(nullptr, _strRelativePath.c_str(), L"사운드 로딩 실패", MB_OK);
		delete pSound;
		return nullptr;
	}

	// map 에 로딩된 텍스쳐를 등록
	m_mapSound.insert(make_pair(_Key, pSound));

	// 텍스쳐 에셋에 본인의 키값과 상대경로를 알려줌
	pSound->m_strKey = _Key;
	pSound->m_strRelativePath = _strRelativePath;

	return pSound;
}

CSound* CAssetMgr::FindSound(const wstring& _Key)
{
	auto iter = m_mapSound.find(_Key);
	if (iter == m_mapSound.end())
	{
		return nullptr;
	}

	else
	{
		return iter->second;
	}
}

