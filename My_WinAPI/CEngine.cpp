#include "pch.h"
#include "CEngine.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_Resolution{}
	, m_hDC(nullptr)
{

}

CEngine::~CEngine()
{
	//DC ����
	ReleaseDC(m_hMainWnd, m_hDC);
}

int CEngine::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	// ������ �ػ� ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, m_Resolution.x, m_Resolution.y, 0);

	// DC����
	m_hDC = GetDC(m_hMainWnd);

	return S_OK;
}

void CEngine::progress()
{
}

