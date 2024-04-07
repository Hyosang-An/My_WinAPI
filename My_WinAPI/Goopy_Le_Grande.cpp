#include "pch.h"
#include "Goopy_Le_Grande.h"

Goopy_Le_Grande::Goopy_Le_Grande()
{
	SetName(L"Goopy Le Grande");

	m_Rigidbody = AddComponent(new CRigidbody);
	// 콜백함수 설정
	m_Rigidbody->SetGroundCallbackFunc([this]() {this->EnterGround(); });
	m_Rigidbody->SetAirCallbackFunc([this]() {this->LeaveGround(); });

	// 애니메이터 설정
	m_Animator = AddComponent(new CAnimator);

	m_BodyCollider = AddComponent(new CCollider);
	m_BodyCollider->SetScale(Vec2(150, 200));

	m_PunchCollider = AddComponent(new CCollider);
	m_PunchCollider->SetActive(false);

	m_SmashCollider = AddComponent(new CCollider);
	m_SmashCollider->SetActive(false);
}

Goopy_Le_Grande::~Goopy_Le_Grande()
{
}

void Goopy_Le_Grande::begin()
{
	LoadAnimation();
	m_Animator->Play(L"slime_intro_L", false);
}

void Goopy_Le_Grande::tick()
{
	UpdateState();
	MoveAndAction();
	UpdateAnimation();
}

void Goopy_Le_Grande::UpdateState()
{
}

void Goopy_Le_Grande::MoveAndAction()
{
}

void Goopy_Le_Grande::UpdateAnimation()
{
}

void Goopy_Le_Grande::render()
{
	auto curAnim = m_Animator->GetCurAnimation();

	// 현재 프레임 정보
	const tAnimationFrame& frm = curAnim->GetCurFrame();

	// 애니메이션을 재생하고 있는 오브젝트
	CObj* pOwnerObj = m_Animator->GetOwner();

	// 오브젝트 위치
	Vec2 vRenderPos = pOwnerObj->GetRenderPos();

	const float ALPHA_MAX = 255.f;

	// AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)ALPHA_MAX;
	bf.AlphaFormat = AC_SRC_ALPHA;

	// 현재 프레임 이미지를 오브젝트 위치에 렌더링
	AlphaBlend(SUBDC,
		(int)(vRenderPos.x - frm.SliceSize.x / 2.f + frm.Offset.x), (int)(vRenderPos.y - frm.SliceSize.y / 2.f + frm.Offset.y), (int)frm.SliceSize.x, (int)frm.SliceSize.y,
		curAnim->GetAtlasDC(), (int)frm.PosInAtlas.x, (int)frm.PosInAtlas.y, (int)frm.SliceSize.x, (int)frm.SliceSize.y,
		bf);
}



void Goopy_Le_Grande::LoadAnimation()
{
	// 1페이즈 
	// L
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Intro\\slime_intro_L.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Down\\slime_air_down_L.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Up\\slime_air_up_L.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Jump\\slime_jump_L.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Punch\\slime_jump_L.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_1_L.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_2_L.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Up Down Transition\\slime_up_down_trans_L.anim");

	//// R
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Down\\slime_air_down_R.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Up\\slime_air_up_R.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Jump\\slime_jump_R.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Punch\\slime_jump_R.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_1_R.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_2_R.anim");
	//m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Up Down Transition\\slime_up_down_trans_R.anim");

	// VFX
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Dust\\A\\lg_slime_dust_a.anim");
}

void Goopy_Le_Grande::EnterGround()
{
}

void Goopy_Le_Grande::LeaveGround()
{
}

void Goopy_Le_Grande::OnCollisionEnter(CCollider* _pOtherCollider)
{
}

void Goopy_Le_Grande::OnCollisionStay(CCollider* _pOtherCollider)
{
}

void Goopy_Le_Grande::OnCollisionExit(CCollider* _pOtherCollider)
{
}

