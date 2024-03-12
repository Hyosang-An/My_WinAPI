#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CComponent.h"
#include "CCollider.h"

CObj::CObj()
	: m_eType(LAYER_TYPE::NONE)
{
}

CObj::~CObj()
{
	Safe_Del_Vec(m_vecComponent);

	//if (m_pCollider != nullptr)
	//	delete m_pCollider;
}

void CObj::begin()
{
}

void CObj::tick()
{

}

void CObj::finaltick()
{
	for (size_t i = 0; i < m_vecComponent.size(); i++)
	{
		m_vecComponent[i]->finaltick();
	}

	//À¯Æ©ºê ¿ë
	//if (m_pCollider)
	//	m_pCollider->finaltick();
}

void CObj::render()
{
	Rectangle(SUBDC, (int)(m_Pos.x - m_Scale.x * 0.5f)
		, (int)(m_Pos.y - m_Scale.y * 0.5f)
		, (int)(m_Pos.x + m_Scale.x * 0.5f)
		, (int)(m_Pos.y + m_Scale.y * 0.5f));

	//ComponentRender();
}

//void CObj::ComponentRender()
//{
//	if (m_pCollider)
//	{
//		m_pCollider->render();
//	}
//}

//void CObj::CreateCollider()
//{
//	m_pCollider = new CCollider;
//	m_pCollider->m_pOwner = this;
//
//	m_vecComponent.push_back(m_pCollider);
//}

