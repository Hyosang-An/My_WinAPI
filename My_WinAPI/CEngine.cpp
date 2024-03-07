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
	// DC 삭제
	ReleaseDC(m_hMainWnd, m_hMainDC);

	// 펜 삭제
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	// 브러쉬 삭제
	for (int i = 0; i < (UINT)BRUSH_TYPE::DELETE_END; ++i)
	{
		DeleteObject(m_arrBrush[i]);
	}
}

int CEngine::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	// 윈도우 해상도 변경
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, m_Resolution.x, m_Resolution.y, 0);

	// DC 및 펜, 브러쉬 생성
	CreateDefaultGDIObj();

	// Manager 초기화
	CLevelMgr::GetInstance().init();
	CTimeMgr::GetInstance().init();


	return S_OK;
}

void CEngine::progress()
{
	CTimeMgr::GetInstance().tick();
	CLevelMgr::GetInstance().progress(); // 레벨에 있는 모든 오브젝트의 tick, finaltick 실행

	// 화면 Clear
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
	// DC생성
	// DC 란? 렌더링과 관련, 비트맵에 렌더링하기 위해 필요한 필수 정보 집합체
	m_hMainDC = GetDC(m_hMainWnd);
	m_hSubDC = CreateCompatibleDC(m_hMainDC);

	m_hSubBitmap = CreateCompatibleBitmap(m_hMainDC, m_Resolution.x, m_Resolution.y);

	// SubDC가 SubBitmap을 지정하게 함.
	HBITMAP hPrevBitmap = static_cast<HBITMAP>(SelectObject(m_hSubDC, m_hSubBitmap));
	DeleteObject(hPrevBitmap);

	// 자주 사용할 펜 생성
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// 자주 사용할 브러쉬 생성
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::GRAY] = CreateSolidBrush(RGB(100, 100, 100));
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
}
