#include "pch.h"
#include "CWall.h"

CWall::CWall() 
{
	m_WallCollider = AddComponent(new CCollider);
}

CWall::CWall(const CWall& _other)
{
	m_WallCollider = AddComponent(new CCollider(*_other.m_WallCollider));
}

CWall::~CWall()
{
}


void CWall::SetColliderScale(Vec2 _scale)
{
	m_WallCollider->SetScale(_scale);
}

void CWall::OnCollisionEnter(CCollider* _pOtherCollider)
{
}

void CWall::OnCollisionStay(CCollider* _pOtherCollider)
{
}

void CWall::OnCollisionExit(CCollider* _pOtherCollider)
{
}
