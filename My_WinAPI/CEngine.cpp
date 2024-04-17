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

int CEngine::init(HINSTANCE _hInst, HWND _hWnd, POINT _Resolution)
{
	m_hInstance = _hInst;
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	ChangeWindowSize(m_Resolution, false);

	// DC �� ��, �귯�� ����
	CreateDefaultGDIObj();

	// Manager �ʱ�ȭ
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
	CTimeMgr::GetInstance().tick();			// �� �����Ӱ� DT, FPS ��� �� ���
	CKeyMgr::GetInstance().tick();			// Ű �Է� Ȯ�� �� Ű ���� ����
	CDbgRenderer::GetInstance().tick();
	CCamera::GetInstance().tick();
	// ==================================================================================


	//		||Level Progress||
	// ==================================================================================
	CLevelMgr::GetInstance().progress();	// ������ �ִ� ��� ������Ʈ�� tick, finaltick ����
	// ==================================================================================


	//		||Collision Check||
	// ==================================================================================
	CCollisionMgr::GetInstance().tick();
	// ==================================================================================


	//		||Rendering||
	// ==================================================================================
	// ȭ�� Clear
	{
		USE_BRUSH(GetSubDC(), BRUSH_TYPE::GRAY);
		Rectangle(GetSubDC(), -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);
	}

	// ������ �ִ� ��� ������Ʈ ������
	CLevelMgr::GetInstance().render();	

	// ī�޶� ����Ʈ ������
	CCamera::GetInstance().CameraEffectRender();

	// ����� ������ !�����
	CDbgRenderer::GetInstance().render();

	// Path ������
	//CPathMgr::GetInstance().render();

	// SubDC -> MainDC
	BitBlt(m_hMainDC, 0, 0, m_Resolution.x, m_Resolution.y, GetSubDC(), 0, 0, SRCCOPY);
	// ==================================================================================


	//		||Task ó��||  ���� �������� �����ؾ� ��
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
	// �Էµ� �ػ󵵸� �������� ���� ���� �������� ũ�⸦ ���
	RECT rt = { 0, 0, (LONG)_Resolution.x, (LONG)_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);

	// ������ ũ�⸦ ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CEngine::CreateDefaultGDIObj()
{
	// DC����
	// DC ��? �������� ����, ��Ʈ�ʿ� �������ϱ� ���� �ʿ��� �ʼ� ���� ����ü
	m_hMainDC = GetDC(m_hMainWnd);
	
	m_SubTexture = CAssetMgr::GetInstance().CreateTexture(L"SubTexture", (UINT)m_Resolution.x, (UINT)m_Resolution.y);

	// ���� ����� �� ����
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	// ���� ����� �귯�� ����
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::GRAY] = CreateSolidBrush(RGB(100, 100, 100));
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
}

