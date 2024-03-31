#include "pch.h"
#include "CPlatform.h"
#include "CPlayer.h"

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
		CPlayer* player = static_cast<CPlayer*>(otherObj);
		auto rigidbody = player->GetComponent<CRigidbody>();

		rigidbody->SetGround(true);
		player->SetOnPlatform(true);
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
		CPlayer* player = static_cast<CPlayer*>(otherObj);
		auto rigidbody = player->GetComponent<CRigidbody>();

		rigidbody->SetGround(false);
		player->SetOnPlatform(false);
	}
}

