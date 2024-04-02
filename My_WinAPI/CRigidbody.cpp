#include "pch.h"
#include "CRigidbody.h"

#include "CPlayer.h"

CRigidbody::CRigidbody() :
	m_fMass(1),
	m_GravityAccel(450),
	m_Friction(0),
	m_MaxWalkSpeed(0),
	m_MaxGravitySpeed(800),
	m_UseGravity(true),
	m_OnGround(false),
	m_maxDashSpeed(400)
{

}

CRigidbody::CRigidbody(const CRigidbody& _other) :
	CComponent(_other),
	m_fMass(_other.m_fMass),

	m_GravityAccel(_other.m_GravityAccel),

	m_Friction(_other.m_Friction),

	m_MaxWalkSpeed(_other.m_MaxWalkSpeed),
	m_MaxGravitySpeed(_other.m_MaxGravitySpeed),
	m_UseGravity(_other.m_UseGravity),
	m_OnGround(_other.m_OnGround),
	m_GroundCallbackFunc(nullptr),
	m_AirCallbackFunc(nullptr),
	m_maxDashSpeed(_other.m_maxDashSpeed)
{
}

CRigidbody::~CRigidbody()
{
}



void CRigidbody::SetGround(bool _b)
{
	// ���� ���¿� ������ �׳� ����
	if (m_OnGround == _b)
		return;

	// ���� ���¿� �ٸ� ���

	m_OnGround = _b;

	if (m_OnGround)
	{
		m_Velocity.y = 0;

		if (m_GroundCallbackFunc)
			m_GroundCallbackFunc();
	}
	else
	{
		if (m_AirCallbackFunc)
			m_AirCallbackFunc();
	}
}

void CRigidbody::finaltick()
{

	// �߷� �̿��� �ܷ����� ���� ���ӵ�
	Vec2 AccelWithoutGravity = m_Force / m_fMass;

	// �ӵ� ������Ʈ
	m_Velocity += AccelWithoutGravity * DT;

	// �÷��̾� �¿� running �ӵ� ����
	// �÷��̾�鼭 �뽬��尡 �ƴ� ���
	auto player = dynamic_cast<CPlayer*>(m_Owner);
	if (!(player != nullptr && player->GetBaseState() == BASE_STATE::DASH))
	{
		if (m_MaxWalkSpeed != 0 && m_MaxWalkSpeed < abs(m_Velocity.x))
		{
			if (m_Velocity.x < 0)
				m_Velocity.x = -m_MaxWalkSpeed;
			else
				m_Velocity.x = m_MaxWalkSpeed;
		}
		
	}
	// �÷��̾�鼭 �뽬����� ��
	else
	{
		if (m_maxDashSpeed < m_Velocity.Length())
			m_Velocity = m_Velocity.Normalize() * m_maxDashSpeed;
	}

	 // ���� ����
	 // ���� RigidBody �� ����� ���� �����鼭, OnGround�ε� �ӵ��� �ִ°��
	 // ������ ���ؼ� ���� �ӵ��� ���δ�
	//if (m_Force.IsZero() && m_OnGround)
	//{
	//	float speed = m_Velocity.Length();

	//	speed -= m_Friction * DT;

	//	// ������ ���� �ӵ��� ������ �� ���� �����Ƿ� ����ó��
	//	if (speed <= 0)
	//		speed = 0;

	//	if (!m_Velocity.IsZero())
	//		m_Velocity.Normalize();

	//	m_Velocity *= speed;
	//}

	// �߷� ���� ( �߷� �������̸鼭 OnGround�� �� )
	if (m_UseGravity && !m_OnGround)
	{
		m_Velocity += Vec2(0, m_GravityAccel) * DT;
		
		if (m_MaxGravitySpeed != 0 && m_Velocity.y > m_MaxGravitySpeed)
			m_Velocity.y = m_MaxGravitySpeed;
	}

	// ��ġ ������Ʈ
	auto objPos = m_Owner->GetPos();
	m_Owner->SetPos(objPos + m_Velocity * DT);

	// DebugRender
	DrawDebugLine(PEN_TYPE::BLUE, objPos, objPos + m_Velocity, 0.f);

	// �� �ʱ�ȭ
	m_Force = Vec2(0, 0);
}
