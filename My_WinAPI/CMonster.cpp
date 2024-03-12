#include "pch.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CEngine.h"

CMonster::CMonster()
	: m_pCollider(nullptr)
{
	m_eType = LAYER_TYPE::MONSTER;

	m_pCollider = AddComponent(new CCollider);
	m_pCollider->SetScale(Vec2(120, 120));
}

CMonster::~CMonster()
{
}

void CMonster::tick()
{
}

void CMonster::render()
{
	auto Pos = GetPos();
	auto Scale = GetScale();
	Rectangle(SUBDC, (int)(Pos.x - Scale.x * 0.5f)
		, (int)(Pos.y - Scale.y * 0.5f)
		, (int)(Pos.x + Scale.x * 0.5f)
		, (int)(Pos.y + Scale.y * 0.5f));
}

void CMonster::OnCollisionEnter(CCollider* _pOwnCollider, CCollider* _pOtherCollider)
{
	CObj* pOtherObj = _pOtherCollider->GetOwner();
	if (pOtherObj->GetLayerType() == LAYER_TYPE::PLAYER_MISSILE)
	{

	}

}

void CMonster::OnCollisionStay(CCollider* _pOwnCollider, CCollider* _pOtherCollider)
{
}

void CMonster::OnCollisionExit(CCollider* _pOwnCollider, CCollider* _pOtherCollider)
{
	
}
