#include "pch.h"
#include "CEngine.h"
#include "CLevelMgr.h"
#include "CTimeMgr.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_Resolution{}
	, m_hMainDC(nullptr)
	, m_hSubDC(nullptr)
	, m_hSubBitmap(nullptr)
	, m_arrPen{}
	, m_arrBrush{}
{

}

CEngine::~CEngine()
{
	// DC ����
	ReleaseDC(m_hMainWnd, m_hMainDC);

	// �� ����
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	// �귯�� ����
	for (int i = 0; i < (UINT)BRUSH_TYPE::DELETE_END; ++i)
	{
		DeleteObject(m_arrBrush[i]);
	}
}

int CEngine::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	// ������ �ػ� ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, m_Resolution.x, m_Resolution.y, 0);

	// DC �� ��, �귯�� ����
	CreateDefaultGDIObj();

	// Manager �ʱ�ȭ
	CLevelMgr::GetInstance().init();
	CTimeMgr::GetInstance().init();


	return S_OK;
}

void CEngine::progress()
{
	CTimeMgr::GetInstance().tick();
	CLevelMgr::GetInstance().progress(); // ������ �ִ� ��� ������Ʈ�� tick, finaltick ����

	// ȭ�� Clear
	{
		USE_BRUSH(m_hSubDC, BRUSH_TYPE::GRAY);
		Rectangle(m_hSubDC, -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);
	}

	CLevelMgr::GetInstance().render();
	
	// SubDC -> MainDC
	BitBlt(m_hMainDC, 0, 0, m_Resolution.x, m_Resolution.y, m_hSubDC, 0, 0, SRCCOPY);
}

void CEngine::CreateDefaultGDIObj()
{
	// DC����
	// DC ��? �������� ����, ��Ʈ�ʿ� �������ϱ� ���� �ʿ��� �ʼ� ���� ����ü
	m_hMainDC = GetDC(m_hMainWnd);
	m_hSubDC = CreateCompatibleDC(m_hMainDC);

	m_hSubBitmap = CreateCompatibleBitmap(m_hMainDC, m_Resolution.x, m_Resolution.y);

	// SubDC�� SubBitmap�� �����ϰ� ��.
	HBITMAP hPrevBitmap = static_cast<HBITMAP>(SelectObject(m_hSubDC, m_hSubBitmap));
	DeleteObject(hPrevBitmap);

	// ���� ����� �� ����
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// ���� ����� �귯�� ����
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::GRAY] = CreateSolidBrush(RGB(100, 100, 100));
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
}
