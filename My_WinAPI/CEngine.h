#pragma once
#include "Singleton.h"
class CEngine :
    public Singleton<CEngine>
{
    friend class Singleton<CEngine>;

private:
    HWND    m_hMainWnd;     // 메인 윈도우 핸들
    POINT   m_Resolution;   // 메인 윈도우 해상도
    HDC     m_hDC;          // 메인 윈도우 DC

public:
    int     init(HWND _hWnd, POINT _Resolution);
    void    progress();

private:
    CEngine();
    ~CEngine();
};

