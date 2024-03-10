#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fSpeed(1000)
	, m_pCollider(nullptr)
{
	CreateCollider();
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


