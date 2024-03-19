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
#include "CGuidedMissile.h"

CPlayer::CPlayer() :
	m_fSpeed(500.f),
	m_Texture{}
{
	m_eType = LAYER_TYPE::PLAYER;

	m_HeadCol = AddComponent(new CCollider);
	m_HeadCol->SetName(L"Head Collider");
	m_HeadCol->SetOffsetPos(Vec2(0, -80));
	m_HeadCol->SetScale(Vec2(30, 30));

	m_BodyCol = AddComponent(new CCollider);
	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 0.f));
	m_BodyCol->SetScale(Vec2(60.f, 60.f));

	m_Texture = CAssetMgr::GetInstance().LoadTexture(L"PlayerTex", L"texture\\Fighter.bmp");
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
		CMissile* pMissile = new CGuidedMissile;

		pMissile->SetPos(Vec2(GetPos() + Vec2(0, - GetScale().y * 0.5f)));
		pMissile->SetScale(20, 20);
		//pMissile->SetAngle(-3.141592f * 0.5);
		pMissile->SetName(L"Player Guided Missile");

		SpawnObject(CLevelMgr::GetInstance().GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);
	}

	SetPos(vPos);
}

void CPlayer::render()
{
	auto vPos = GetPos();
	
	auto texWidth = (m_Texture->GetWith());
	auto texHeight = (m_Texture->GetHeight());


	TransparentBlt(SUBDC, int(vPos.x - texWidth / 2.f)
		, int(vPos.y - texHeight / 2.f)
		, texWidth, texHeight
		, m_Texture->GetDC()
		, 0, 0, texWidth, texHeight,
		RGB(255, 0, 255));
}


