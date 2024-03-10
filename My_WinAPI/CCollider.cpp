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
	// Obj의 위치를 따라가도록 업데이트
	auto pos = m_pOwner->GetPos();
	m_vFinalPos = pos + m_vOffsetPos;

	DrawDebugRect(PEN_TYPE::GREEN, m_vFinalPos, m_vScale, 0.f);
}

void CCollider::render()
{
	USE_PEN(SUBDC, PEN_TYPE::GREEN);
	USE_BRUSH(SUBDC, BRUSH_TYPE::HOLLOW);
	Rectangle(SUBDC, int(m_vFinalPos.x - m_vScale.x * 0.5f),
					 int(m_vFinalPos.y - m_vScale.y * 0.5f),
					 int(m_vFinalPos.x + m_vScale.x * 0.5f),
					 int(m_vFinalPos.y + m_vScale.y * 0.5f));
}