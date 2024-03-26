#include "pch.h"
#include "CRigidbody.h"

CRigidbody::CRigidbody() :
	m_fMass(1),
	m_GravityAccel(100),
	m_Friction(10000),
	m_MinWalkSpeed(90),
	m_MaxWalkSpeed(200),
	m_MaxGravitySpeed(500),
	m_UseGravity(false),
	m_OnGround(true),
	m_JumpSpeed(400)
{
}

CRigidbody::~CRigidbody()
{
}



void CRigidbody::finaltick()
{

	// �߷� �̿��� �ܷ����� ���� ���ӵ�
	Vec2 AccelWithoutGravity = m_Force / m_fMass;

	// �ӵ� ������Ʈ
	m_Velocity += AccelWithoutGravity * DT;

	// �ִ� �ӵ� ����
	if (m_MaxWalkSpeed !=0 && m_MaxWalkSpeed < m_Velocity.Length())
		m_Velocity = m_Velocity.Normalize() * m_MaxWalkSpeed;

	// �ּ� �ӵ� ����
	if (m_MinWalkSpeed != 0 && m_Velocity.Length() < m_MinWalkSpeed && !AccelWithoutGravity.IsZero())
	{
		auto accel = AccelWithoutGravity;
		m_Velocity = accel.Normalize() * m_MinWalkSpeed;
	}

	// ���� RigidBody �� ����� ���� �����鼭, OnGround�ε� �ӵ��� �ִ°��
	// ������ ���ؼ� ���� �ӵ��� ���δ�
	if (m_Force.IsZero() && m_OnGround)
	{
		float speed = m_Velocity.Length();

		speed -= m_Friction * DT;

		// ������ ���� �ӵ��� ������ �� ���� �����Ƿ� ����ó��
		if (speed <= 0)
			speed = 0;

		if (!m_Velocity.IsZero())
			m_Velocity.Normalize();

		m_Velocity *= speed;
	}

	// ��ġ ������Ʈ
	m_pOwner->SetPos(m_pOwner->GetPos() + m_Velocity * DT);

	// �� �ʱ�ȭ
	m_Force = Vec2(0, 0);
}
