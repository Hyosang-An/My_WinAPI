#pragma once
#include "Singleton.h"
class CEngine :
    public Singleton<CEngine>
{
    friend class Singleton<CEngine>;

private:
    HWND    m_hMainWnd;     // ���� ������ �ڵ�
    POINT   m_Resolution;   // ���� ������ �ػ�
    HDC     m_hDC;          // ���� ������ DC

public:
    int     init(HWND _hWnd, POINT _Resolution);
    void    progress();

private:
    CEngine();
    ~CEngine();
};

