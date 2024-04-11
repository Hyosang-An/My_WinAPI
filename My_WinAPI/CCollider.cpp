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

CCollider::CCollider(const CCollider& _other) :
	CComponent(_other),
	m_vOffsetPos(_other.m_vOffsetPos),
	m_vScale(_other.m_vScale),
	m_CollisionCount(0),
	m_bActive(_other.m_bActive)
{
}

CCollider::~CCollider()
{
}

void CCollider::finaltick()
{
	// Obj의 위치를 따라가도록 업데이트
	auto pos = m_Owner->GetPos();
	m_vFinalPos = pos + m_vOffsetPos;
}

void CCollider::OnCollisionEnter(CCollider* _pOtherCollider)
{
	m_CollisionCount++;
	m_Owner->OnCollisionEnter(this, _pOtherCollider);
}

void CCollider::OnCollisionStay(CCollider* _pOtherCollider)
{
	m_Owner->OnCollisionStay(this, _pOtherCollider);
}

void CCollider::OnCollisionExit(CCollider* _pOtherCollider)
{
	m_CollisionCount--;
	m_Owner->OnCollisionExit(this, _pOtherCollider);
}
