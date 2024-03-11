#include "pch.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CEngine.h"

CMonster::CMonster()
	: m_pCollider(nullptr)
{
	//CreateCollider();
	//GetCollider()->SetScale(Vec2(120, 120));
	
	// 추후 수정 
	// m_pCollider->SetScale(Vec2(120, 120));

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
