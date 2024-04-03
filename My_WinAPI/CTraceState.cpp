#include "pch.h"
#include "CTraceState.h"

CTraceState::CTraceState() :
	m_fRange(0),
	m_pTarget(nullptr)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
	m_fRange = GetBlackboardData<float>(L"DetectRange");
	m_pTarget = GetBlackboardData<CObj*>(L"Target");

	// 몬스터 속도 설정
	// TODO
}

void CTraceState::finaltick()
{
	auto selfObj = GetObj();
	// 몬스터의 탐지 범위를 시각화
	DrawDebugCircle(PEN_TYPE::GREEN, selfObj->GetPos(), Vec2(m_fRange * 2.f, m_fRange * 2.f), 0);

	// 플레이어를 향한다.
	Vec2 vDir = m_pTarget->GetPos() - selfObj->GetPos();
	if (!vDir.IsZero())
	{
		// 몬스터 방향 설정
		// TODO
	}

	// 플레이어가 탐지 범위 밖으로 가면 Idle State로 변경
	auto dist = m_pTarget->GetPos().GetDistanceWith(selfObj->GetPos());
	if (dist > m_fRange)
		GetFSM()->ChangeState(L"Idle");

}

void CTraceState::Exit()
{
	// 몬스터 속도 0
	// TODO
}

