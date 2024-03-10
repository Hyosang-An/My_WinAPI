#include "pch.h"
#include "CMonster.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_pCollider(nullptr)
{
	CreateCollider();
}

CMonster::~CMonster()
{
}

void CMonster::tick()
{
}