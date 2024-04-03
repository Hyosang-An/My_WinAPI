#include "pch.h"
#include "CIdleState.h"

CIdleState::CIdleState() :
	m_fRange(0),
	m_pTarget(nullptr)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
	m_fRange = GetBlackboardData<float>(L"DetectRange");
	m_pTarget = GetBlackboardData<CObj*>(L"Target");
}

void CIdleState::finaltick()
{
	auto selfObj = GetObj();

	// ������ Ž�� ������ �ð�ȭ
	DrawDebugCircle(PEN_TYPE::GREEN, selfObj->GetPos(), Vec2(m_fRange * 2.f, m_fRange * 2.f), 0);

	// �÷��̾ �����Ǹ� Trace State�� ����
	auto dist = m_pTarget->GetPos().GetDistanceWith(selfObj->GetPos());
	if (dist < m_fRange)
		GetFSM()->ChangeState(L"Trace");
}

void CIdleState::Exit()
{
}


