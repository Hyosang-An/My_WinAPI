#pragma once
#include "CAsset.h"
class CTexture :
    public CAsset
{
    friend class CAssetMgr;

private:
    HDC     m_hDC;
    HBITMAP m_hBitmap;
    BITMAP  m_Info;

private:
    virtual int Load(const wstring& _strFilePath) override;

public:
    HDC GetDC() { return m_hDC; }
    LONG GetWith() { return m_Info.bmWidth; }
    LONG GetHeight() { return m_Info.bmHeight; }

public:
    CTexture();
    ~CTexture();
};

