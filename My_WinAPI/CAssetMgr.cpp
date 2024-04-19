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
	// ��ϵ� �ؽ��İ� �̹� ������ �ִ� �� ��ȯ
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
		return pTex;

	// �ؽ��İ� ������ ���� �� ��� �� ��ȯ
	wstring strFilePath = CPathMgr::GetInstance().GetContentsPath();
	strFilePath += (L"\\" + _strRelativePath);

	pTex = new CTexture;
	if (FAILED(pTex->Load(strFilePath)))
	{
		MessageBox(nullptr, strFilePath.c_str(), L"�ؽ��� �ε� ����", MB_OK);
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
		MessageBox(nullptr, _strKey.c_str(), L"�ؽ��� ���� ����", MB_OK);
		delete pTex;
		return nullptr;
	}

	m_mapTexture.insert(make_pair(_strKey, pTex));
	pTex->m_strKey = _strKey;

	return pTex;
}

CSound* CAssetMgr::LoadSound(const wstring& _Key, const wstring& _strRelativePath)
{
	// �̹� �ش� Ű�� ��ϵ� ���尡 ������ �ش� sound return
	CSound* pSound = FindSound(_Key);
	if (nullptr != pSound)
	{
		return pSound;
	}

	// Full Path �� �����
	wstring strFilePath = CPathMgr::GetInstance().GetContentsPath();
	strFilePath += (L"\\" + _strRelativePath);

	// ���� ��ü ����
	// ���� �ε�
	pSound = new CSound;
	if (FAILED(pSound->Load(strFilePath)))
	{
		MessageBox(nullptr, _strRelativePath.c_str(), L"���� �ε� ����", MB_OK);
		delete pSound;
		return nullptr;
	}

	// map �� �ε��� �ؽ��ĸ� ���
	m_mapSound.insert(make_pair(_Key, pSound));

	// �ؽ��� ���¿� ������ Ű���� ����θ� �˷���
	pSound->m_strKey = _Key;
	pSound->m_strRelativePath = _strRelativePath;

	return pSound;
}

CSound* CAssetMgr::FindSound(const wstring& _Key)
{
	return nullptr;
}

