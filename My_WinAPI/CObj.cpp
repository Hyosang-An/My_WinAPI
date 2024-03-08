#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CComponent.h"
#include "CCollider.h"

CObj::CObj()

{
}

CObj::~CObj()
{
	Safe_Del_Vec(m_vecComponent);

	if (m_pCollider != nullptr)
		delete m_pCollider;
}

void CObj::begin()
{
}

void CObj::tick()
{
	
}

void CObj::finaltick()
{
}

void CObj::render()
{
	Rectangle(SUBDC, (int)(m_Pos.x - m_Scale.x * 0.5f)
		, (int)(m_Pos.y - m_Scale.y * 0.5f)
		, (int)(m_Pos.x + m_Scale.x * 0.5f)
		, (int)(m_Pos.y + m_Scale.y * 0.5f));
}

CComponent* CObj::AddComponent(CComponent* _component)
{
	_component->m_pOwner = this;
	m_vecComponent.push_back(_component);

	return _component;
}

void CObj::CreateCollider()
{
	m_pCollider = new CCollider;
}

