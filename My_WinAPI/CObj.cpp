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
	// ����Ű�� ������ �̵��Ѵ�.

	// ���ǽð� ����ȭ

	float DT = CTimeMgr::GetInstance().GetDeltaTime();

	float fSpeed = 1000.f;

	// ����Ű�� �������� ������(����������) �������� 1�ȼ� �̵�
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


