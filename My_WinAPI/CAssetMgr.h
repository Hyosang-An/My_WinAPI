#pragma once
#include "Singleton.h"

#include "CTexture.h"
#include "CSound.h"

class CAssetMgr :
	public Singleton<CAssetMgr>
{
	friend Singleton<CAssetMgr>;

private:
	map<wstring, CTexture*> m_mapTexture;
	map<wstring, CSound*>   m_mapSound;

public:
	void init();

	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey);

private:
	CAssetMgr();
	~CAssetMgr();
};

