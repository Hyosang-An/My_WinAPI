#pragma once
#include "CAsset.h"
class CTexture :
    public CAsset
{
    friend class CAssetMgr;
    friend class CAnimator;

private:
    HDC     m_hDC;
    HBITMAP m_hBitmap;
    BITMAP  m_Info;

private:
    virtual int Load(const wstring& _strFilePath) override;

    int Create(UINT _width, UINT _height);

public:
    HDC GetDC() { return m_hDC; }
    LONG GetWidth() { return m_Info.bmWidth; }
    LONG GetHeight() { return m_Info.bmHeight; }

public:
    CTexture();
    ~CTexture();
};

