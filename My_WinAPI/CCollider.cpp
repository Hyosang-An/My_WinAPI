#include "pch.h"
#include "CCollider.h"
#include "CObj.h"
#include "CEngine.h"
#include "CDbgRenderer.h"

CCollider::CCollider()
{
}

CCollider::~CCollider()
{
}

void CCollider::finaltick()
{
	// Obj�� ��ġ�� ���󰡵��� ������Ʈ
	auto pos = m_pOwner->GetPos();
	m_vFinalPos = pos + m_vOffsetPos;

	DrawDebugRect(PEN_TYPE::GREEN, m_vFinalPos, m_vScale, 0.f);
}

void CCollider::OnCollisionEnter(CCollider* _pOtherCollider)
{
	int a;
}

void CCollider::OnCollisionStay(CCollider* _pOtherCollider)
{
	int a;

}

void CCollider::OnCollisionExit(CCollider* _pOtherCollider)
{
	int a;

}
