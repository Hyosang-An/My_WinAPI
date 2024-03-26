#include "pch.h"
#include "CIdleState.h"

CIdleState::CIdleState() :
	m_fRange(0),
	m_pSelf(nullptr),
	m_pTarget(nullptr)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
	m_fRange = GetBlackboardData<float>(L"DetectRange");
	m_pSelf = GetBlackboardData<CObj*>(L"Self");
	m_pTarget = GetBlackboardData<CObj*>(L"Target");

	m_pSelf->SetSpeed(0);
}

void CIdleState::finaltick()
{
	// 몬스터의 탐지 범위를 시각화
	DrawDebugCircle(PEN_TYPE::GREEN, m_pSelf->GetPos(), Vec2(m_fRange * 2.f, m_fRange * 2.f), 0);

	// 플레이어가 감지되면 Trace State로 변경
	auto dist = m_pTarget->GetPos().GetDistanceWith(m_pSelf->GetPos());
	if (dist < m_fRange)
		GetFSM()->ChangeState(L"Trace");
}

void CIdleState::Exit()
{
}


