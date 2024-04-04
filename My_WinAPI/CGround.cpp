#include "pch.h"
#include "CGround.h"

#include "CEngine.h"
#include "CPlayer.h"

int CGround::havePlayerCnt = 0;

CGround::CGround() :
	m_Texture(nullptr),
	m_GroundCollider{}
{
	m_GroundCollider = AddComponent(new CCollider);
}

CGround::CGround(const CGround& _other) :
	m_Texture(_other.m_Texture)
{
	m_GroundCollider = AddComponent(new CCollider(*_other.m_GroundCollider));
}

CGround::~CGround()
{
}

void CGround::SetColliderScale(Vec2 _scale)
{
	m_GroundCollider->SetScale(_scale);
}

void CGround::begin()
{
}

void CGround::tick()
{
}

void CGround::OnCollisionEnter(CCollider* _pOtherCollider)
{
	if (CPlayer* player = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		havePlayerCnt++;

		auto playerRigidbody = player->GetComponent<CRigidbody>();
		if (playerRigidbody->IsOnGround())
			return;

		playerRigidbody->SetGround(true);

		auto playerCollider = _pOtherCollider;

		Vec2 playerColliderPos = playerCollider->GetFinalPos();
		Vec2 playerColliderScale = playerCollider->GetScale();

		Vec2 groundColliderPos = m_GroundCollider->GetFinalPos();
		Vec2 groundColliderScale = m_GroundCollider->GetScale();

		// 파고 들어간 깊이
		float depth = (playerColliderScale.y + groundColliderScale.y) * 0.5 - (groundColliderPos.y - playerColliderPos.y);

		player->SetPos(player->GetPos() + Vec2(0, -depth));
		//playerRigidbody->SetVelocity_Y(0); // y 속도 0는 SetGround가 해줌
	}
}

void CGround::OnCollisionStay(CCollider* _pOtherCollider)
{
	if (CPlayer* player = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		auto playerRigidbody = player->GetComponent<CRigidbody>();

		playerRigidbody->SetGround(true);

		auto playerCollider = _pOtherCollider;

		Vec2 playerColliderPos = playerCollider->GetFinalPos();
		Vec2 playerColliderScale = playerCollider->GetScale();

		Vec2 groundColliderPos = m_GroundCollider->GetFinalPos();
		Vec2 groundColliderScale = m_GroundCollider->GetScale();

		// 파고 들어간 깊이
		float depth = (playerColliderScale.y + groundColliderScale.y) * 0.5 - (groundColliderPos.y - playerColliderPos.y);

		if (depth > 0)
		{
			player->SetPos(player->GetPos() + Vec2(0, -depth));
			//playerRigidbody->SetVelocity_Y(0); // y 속도 0는 SetGround가 해줌
		}
	}
}

void CGround::OnCollisionExit(CCollider* _pOtherCollider)
{
	if (CPlayer* player = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		auto playerRigidbody = player->GetComponent<CRigidbody>();
		if (havePlayerCnt == 1)
			playerRigidbody->SetGround(false);

		havePlayerCnt--;
	}
}
