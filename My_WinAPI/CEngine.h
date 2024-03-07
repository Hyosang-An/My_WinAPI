#pragma once
#include "Singleton.h"
class CEngine :
    public Singleton<CEngine>
{
    friend class Singleton<CEngine>;

private:
    HWND    m_hMainWnd;     // ���� ������ �ڵ�
    POINT   m_Resolution;   // ���� ������ �ػ�
    HDC     m_hMainDC;          // ���� ������ DC
    HDC     m_hSubDC;       // ���� DC
    HBITMAP m_hSubBitmap;   // ���� bitmap

    HPEN    m_arrPen[(UINT)PEN_TYPE::END];
    HBRUSH  m_arrBrush[(UINT)BRUSH_TYPE::END];

public:
    int     init(HWND _hWnd, POINT _Resolution);
    void    progress();

    HPEN    GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }
    HBRUSH  GetBrush(BRUSH_TYPE _type) { return m_arrBrush[(UINT)_type]; }

    HDC     GetMainDC() { return m_hMainDC; }
    HDC     GetSubDC() { return m_hSubDC; }
    HWND    GetMainWnd() { return m_hMainWnd; }

private:
    void CreateDefaultGDIObj();

private:
    CEngine();
    ~CEngine();
};

