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
	// 초당 1000을 카운팅하는 GetTickCount 함수는 정밀도가 떨어진다.

	// 1초에 셀 수 있는  카운트 기준을 얻는다.
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::tick()
{
	// 현재 카운트 계산
	QueryPerformanceCounter(&m_llCurCount);

	// 이전 카운트와 현재 카운트의 차이를 통해 1프레임 간의 시간 차이를 계산
	m_DeltaTime = (double(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart);

	// 누적시간을 통해서 프로그램이 실행된 이후로 지나간 시간을 기록
	m_Time += m_DeltaTime;

	// 현재 카운트 값을 저장
	m_llPrevCount = m_llCurCount;

	// FPS 계산
	m_FPS++;

	// 1초에 한번씩 TextOUT 출력
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

