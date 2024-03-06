#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"

CObj::CObj()
{
}

CObj::~CObj()
{
}

void CObj::begin()
{
}

void CObj::tick()
{
	// 방향키가 눌리면 이동한다.

	// 현실시간 동기화

	float DT = CTimeMgr::GetInstance().GetDeltaTime();

	float fSpeed = 1000.f;

	// 왼쪽키가 눌린적이 있으면(눌려있으면) 왼쪽으로 1픽셀 이동
	if (0x8001 & GetAsyncKeyState(VK_LEFT))
	{
		m_Pos.x -= fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_RIGHT))
	{
		m_Pos.x += fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_UP))
	{
		m_Pos.y -= fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_DOWN))
	{
		m_Pos.y += fSpeed * DT;
	}
}

void CObj::finaltick()
{
}

void CObj::render()
{
	HDC dc = CEngine::GetInstance().GetMainDC();


	Rectangle(dc, m_Pos.x - m_Scale.x * 0.5f
		, m_Pos.y - m_Scale.y * 0.5f
		, m_Pos.x + m_Scale.x * 0.5f
		, m_Pos.y + m_Scale.y * 0.5f);
}


