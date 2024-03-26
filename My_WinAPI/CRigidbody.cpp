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

	// 중력 이외의 외력으로 인한 가속도
	Vec2 AccelWithoutGravity = m_Force / m_fMass;

	// 속도 업데이트
	m_Velocity += AccelWithoutGravity * DT;

	// 최대 속도 제한
	if (m_MaxWalkSpeed !=0 && m_MaxWalkSpeed < m_Velocity.Length())
		m_Velocity = m_Velocity.Normalize() * m_MaxWalkSpeed;

	// 최소 속도 보정
	if (m_MinWalkSpeed != 0 && m_Velocity.Length() < m_MinWalkSpeed && !AccelWithoutGravity.IsZero())
	{
		auto accel = AccelWithoutGravity;
		m_Velocity = accel.Normalize() * m_MinWalkSpeed;
	}

	// 만약 RigidBody 에 적용된 힘이 없으면서, OnGround인데 속도는 있는경우
	// 마찰에 의해서 현재 속도를 줄인다
	if (m_Force.IsZero() && m_OnGround)
	{
		float speed = m_Velocity.Length();

		speed -= m_Friction * DT;

		// 마찰에 의해 속도가 음수가 될 수는 없으므로 예외처리
		if (speed <= 0)
			speed = 0;

		if (!m_Velocity.IsZero())
			m_Velocity.Normalize();

		m_Velocity *= speed;
	}

	// 위치 업데이트
	m_pOwner->SetPos(m_pOwner->GetPos() + m_Velocity * DT);

	// 힘 초기화
	m_Force = Vec2(0, 0);
}
