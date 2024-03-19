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

