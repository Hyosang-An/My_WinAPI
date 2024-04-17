#include "pch.h"
#include "Onion_TearDrop.h"


Onion_TearDrop::Onion_TearDrop()
{
	m_fSpeed = 200;
	m_fAngle = PI / 2;

	m_Collider->SetScale(Vec2(30, 30));

	m_Texture = CAssetMgr::GetInstance().LoadTexture(L"Onion_TearDrop", L"animation\\Boss\\Veggie\\onion\\tear_drop\\tear_drop\\veggie_onion_tear_drop_a_0001.png");

	m_Animator = AddComponent(new CAnimator);
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\tear_drop\\tear_drop_death\\veggie_onion_tear_drop_death.anim");
}

Onion_TearDrop::Onion_TearDrop(const Onion_TearDrop& _other) :
	CMissile(_other),
	m_Texture(_other.m_Texture)
{
}

Onion_TearDrop::~Onion_TearDrop()
{
}

void Onion_TearDrop::begin()
{
}

void Onion_TearDrop::tick()
{
	if (m_fSpeed == 0)
	{
		if (m_Animator->IsCurAnimationFinished())
			SelfDestruct();

		return;
	}

	CMissile::tick();

	if (m_Pos.y > 260)
	{
		m_Pos.y = 260;

		m_fSpeed = 0;
		m_Animator->Play(L"veggie_onion_tear_drop_death", false);
		m_bFalling = false;
	}
}

void Onion_TearDrop::render()
{
	if (m_bFalling)
	{
		// 오브젝트 위치
		Vec2 vRenderPos = GetRenderPos();
		Vec2 vScale = GetScale();

		int Texture_width = m_Texture->GetWidth();
		int Texture_height = m_Texture->GetHeight();

		// AlphaBlending
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;

		// 현재 프레임 이미지를 오브젝트 위치에 렌더링
		AlphaBlend(SUBDC,
			(int)(vRenderPos.x - Texture_width / 2.f), (int)(vRenderPos.y - Texture_height / 2.f), Texture_width, Texture_height,
			m_Texture->GetDC(), 0, 0, Texture_width, Texture_height,
			bf);
	}
	else
	{
		m_Animator->render();
	}
}

void Onion_TearDrop::OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider)
{
}

