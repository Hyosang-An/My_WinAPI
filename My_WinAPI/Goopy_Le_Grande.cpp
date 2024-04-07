#include "pch.h"
#include "Goopy_Le_Grande.h"

Goopy_Le_Grande::Goopy_Le_Grande()
{
	SetName(L"Goopy Le Grande");

	m_Rigidbody = AddComponent(new CRigidbody);
	// 콜백함수 설정
	m_Rigidbody->SetGroundCallbackFunc([this]() {this->EnterGround(); });
	m_Rigidbody->SetAirCallbackFunc([this]() {this->LeaveGround(); });

	m_BodyCollider = AddComponent(new CCollider);

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
}

void Goopy_Le_Grande::tick()
{
}

void Goopy_Le_Grande::render()
{
}

void Goopy_Le_Grande::LoadAnimation()
{
	// 1페이즈 
	// L
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Intro\\slime_intro_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Down\\slime_air_down_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Up\\slime_air_up_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Jump\\slime_jump_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Punch\\slime_jump_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_1_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_2_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Up Down Transition\\slime_up_down_trans_L.anim");

	// R
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Down\\slime_air_down_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Up\\slime_air_up_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Jump\\slime_jump_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Punch\\slime_jump_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_1_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_2_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Up Down Transition\\slime_up_down_trans_R.anim");
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

