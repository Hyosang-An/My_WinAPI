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

	// ���� �ӵ� ����
	// TODO
}

void CTraceState::finaltick()
{
	auto selfObj = GetObj();
	// ������ Ž�� ������ �ð�ȭ
	DrawDebugCircle(PEN_TYPE::RED, selfObj->GetPos(), Vec2(m_fRange * 2.f, m_fRange * 2.f), 0);

	// �÷��̾ ���Ѵ�.
	Vec2 vDir = m_pTarget->GetPos() - selfObj->GetPos();
	if (!vDir.IsZero())
	{
		// ���� ���� ����
		// TODO
	}

	// �÷��̾ Ž�� ���� ������ ���� Idle State�� ����
	auto dist = m_pTarget->GetPos().GetDistanceWith(selfObj->GetPos());
	if (dist > m_fRange)
		GetFSM()->ChangeState(L"Idle");

}

void CTraceState::Exit()
{
	// ���� �ӵ� 0
	// TODO
}

