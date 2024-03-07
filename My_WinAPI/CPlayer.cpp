#include "pch.h"
#include "CPlayer.h"
#include "CTimeMgr.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::begin()
{
}

void CPlayer::tick()
{
	// ����Ű�� ������ �̵��Ѵ�.

	// ���ǽð� ����ȭ

	float DT = CTimeMgr::GetInstance().GetDeltaTime();

	float fSpeed = 1000.f;

	auto vPos = GetPos();

	// ����Ű�� �������� ������(����������) �������� 1�ȼ� �̵�
	if (0x8001 & GetAsyncKeyState(VK_LEFT))
	{
		vPos.x -= fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_RIGHT))
	{
		vPos.x += fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_UP))
	{
		vPos.y -= fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_DOWN))
	{
		vPos.y += fSpeed * DT;
	}

	SetPos(vPos);
}

void CPlayer::finaltick()
{
}

void CPlayer::render()
{
	CObj::render();
}


