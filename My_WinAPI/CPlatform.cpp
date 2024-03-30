#include "pch.h"
#include "CPlatform.h"

CPlatform::CPlatform()
{
	SetScale(Vec2(500, 100));
	m_PlatformCollider = AddComponent(new CCollider);
	m_PlatformCollider->SetScale(GetScale());
}

CPlatform::~CPlatform()
{
}

void CPlatform::tick()
{
}

void CPlatform::OnCollisionEnter(CCollider* _pOwnCollider, CCollider* _pOtherCollider)
{
	auto otherObj = _pOtherCollider->GetOwner();
	if (otherObj->GetLayerType() == LAYER_TYPE::PLAYER)
	{
		auto rigidbody = otherObj->GetComponent<CRigidbody>();
		rigidbody->SetGround(true);
	}
}

void CPlatform::OnCollisionStay(CCollider* _pOwnCollider, CCollider* _pOtherCollider)
{
}

void CPlatform::OnCollisionExit(CCollider* _pOwnCollider, CCollider* _pOtherCollider)
{
	auto otherObj = _pOtherCollider->GetOwner();
	if (otherObj->GetLayerType() == LAYER_TYPE::PLAYER)
	{
		auto rigidbody = otherObj->GetComponent<CRigidbody>();
		rigidbody->SetGround(false);
	}
}

