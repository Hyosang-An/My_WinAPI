#include "pch.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CKeyMgr.h"
#include "CCollider.h"
#include "CDbgRenderer.h"


#include "CEngine.h"

CPlayer::CPlayer()
	: m_fSpeed(500.f)
	, m_pCollider(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(120, 120));
	//GetCollider()->SetOffsetPos(Vec2(100, 100));

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

void CPlayer::render()
{
	auto Pos = GetPos();
	auto Scale = GetScale();

	Rectangle(SUBDC, (int)(Pos.x - Scale.x * 0.5f)
		, (int)(Pos.y - Scale.y * 0.5f)
		, (int)(Pos.x + Scale.x * 0.5f)
		, (int)(Pos.y + Scale.y * 0.5f));

	//ComponentRender();
}


