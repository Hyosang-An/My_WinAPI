#pragma once
#include "CEntity.h"

class CAsset :
    public CEntity
{
    friend class CAssetMgr;

private:
    wstring m_strKey;           // 로딩할 때 사용할 키
    wstring m_strRelativePath;  // 상대 경로

public:
    const wstring& GetKey() const { return m_strKey; }
    const wstring& GetRelativePath() const { return m_strRelativePath; }

public:
    // Load가 순수 가상함수라서 CAsset은 Clone이 안됨.
    virtual int Load(const wstring& _strFilePath) = 0;
public:
    CAsset();
    ~CAsset();
};

