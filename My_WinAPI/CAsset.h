#pragma once
#include "CEntity.h"

class CAsset :
    public CEntity
{
    friend class CAssetMgr;

private:
    wstring m_strKey;           // �ε��� �� ����� Ű
    wstring m_strRelativePath;  // ��� ���

public:
    const wstring& GetKey() const { return m_strKey; }
    const wstring& GetRelativePath() const { return m_strRelativePath; }

public:
    // Load�� ���� �����Լ��� CAsset�� Clone�� �ȵ�.
    virtual int Load(const wstring& _strFilePath) = 0;
public:
    CAsset();
    ~CAsset();
};

