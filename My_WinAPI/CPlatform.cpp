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

void CPlatform::OnCollisionEnter(CCollider* _pOtherCollider)
{
	if (CPlayer* player = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		// 플랫폼 위 쪽에서 들어오는게 아니면 리턴
		CRigidbody* playerRigidbody = player->GetComponent<CRigidbody>();
		if (playerRigidbody->GetVelocity().y < 0)
			return;


		// 겹치는 영역 계산
		CCollider* playerCollider = _pOtherCollider;

		Vec2 platformLeftTop(m_PlatformCollider->GetFinalPos().x - m_PlatformCollider->GetScale().x / 2, m_PlatformCollider->GetFinalPos().y - m_PlatformCollider->GetScale().y / 2);
		Vec2 platformRightBottom(m_PlatformCollider->GetFinalPos().x + m_PlatformCollider->GetScale().x / 2, m_PlatformCollider->GetFinalPos().y + m_PlatformCollider->GetScale().y / 2);
		Vec2 playerLeftTop(playerCollider->GetFinalPos().x - playerCollider->GetScale().x / 2, playerCollider->GetFinalPos().y - playerCollider->GetScale().y / 2);
		Vec2 playerRightBottom(playerCollider->GetFinalPos().x + playerCollider->GetScale().x / 2, playerCollider->GetFinalPos().y + playerCollider->GetScale().y / 2);

		// 겹치는 영역의 좌측 상단과 우측 하단 좌표 계산
		Vec2 overlapLeftTop = Vec2(max(platformLeftTop.x, playerLeftTop.x), max(platformLeftTop.y, playerLeftTop.y));
		Vec2 overlapRightBottom = Vec2(min(platformRightBottom.x, playerRightBottom.x), min(platformRightBottom.y, playerRightBottom.y));

		// 겹치는 영역 가로 세로 비율 (0 이상)
		float overlapRatio = (overlapRightBottom.y - overlapLeftTop.y) / (overlapRightBottom.x - overlapLeftTop.x);

		// 플레이어 속도 가로 세로 비율 (0 이상)
		float playerVelocityRatio = abs(playerRigidbody->GetVelocity().y / playerRigidbody->GetVelocity().x);

		// 플레이어 속도 비율이 더 완만한 경우 리턴
		if (playerVelocityRatio < overlapRatio)
			return;

		playerRigidbody->SetGround(true);
		player->SetOnPlatform(true);
	}
}

void CPlatform::OnCollisionStay(CCollider* _pOtherCollider)
{

}

void CPlatform::OnCollisionExit(CCollider* _pOtherCollider)
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

