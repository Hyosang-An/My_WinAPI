#include "pch.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CKeyMgr.h"

CPlayer::CPlayer()
	: m_fSpeed(500.f)
{

	CreateCollider();
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

	auto vPos = GetPos();

	// ����Ű�� �������� ������(����������) �������� 1�ȼ� �̵�
	if (KEY_PRESSED(KEY::LEFT))
	{
		vPos.x -= m_fSpeed * DT;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		vPos.x += m_fSpeed * DT;
	}

	if (KEY_PRESSED(KEY::UP))
	{
		vPos.y -= m_fSpeed * DT;
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		vPos.y += m_fSpeed * DT;
	}

	if (KEY_JUST_PRESSED(KEY::SPACE))
	{
		CMissile* pMissile = new CMissile;

		pMissile->SetPos(Vec2(GetPos() + Vec2(0, - GetScale().y * 0.5f)));
		pMissile->SetScale(20, 20);

		CLevelMgr::GetInstance().GetCurrentLevel()->AddObject(pMissile);
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


