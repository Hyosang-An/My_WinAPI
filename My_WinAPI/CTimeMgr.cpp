#include "pch.h"
#include "CTimeMgr.h"
#include "CEngine.h"	

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_FPS(0)
	, m_DeltaTime(0)
	, m_Time(0)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	// �ʴ� 1000�� ī�����ϴ� GetTickCount �Լ��� ���е��� ��������.

	// 1�ʿ� �� �� �ִ�  ī��Ʈ ������ ��´�.
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::tick()
{
	// ���� ī��Ʈ ���
	QueryPerformanceCounter(&m_llCurCount);

	// ���� ī��Ʈ�� ���� ī��Ʈ�� ���̸� ���� 1������ ���� �ð� ���̸� ���
	m_DeltaTime = (double(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart);

	// �����ð��� ���ؼ� ���α׷��� ����� ���ķ� ������ �ð��� ���
	m_Time += m_DeltaTime;

	// ���� ī��Ʈ ���� ����
	m_llPrevCount = m_llCurCount;

	// FPS ���
	m_FPS++;

	// 1�ʿ� �ѹ��� TextOUT ���
	static double AccTime = 0.f;
	AccTime += m_DeltaTime;

	if (1 < AccTime)
	{
		wchar_t szBuff[255]{};
		swprintf_s(szBuff, L"DeltaTime : %f, FPS : %d ", m_DeltaTime, m_FPS);
		TextOut(CEngine::GetInstance().GetMainDC(), 10, 10, szBuff, wcslen(szBuff));
		SetWindowText(CEngine::GetInstance().GetMainWnd(), szBuff);
		AccTime = 0;
		m_FPS = 0;
	}
}

