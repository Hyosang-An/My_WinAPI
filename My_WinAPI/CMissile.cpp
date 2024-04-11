#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CEngine.h"
#include "CCollider.h"

CMissile::CMissile() :
	m_fAngle(-3.14f*0.5f),
	m_fSpeed(1000),
	m_pCollider(nullptr)
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
	Vec2 vDir = Vec2(cosf(m_fAngle), sinf(m_fAngle));
	vDir.Normalize();
	vPos += DT * m_fSpeed * vDir;
	SetPos(vPos);
}

void CMissile::render()
{
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();

	Ellipse(SUBDC, (int)(vRenderPos.x - vScale.x * 0.5f)
		, (int)(vRenderPos.y - vScale.y * 0.5f)
		, (int)(vRenderPos.x + vScale.x * 0.5f)
		, (int)(vRenderPos.y + vScale.y * 0.5f));
}

void CMissile::OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider)
{
	CObj* pOtherObj = _pOtherCollider->GetOwner();

	if (pOtherObj->GetLayerType() == LAYER_TYPE::MONSTER)
		SelfDestruct();
}

void CMissile::OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider)
{
}

void CMissile::OnCollisionExit(CCollider* _myCollider, CCollider* _pOtherCollider)
{
}


