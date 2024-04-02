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
	// 이전 상태와 같으면 그냥 리턴
	if (m_OnGround == _b)
		return;

	// 이전 상태와 다른 경우

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

	// 중력 이외의 외력으로 인한 가속도
	Vec2 AccelWithoutGravity = m_Force / m_fMass;

	// 속도 업데이트
	m_Velocity += AccelWithoutGravity * DT;

	// 플레이어 좌우 running 속도 제한
	// 플레이어면서 대쉬모드가 아닌 경우
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
	// 플레이어면서 대쉬모드일 때
	else
	{
		if (m_maxDashSpeed < m_Velocity.Length())
			m_Velocity = m_Velocity.Normalize() * m_maxDashSpeed;
	}

	 // 마찰 적용
	 // 만약 RigidBody 에 적용된 힘이 없으면서, OnGround인데 속도는 있는경우
	 // 마찰에 의해서 현재 속도를 줄인다
	//if (m_Force.IsZero() && m_OnGround)
	//{
	//	float speed = m_Velocity.Length();

	//	speed -= m_Friction * DT;

	//	// 마찰에 의해 속도가 음수가 될 수는 없으므로 예외처리
	//	if (speed <= 0)
	//		speed = 0;

	//	if (!m_Velocity.IsZero())
	//		m_Velocity.Normalize();

	//	m_Velocity *= speed;
	//}

	// 중력 적용 ( 중력 사용상태이면서 OnGround일 때 )
	if (m_UseGravity && !m_OnGround)
	{
		m_Velocity += Vec2(0, m_GravityAccel) * DT;
		
		if (m_MaxGravitySpeed != 0 && m_Velocity.y > m_MaxGravitySpeed)
			m_Velocity.y = m_MaxGravitySpeed;
	}

	// 위치 업데이트
	auto objPos = m_Owner->GetPos();
	m_Owner->SetPos(objPos + m_Velocity * DT);

	// DebugRender
	DrawDebugLine(PEN_TYPE::BLUE, objPos, objPos + m_Velocity, 0.f);

	// 힘 초기화
	m_Force = Vec2(0, 0);
}
