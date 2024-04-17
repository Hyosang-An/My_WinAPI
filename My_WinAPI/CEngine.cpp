#include "pch.h"
#include "CEngine.h"
#include "CLevelMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CDbgRenderer.h"
#include "CCollisionMgr.h"
#include "CTaskMgr.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CRandomMgr.h"

CEngine::CEngine()
	: m_hInstance{}
	, m_hMainWnd(nullptr)
	, m_Resolution{}
	, m_hMainDC(nullptr)
	, m_arrPen{}
	, m_arrBrush{}
	, m_SubTexture{}
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

int CEngine::init(HINSTANCE _hInst, HWND _hWnd, POINT _Resolution)
{
	m_hInstance = _hInst;
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	ChangeWindowSize(m_Resolution, false);

	// DC 및 펜, 브러쉬 생성
	CreateDefaultGDIObj();

	// Manager 초기화
	CPathMgr::GetInstance().init();
	CTimeMgr::GetInstance().init();
	CKeyMgr::GetInstance().init();
	CAssetMgr::GetInstance().init();
	CCamera::GetInstance().init();
	CCollisionMgr::GetInstance().init();
	CRandomMgr::GetInstance().init();
	
	CLevelMgr::GetInstance().init();

	return S_OK;
}

void CEngine::progress()
{
	//		||Manager Tick||
	// ==================================================================================
	CTimeMgr::GetInstance().tick();			// 매 프레임간 DT, FPS 계산 및 출력
	CKeyMgr::GetInstance().tick();			// 키 입력 확인 및 키 상태 변경
	CDbgRenderer::GetInstance().tick();
	CCamera::GetInstance().tick();
	// ==================================================================================


	//		||Level Progress||
	// ==================================================================================
	CLevelMgr::GetInstance().progress();	// 레벨에 있는 모든 오브젝트의 tick, finaltick 실행
	// ==================================================================================


	//		||Collision Check||
	// ==================================================================================
	CCollisionMgr::GetInstance().tick();
	// ==================================================================================


	//		||Rendering||
	// ==================================================================================
	// 화면 Clear
	{
		USE_BRUSH(GetSubDC(), BRUSH_TYPE::GRAY);
		Rectangle(GetSubDC(), -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);
	}

	// 레벨에 있는 모든 오브젝트 렌더링
	CLevelMgr::GetInstance().render();	

	// 카메라 이펙트 렌더링
	CCamera::GetInstance().CameraEffectRender();

	// 디버그 렌더링 !디버깅
	CDbgRenderer::GetInstance().render();

	// Path 렌더링
	//CPathMgr::GetInstance().render();

	// SubDC -> MainDC
	BitBlt(m_hMainDC, 0, 0, m_Resolution.x, m_Resolution.y, GetSubDC(), 0, 0, SRCCOPY);
	// ==================================================================================


	//		||Task 처리||  가장 마지막에 수행해야 함
	// ==================================================================================
	CTaskMgr::GetInstance().tick();
	// ==================================================================================

}

HDC CEngine::GetSubDC()
{
	return m_SubTexture->GetDC();
}

void CEngine::ChangeWindowSize(Vec2 _Resolution, bool _bMenu)
{
	// 입력된 해상도를 가져가기 위한 실제 윈도우의 크기를 계산
	RECT rt = { 0, 0, (LONG)_Resolution.x, (LONG)_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);

	// 윈도우 크기를 변경
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CEngine::CreateDefaultGDIObj()
{
	// DC생성
	// DC 란? 렌더링과 관련, 비트맵에 렌더링하기 위해 필요한 필수 정보 집합체
	m_hMainDC = GetDC(m_hMainWnd);
	
	m_SubTexture = CAssetMgr::GetInstance().CreateTexture(L"SubTexture", (UINT)m_Resolution.x, (UINT)m_Resolution.y);

	// 자주 사용할 펜 생성
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	// 자주 사용할 브러쉬 생성
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::GRAY] = CreateSolidBrush(RGB(100, 100, 100));
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
}

