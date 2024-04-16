#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CEngine.h"
#include "CCollider.h"

CMissile::CMissile() :
	m_fAngle(-3.14f*0.5f),
	m_fSpeed(200),
	m_Collider(nullptr)
{
	m_Collider = AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(20, 20));
}

CMissile::CMissile(const CMissile& _other) :
	CObj(_other),
	m_fAngle(_other.m_fAngle),
	m_fSpeed(_other.m_fSpeed),
	m_Collider{}
{
	m_Collider = AddComponent(new CCollider(*_other.m_Collider));
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


