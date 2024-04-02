#pragma once
#include "Singleton.h"

class CTexture;

class CEngine :
    public Singleton<CEngine>
{
    friend class Singleton<CEngine>;

private:
    HINSTANCE   m_hInstance;    //프로세스 메모리 핸들
    HWND        m_hMainWnd;     // 메인 윈도우 핸들
    POINT       m_Resolution;   // 메인 윈도우 해상도
    HDC         m_hMainDC;          // 메인 윈도우 DC
   
    CTexture*   m_SubTexture;     // 더블 버퍼링 용도 텍스쳐

    HPEN    m_arrPen[(UINT)PEN_TYPE::END];
    HBRUSH  m_arrBrush[(UINT)BRUSH_TYPE::END];

public:
    int     init(HINSTANCE _hInst, HWND _hWnd, POINT _Resolution);
    void    progress();

    HPEN    GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }
    HBRUSH  GetBrush(BRUSH_TYPE _type) { return m_arrBrush[(UINT)_type]; }

    HDC     GetMainDC() { return m_hMainDC; }
    HDC     GetSubDC();
    HWND    GetMainWnd() { return m_hMainWnd; }
    HINSTANCE GetProcessInstance() { return m_hInstance; }
    Vec2    GetResolution() { return m_Resolution; }

private:
    void CreateDefaultGDIObj();

private:
    CEngine();
    ~CEngine();
};
