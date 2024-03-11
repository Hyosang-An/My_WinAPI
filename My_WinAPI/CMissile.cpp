#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CEngine.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_fSpeed(200)
	, m_pCollider(nullptr)
{
	m_pCollider = AddComponent(new CCollider);
	m_pCollider->SetScale(Vec2(20, 20));
}

CMissile::~CMissile()
{
}

void CMissile::tick()
{
	Vec2 vPos = GetPos();
	vPos.y -= DT * m_fSpeed;
	SetPos(vPos);
}

void CMissile::render()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(SUBDC, (int)(vPos.x - vScale.x * 0.5f)
		, (int)(vPos.y - vScale.y * 0.5f)
		, (int)(vPos.x + vScale.x * 0.5f)
		, (int)(vPos.y + vScale.y * 0.5f));
}


