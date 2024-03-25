#include "pch.h"
#include "CTraceState.h"

CTraceState::CTraceState()
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
	Range = GetBlackboardData<float>(L"DetectRange");
	Speed = GetBlackboardData<float>(L"Speed");
	pSelf = GetBlackboardData<CObj*>(L"Self");
	pTarget = GetBlackboardData<CObj*>(L"Target");
}

void CTraceState::finaltick()
{

	// 플레이어를 향한다.
	Vec2 vDir = pTarget->GetPos() - pSelf->GetPos();
	if (!vDir.IsZero())
	{
		vDir.Normalize();
		GetObj()->SetDir(vDir);
	}
}

void CTraceState::Exit()
{
}

