#include "pch.h"
#include "CTraceState.h"

CTraceState::CTraceState() :
	m_fRange(0),
	m_pSelf(nullptr),
	m_pTarget(nullptr)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
	m_fRange = GetBlackboardData<float>(L"DetectRange");
	m_pSelf = GetBlackboardData<CObj*>(L"Self");
	m_pTarget = GetBlackboardData<CObj*>(L"Target");

	m_pSelf->SetSpeed(100);
}

void CTraceState::finaltick()
{
	// ������ Ž�� ������ �ð�ȭ
	DrawDebugCircle(PEN_TYPE::GREEN, m_pSelf->GetPos(), Vec2(m_fRange * 2.f, m_fRange * 2.f), 0);

	// �÷��̾ ���Ѵ�.
	Vec2 vDir = m_pTarget->GetPos() - m_pSelf->GetPos();
	if (!vDir.IsZero())
	{
		m_pSelf->SetDir(vDir.Normalize());
	}

	// �÷��̾ Ž�� ���� ������ ���� Idle State�� ����
	auto dist = m_pTarget->GetPos().GetDistanceWith(m_pSelf->GetPos());
	if (dist > m_fRange)
		GetFSM()->ChangeState(L"Idle");

}

void CTraceState::Exit()
{
	m_pSelf->SetSpeed(0);
}

