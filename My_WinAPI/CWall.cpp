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

	// ��ġ�� ���� ���
	CCollider* otherCollider = _pOtherCollider;

	Vec2 wallLeftTop(m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x / 2, m_WallCollider->GetFinalPos().y - m_WallCollider->GetScale().y / 2);
	Vec2 wallRightBottom(m_WallCollider->GetFinalPos().x + m_WallCollider->GetScale().x / 2, m_WallCollider->GetFinalPos().y + m_WallCollider->GetScale().y / 2);
	Vec2 otherObjLeftTop(otherCollider->GetFinalPos().x - otherCollider->GetScale().x / 2, otherCollider->GetFinalPos().y - otherCollider->GetScale().y / 2);
	Vec2 otherObjRightBottom(otherCollider->GetFinalPos().x + otherCollider->GetScale().x / 2, otherCollider->GetFinalPos().y + otherCollider->GetScale().y / 2);

	// ��ġ�� ������ ���� ��ܰ� ���� �ϴ� ��ǥ ���
	Vec2 overlapLeftTop = Vec2(max(wallLeftTop.x, otherObjLeftTop.x), max(wallLeftTop.y, otherObjLeftTop.y));
	Vec2 overlapRightBottom = Vec2(min(wallRightBottom.x, otherObjRightBottom.x), min(wallRightBottom.y, otherObjRightBottom.y));

	// ��ġ�� ���� ���� ���� ���� (0 �̻�)
	float overlapRatio = (overlapRightBottom.y - overlapLeftTop.y) / (overlapRightBottom.x - overlapLeftTop.x);

	// �÷��̾� �ӵ� ���� ���� ���� (0 �̻�)
	float otherVelocityRatio = 0;
	if (otherRigidbody->GetVelocity().y != 0)
		otherVelocityRatio = abs(otherRigidbody->GetVelocity().y / otherRigidbody->GetVelocity().x);



	// ��ġ�� ������ ���� y��ǥ�� �÷��� ���� y��ǥ�� ������ ���� �浹
	if (overlapLeftTop.y == (m_WallCollider->GetFinalPos().y - m_WallCollider->GetScale().y * 0.5f))
	{
		// �÷��̾� �ӵ� ������ �� �ϸ��� ��� ���̵� �浹
		if (otherVelocityRatio < overlapRatio)
		{
			// �� �浹
			if (overlapLeftTop.x == (m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x * 0.5f))
				otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
			
			// �� �浹
			else
				otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
		}

		// �÷��̾� �ӵ� ������ �� ���ĸ� ��� �����ϰ� �� �浹
		else if (overlapRightBottom.x - overlapLeftTop.x != 0)
		{
			otherObj->SetPos(otherObj->GetPos() - Vec2(0, (overlapRightBottom.y - overlapLeftTop.y)));
		}

	}
	// ��ġ�� ������ �Ʒ��� y��ǥ�� �÷��� �Ʒ��� y��ǥ�� ������ �Ʒ��� �浹
	else if (overlapRightBottom.y == (m_WallCollider->GetFinalPos().y + m_WallCollider->GetScale().y * 0.5f))
	{
		// �÷��̾� �ӵ� ������ �� �ϸ��� ��� ���̵� �浹
		if (otherVelocityRatio < overlapRatio)
		{
			// �� �浹
			if (overlapLeftTop.x == (m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x * 0.5f))
				otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));

			// �� �浹
			else
				otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
		}

		// �÷��̾� �ӵ� ������ �� ���ĸ� ��� �����ϰ� �� �浹
		else if (overlapRightBottom.x - overlapLeftTop.x != 0)
		{
			otherObj->SetPos(otherObj->GetPos() + Vec2(0, (overlapRightBottom.y - overlapLeftTop.y)));
		}
	}

	// �� �� ���� �� �ƴϸ� �����ϰ� ���̵� �浹
	else
	{
		// �� �浹
		if (overlapLeftTop.x == (m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x * 0.5f))
			otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));

		// �� �浹
		else
			otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
	}

}

void CWall::OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider)
{
	// ����
	if (_pOtherCollider->GetName() == L"Punch Collider")
		return;

	CObj* otherObj = _pOtherCollider->GetOwner();
	auto otherRigidbody = otherObj->GetComponent<CRigidbody>();

	if (otherRigidbody == nullptr)
		return;

	// ��ġ�� ���� ���
	CCollider* otherCollider = _pOtherCollider;

	Vec2 wallLeftTop(m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x / 2, m_WallCollider->GetFinalPos().y - m_WallCollider->GetScale().y / 2);
	Vec2 wallRightBottom(m_WallCollider->GetFinalPos().x + m_WallCollider->GetScale().x / 2, m_WallCollider->GetFinalPos().y + m_WallCollider->GetScale().y / 2);
	Vec2 otherObjLeftTop(otherCollider->GetFinalPos().x - otherCollider->GetScale().x / 2, otherCollider->GetFinalPos().y - otherCollider->GetScale().y / 2);
	Vec2 otherObjRightBottom(otherCollider->GetFinalPos().x + otherCollider->GetScale().x / 2, otherCollider->GetFinalPos().y + otherCollider->GetScale().y / 2);

	// ��ġ�� ������ ���� ��ܰ� ���� �ϴ� ��ǥ ���
	Vec2 overlapLeftTop = Vec2(max(wallLeftTop.x, otherObjLeftTop.x), max(wallLeftTop.y, otherObjLeftTop.y));
	Vec2 overlapRightBottom = Vec2(min(wallRightBottom.x, otherObjRightBottom.x), min(wallRightBottom.y, otherObjRightBottom.y));

	// ��ġ�� ���� ���� ���� ���� (0 �̻�)
	float overlapRatio = (overlapRightBottom.y - overlapLeftTop.y) / (overlapRightBottom.x - overlapLeftTop.x);

	// x ���� �ӵ� 0 �� �� (otherVelocityRatio�� �и� 0�̵Ǵ� ���)
	if (otherRigidbody->GetVelocity().x == 0)
	{

			
	}

	// �÷��̾� �ӵ� ���� ���� ���� (0 �̻�)
	float otherVelocityRatio = 0;
	if (otherRigidbody->GetVelocity().y != 0)
		otherVelocityRatio = abs(otherRigidbody->GetVelocity().y / otherRigidbody->GetVelocity().x);


	// ��ġ�� ������ ���� y��ǥ�� �÷��� ���� y��ǥ�� ������ ���� �浹
	if (overlapLeftTop.y == (m_WallCollider->GetFinalPos().y - m_WallCollider->GetScale().y * 0.5f))
	{
		// �÷��̾� �ӵ� ������ �� �ϸ��� ��� ���̵� �浹
		if (otherVelocityRatio < overlapRatio)
		{
			// �� �浹
			if (overlapLeftTop.x == (m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x * 0.5f))
				otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));

			// �� �浹
			else
				otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
		}

		// �÷��̾� �ӵ� ������ �� ���ĸ� ��� �����ϰ� �� �浹
		else  if (overlapRightBottom.x - overlapLeftTop.x != 0)
		{
			// !�����
			auto otherObjPos = otherObj->GetPos();
			auto diff = overlapRightBottom.y - overlapLeftTop.y;
			otherObj->SetPos(otherObj->GetPos() - Vec2(0, (overlapRightBottom.y - overlapLeftTop.y)));
		}

	}
	// ��ġ�� ������ �Ʒ��� y��ǥ�� �÷��� �Ʒ��� y��ǥ�� ������ �Ʒ��� �浹
	else if (overlapRightBottom.y == (m_WallCollider->GetFinalPos().y + m_WallCollider->GetScale().y * 0.5f))
	{
		// �÷��̾� �ӵ� ������ �� �ϸ��� ��� ���̵� �浹
		if (otherVelocityRatio < overlapRatio)
		{
			// �� �浹
			if (overlapLeftTop.x == (m_WallCollider->GetFinalPos().x - m_WallCollider->GetScale().x * 0.5f))
				otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));

			// �� �浹
			else
				otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
		}

		// �÷��̾� �ӵ� ������ �� ���ĸ� ��� �����ϰ� �� �浹
		else if (overlapRightBottom.x - overlapLeftTop.x != 0)
		{
			otherObj->SetPos(otherObj->GetPos() + Vec2(0, (overlapRightBottom.y - overlapLeftTop.y)));
		}
	}

	// �� �� ���� �� �ƴϸ� �����ϰ� ���̵� �浹
	else
	{
		// �� �浹
		if ((otherCollider->GetFinalPos() - GetPos()).x < 0 )
			otherObj->SetPos(otherObj->GetPos() - Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
		// �� �浹
		else
			otherObj->SetPos(otherObj->GetPos() + Vec2((overlapRightBottom.x - overlapLeftTop.x), 0));
	}


}

void CWall::OnCollisionExit(CCollider* _myCollider, CCollider* _pOtherCollider)
{
}
