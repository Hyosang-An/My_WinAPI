#include "pch.h"
#include "CWall.h"

CWall::CWall() 
{
	m_WallCollider = AddComponent(new CCollider);
}

CWall::CWall(const CWall& _other)
{
	m_WallCollider = AddComponent(new CCollider(*_other.m_WallCollider));
}

CWall::~CWall()
{
}


void CWall::SetColliderScale(Vec2 _scale)
{
	m_WallCollider->SetScale(_scale);
}

void CWall::OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider)
{
	if (_pOtherCollider->GetName() == L"Punch Collider")
		return;

	CObj* otherObj = _pOtherCollider->GetOwner();
	auto otherRigidbody = otherObj->GetComponent<CRigidbody>();

	if (otherRigidbody == nullptr)
		return;

	// 겹치는 영역 계산
	CCollider* otherCollider = _pOtherCollider;

	Vec2 wallLeftTop(m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x / 2, m_WallCollider->GetFinalPos().y - m_WallCollider->GetScale().y / 2);
	Vec2 wallRightBottom(m_WallCollider->GetFinalPos().x + m_WallCollider->GetScale().x / 2, m_WallCollider->GetFinalPos().y + m_WallCollider->GetScale().y / 2);
	Vec2 otherObjLeftTop(otherCollider->GetFinalPos().x - otherCollider->GetScale().x / 2, otherCollider->GetFinalPos().y - otherCollider->GetScale().y / 2);
	Vec2 otherObjRightBottom(otherCollider->GetFinalPos().x + otherCollider->GetScale().x / 2, otherCollider->GetFinalPos().y + otherCollider->GetScale().y / 2);

	// 겹치는 영역의 좌측 상단과 우측 하단 좌표 계산
	Vec2 overlapLeftTop = Vec2(max(wallLeftTop.x, otherObjLeftTop.x), max(wallLeftTop.y, otherObjLeftTop.y));
	Vec2 overlapRightBottom = Vec2(min(wallRightBottom.x, otherObjRightBottom.x), min(wallRightBottom.y, otherObjRightBottom.y));

	// 겹치는 영역 가로 세로 비율 (0 이상)
	float overlapRatio = (overlapRightBottom.y - overlapLeftTop.y) / (overlapRightBottom.x - overlapLeftTop.x);

	// 플레이어 속도 가로 세로 비율 (0 이상)
	float otherVelocityRatio = 0;
	if (otherRigidbody->GetVelocity().y != 0)
		otherVelocityRatio = abs(otherRigidbody->GetVelocity().y / otherRigidbody->GetVelocity().x);



	// 겹치는 영역의 위쪽 y좌표가 플랫폼 위쪽 y좌표와 같으면 위쪽 충돌
	if (overlapLeftTop.y == (m_WallCollider->GetFinalPos().y - m_WallCollider->GetScale().y * 0.5f))
	{
		// 플레이어 속도 비율이 더 완만한 경우 사이드 충돌
		if (otherVelocityRatio < overlapRatio)
		{
			// 좌 충돌
			if (overlapLeftTop.x == (m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x * 0.5f))
				otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
			
			// 우 충돌
			else
				otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
		}

		// 플레이어 속도 비율이 더 가파른 경우 순수하게 상 충돌
		else if (overlapRightBottom.x - overlapLeftTop.x != 0)
		{
			otherObj->SetPos(otherObj->GetPos() - Vec2(0, (overlapRightBottom.y - overlapLeftTop.y)));
		}

	}
	// 겹치는 영역의 아래쪽 y좌표가 플랫폼 아래쪽 y좌표와 같으면 아래쪽 충돌
	else if (overlapRightBottom.y == (m_WallCollider->GetFinalPos().y + m_WallCollider->GetScale().y * 0.5f))
	{
		// 플레이어 속도 비율이 더 완만한 경우 사이드 충돌
		if (otherVelocityRatio < overlapRatio)
		{
			// 좌 충돌
			if (overlapLeftTop.x == (m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x * 0.5f))
				otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));

			// 우 충돌
			else
				otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
		}

		// 플레이어 속도 비율이 더 가파른 경우 순수하게 하 충돌
		else if (overlapRightBottom.x - overlapLeftTop.x != 0)
		{
			otherObj->SetPos(otherObj->GetPos() + Vec2(0, (overlapRightBottom.y - overlapLeftTop.y)));
		}
	}

	// 위 두 조건 다 아니면 순수하게 사이드 충돌
	else
	{
		// 좌 충돌
		if (overlapLeftTop.x == (m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x * 0.5f))
			otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));

		// 우 충돌
		else
			otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
	}

}

void CWall::OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider)
{
	// 예외
	if (_pOtherCollider->GetName() == L"Punch Collider")
		return;

	CObj* otherObj = _pOtherCollider->GetOwner();
	auto otherRigidbody = otherObj->GetComponent<CRigidbody>();

	if (otherRigidbody == nullptr)
		return;

	// 겹치는 영역 계산
	CCollider* otherCollider = _pOtherCollider;

	Vec2 wallLeftTop(m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x / 2, m_WallCollider->GetFinalPos().y - m_WallCollider->GetScale().y / 2);
	Vec2 wallRightBottom(m_WallCollider->GetFinalPos().x + m_WallCollider->GetScale().x / 2, m_WallCollider->GetFinalPos().y + m_WallCollider->GetScale().y / 2);
	Vec2 otherObjLeftTop(otherCollider->GetFinalPos().x - otherCollider->GetScale().x / 2, otherCollider->GetFinalPos().y - otherCollider->GetScale().y / 2);
	Vec2 otherObjRightBottom(otherCollider->GetFinalPos().x + otherCollider->GetScale().x / 2, otherCollider->GetFinalPos().y + otherCollider->GetScale().y / 2);

	// 겹치는 영역의 좌측 상단과 우측 하단 좌표 계산
	Vec2 overlapLeftTop = Vec2(max(wallLeftTop.x, otherObjLeftTop.x), max(wallLeftTop.y, otherObjLeftTop.y));
	Vec2 overlapRightBottom = Vec2(min(wallRightBottom.x, otherObjRightBottom.x), min(wallRightBottom.y, otherObjRightBottom.y));

	// 겹치는 영역 가로 세로 비율 (0 이상)
	float overlapRatio = (overlapRightBottom.y - overlapLeftTop.y) / (overlapRightBottom.x - overlapLeftTop.x);

	// x 방향 속도 0 일 때 (otherVelocityRatio의 분모가 0이되는 경우)
	if (otherRigidbody->GetVelocity().x == 0)
	{

			
	}

	// 플레이어 속도 가로 세로 비율 (0 이상)
	float otherVelocityRatio = 0;
	if (otherRigidbody->GetVelocity().y != 0)
		otherVelocityRatio = abs(otherRigidbody->GetVelocity().y / otherRigidbody->GetVelocity().x);


	// 겹치는 영역의 위쪽 y좌표가 플랫폼 위쪽 y좌표와 같으면 위쪽 충돌
	if (overlapLeftTop.y == (m_WallCollider->GetFinalPos().y - m_WallCollider->GetScale().y * 0.5f))
	{
		// 플레이어 속도 비율이 더 완만한 경우 사이드 충돌
		if (otherVelocityRatio < overlapRatio)
		{
			// 좌 충돌
			if (overlapLeftTop.x == (m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x * 0.5f))
				otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));

			// 우 충돌
			else
				otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
		}

		// 플레이어 속도 비율이 더 가파른 경우 순수하게 상 충돌
		else  if (overlapRightBottom.x - overlapLeftTop.x != 0)
		{
			// !디버그
			auto otherObjPos = otherObj->GetPos();
			auto diff = overlapRightBottom.y - overlapLeftTop.y;
			otherObj->SetPos(otherObj->GetPos() - Vec2(0, (overlapRightBottom.y - overlapLeftTop.y)));
		}

	}
	// 겹치는 영역의 아래쪽 y좌표가 플랫폼 아래쪽 y좌표와 같으면 아래쪽 충돌
	else if (overlapRightBottom.y == (m_WallCollider->GetFinalPos().y + m_WallCollider->GetScale().y * 0.5f))
	{
		// 플레이어 속도 비율이 더 완만한 경우 사이드 충돌
		if (otherVelocityRatio < overlapRatio)
		{
			// 좌 충돌
			if (overlapLeftTop.x == (m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x * 0.5f))
				otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));

			// 우 충돌
			else
				otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
		}

		// 플레이어 속도 비율이 더 가파른 경우 순수하게 하 충돌
		else if (overlapRightBottom.x - overlapLeftTop.x != 0)
		{
			otherObj->SetPos(otherObj->GetPos() + Vec2(0, (overlapRightBottom.y - overlapLeftTop.y)));
		}
	}

	// 위 두 조건 다 아니면 순수하게 사이드 충돌
	else
	{
		// 좌 충돌
		if ((otherCollider->GetFinalPos() - GetPos()).x < 0 )
			otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
		// 우 충돌
		else
			otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
	}


}

void CWall::OnCollisionExit(CCollider* _myCollider, CCollider* _pOtherCollider)
{
}
