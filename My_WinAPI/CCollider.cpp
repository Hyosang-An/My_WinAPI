#include "pch.h"
#include "CCollider.h"
#include "CObj.h"
#include "CEngine.h"
#include "CDbgRenderer.h"

CCollider::CCollider()
	: m_CollisionCount(0)
	, m_bActive(true)
{
}

CCollider::~CCollider()
{
}

void CCollider::finaltick()
{
	// Obj의 위치를 따라가도록 업데이트
	auto pos = m_pOwner->GetPos();
	m_vFinalPos = pos + m_vOffsetPos;

	DrawDebugRect(PEN_TYPE::GREEN, m_vFinalPos, m_vScale, 0.f);
}

void CCollider::OnCollisionEnter(CCollider* _pOtherCollider)
{
	m_CollisionCount++;
	m_pOwner->OnCollisionEnter(this, _pOtherCollider);
}

void CCollider::OnCollisionStay(CCollider* _pOtherCollider)
{
	m_pOwner->OnCollisionStay(this, _pOtherCollider);
}

void CCollider::OnCollisionExit(CCollider* _pOtherCollider)
{
	m_CollisionCount--;
	m_pOwner->OnCollisionExit(this, _pOtherCollider);
}
