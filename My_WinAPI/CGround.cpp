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
	CObj* obj = _pOtherCollider->GetOwner();
	if (!obj->m_bUseGroundCollision)
		return;

	obj->m_iGroundCollisionCnt++;

	auto rigidbody = obj->GetComponent<CRigidbody>();

	if (rigidbody == nullptr || obj->m_iGroundCollisionCnt >= 2)
		return;

	rigidbody->SetOnGround(true);

	auto collider = _pOtherCollider;

	Vec2 colliderPos = collider->GetFinalPos();
	Vec2 colliderScale = collider->GetScale();

	Vec2 groundColliderPos = m_GroundCollider->GetFinalPos();
	Vec2 groundColliderScale = m_GroundCollider->GetScale();

	// 파고 들어간 깊이
	float depth = (colliderScale.y + groundColliderScale.y) * 0.5 - (groundColliderPos.y - colliderPos.y);

	obj->SetPos(obj->GetPos() + Vec2(0, -depth));
}

void CGround::OnCollisionStay(CCollider* _pOtherCollider)
{

	CObj* obj = _pOtherCollider->GetOwner();
	if (!obj->m_bUseGroundCollision)
		return;

	auto rigidbody = obj->GetComponent<CRigidbody>();

	if (rigidbody == nullptr || obj->m_iGroundCollisionCnt >= 2)
		return;

	// 이미 OnGround 상태면 SetOnGround(true) 해도 내부에서 바로 return
	rigidbody->SetOnGround(true);

	auto collider = _pOtherCollider;

	Vec2 colliderPos = collider->GetFinalPos();
	Vec2 colliderScale = collider->GetScale();

	Vec2 groundColliderPos = m_GroundCollider->GetFinalPos();
	Vec2 groundColliderScale = m_GroundCollider->GetScale();

	// 파고 들어간 깊이
	float depth = (colliderScale.y + groundColliderScale.y) * 0.5 - (groundColliderPos.y - colliderPos.y);

	obj->SetPos(obj->GetPos() + Vec2(0, -depth));
}

void CGround::OnCollisionExit(CCollider* _pOtherCollider)
{
	CObj* obj = _pOtherCollider->GetOwner();
	if (!obj->m_bUseGroundCollision)
		return;

	obj->m_iGroundCollisionCnt--;

	auto rigidbody = obj->GetComponent<CRigidbody>();
	if (rigidbody == nullptr || obj->m_iGroundCollisionCnt >= 1)
		return;

	rigidbody->SetOnGround(false);
}
