#include "pch.h"
#include "CGround.h"

#include "CEngine.h"
#include "CPlayer.h"

CGround::CGround() :
	m_Textrue(nullptr),
	m_GroundCollider{}
{
	m_Textrue = CAssetMgr::GetInstance().LoadTexture(L"Ground_test", L"texture\\Funfair Fever\\main playable\\lv2-1_main_playable_ground_loop.png");

	m_GroundCollider = AddComponent(new CCollider);
	m_GroundCollider->SetOffsetPos(Vec2(0, 0));
	m_GroundCollider->SetScale(Vec2(m_Textrue->GetWidth(), 10));
}

CGround::~CGround()
{
}

void CGround::begin()
{
}

void CGround::tick()
{
}

void CGround::render()
{
	// 오브젝트 위치
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	int Texture_width = m_Textrue->GetWidth();
	int Texture_height = m_Textrue->GetHeight();

	// AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	// 현재 프레임 이미지를 오브젝트 위치에 렌더링
	AlphaBlend(SUBDC,
		(int)(vPos.x - Texture_width / 2.f), (int)(vPos.y - Texture_height / 2.f), Texture_width, Texture_height,
		m_Textrue->GetDC(), 0, 0, Texture_width, Texture_height,
		bf);
}

void CGround::OnCollisionEnter(CCollider* _pOtherCollider)
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

		player->SetPos(player->GetPos() + Vec2(0, -depth));
	}
}

void CGround::OnCollisionStay(CCollider* _pOtherCollider)
{

}

void CGround::OnCollisionExit(CCollider* _pOtherCollider)
{
	if (CPlayer* player = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		auto rigidbody = player->GetComponent<CRigidbody>();
		rigidbody->SetGround(false);
	}
}
