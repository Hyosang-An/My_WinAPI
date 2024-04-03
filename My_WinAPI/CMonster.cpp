#include "pch.h"
#include "CMonster.h"

#include "CCollider.h"
#include "CEngine.h"
#include "CLevelMgr.h"

#include "CIdleState.h"
#include "CTraceState.h"



CMonster::CMonster() :
	m_iHP(3),
	m_fDetectRange(100),
	m_pCollider(nullptr),
	m_pFSM(nullptr)
{
	m_eType = LAYER_TYPE::MONSTER;

	m_pCollider = AddComponent(new CCollider);
	m_pCollider->SetScale(Vec2(120, 120));

	m_pFSM = AddComponent(new CFSM);
	m_pFSM->AddState(L"Idle", new CIdleState);
	m_pFSM->AddState(L"Trace", new CTraceState);
}

CMonster::CMonster(const CMonster& _other) :
	CObj(_other),
	m_iHP(_other.m_iHP),
	m_fDetectRange(100),
	m_pCollider(nullptr),
	m_pFSM(nullptr)
{
	m_eType = LAYER_TYPE::MONSTER;

	m_pCollider = AddComponent(new CCollider(*_other.m_pCollider));

	m_pFSM = AddComponent(new CFSM(*_other.m_pFSM));
}

CMonster::~CMonster()
{
}

void CMonster::begin()
{
	m_pFSM->SetBlackboardData(L"DetectRange", DATA_TYPE::FLOAT, &m_fDetectRange);

	CObj* pPlayer = CLevelMgr::GetInstance().FindObjectByName(L"Player");
	m_pFSM->SetBlackboardData(L"Target", DATA_TYPE::OBJ_PTR, pPlayer);

	m_pFSM->ChangeState(L"Idle");

}

void CMonster::tick()
{
	// SetPos(GetPos() + (m_Dir * m_fSpeed * DT));
}

void CMonster::render()
{
	auto RenderPos = GetRenderPos();
	auto Scale = GetScale();
	Rectangle(SUBDC, (int)(RenderPos.x - Scale.x * 0.5f)
		, (int)(RenderPos.y - Scale.y * 0.5f)
		, (int)(RenderPos.x + Scale.x * 0.5f)
		, (int)(RenderPos.y + Scale.y * 0.5f));
}

void CMonster::OnCollisionEnter(CCollider* _pOwnCollider, CCollider* _pOtherCollider)
{
	CObj* pOtherObj = _pOtherCollider->GetOwner();

	switch (pOtherObj->GetLayerType())
	{
		case LAYER_TYPE::PLAYER_MISSILE:
		{
			m_iHP--;
			if (m_iHP <= 0)
				Destroy();
			break;
		}
	}

}

void CMonster::OnCollisionStay(CCollider* _pOwnCollider, CCollider* _pOtherCollider)
{
}

void CMonster::OnCollisionExit(CCollider* _pOwnCollider, CCollider* _pOtherCollider)
{

}
