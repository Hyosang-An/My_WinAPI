#include "pch.h"
#include "Onion.h"

#include "CEffect.h"
#include "CMissile.h"

Onion::Onion()
{
	m_iHP = 5;

	m_BodyCollider = AddComponent(new CCollider);
	m_BodyCollider->SetScale(Vec2(250, 400));

	m_Animator = AddComponent(new CAnimator);
}

Onion::~Onion()
{
	Safe_Del_Map(m_mapEffect);
	delete m_TearDrop;
}

void Onion::begin()
{
	LoadAnimation();
	m_Animator->Play(L"veggie_onion_intro_1", false);

	// ÀÌÆåÆ® Ãß°¡
	auto effect = new CEffect;
	effect->SetName(L"veggie_potato_shoot_fx");
	effect->SetAnimation(L"animation\\Boss\\Veggie\\potato\\shoot_fx\\veggie_potato_shoot_fx.anim");
	m_mapEffect.insert(make_pair(effect->GetName(), effect));
}

void Onion::tick()
{
	UpdateState();
	UpdateAnimation();
	MoveAndAction();	
}


void Onion::UpdateState()
{
	if (m_iHP <= 0)
		m_State = STATE::DEATH;

	switch (m_State)
	{
		case STATE::INTRO:
		{
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_onion_intro_2" && m_Animator->IsCurAnimationFinished())
				m_State = STATE::IDLE;
			break;
		}
		case STATE::IDLE:
		{
			m_accIdleTime += DT;
			if (2 < m_accIdleTime && m_Animator->IsCurAnimationFinished())
			{
				m_accIdleTime = 0;
				m_State = STATE::CRY_INTRO;
			}
			break;
		}
		case STATE::CRY_INTRO:
		{
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_onion_cry_intro_2" && m_Animator->IsCurAnimationFinished())
				m_State = STATE::CRY;
			break;
		}
		case STATE::CRY:
		{
			m_accCryTime += DT;
			if (3 < m_accCryTime && m_Animator->IsCurAnimationFinished())
			{
				m_accCryTime = 0;
				m_State = STATE::CRY_OUTRO;
			}
			break;
		}
		case STATE::CRY_OUTRO:
		{
			if (m_Animator->IsCurAnimationFinished())
				m_State = STATE::IDLE;
			break;
		}
		case STATE::DEATH:
		{
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_onion_death_leave_2" && m_Animator->IsCurAnimationFinished())
				SelfDestruct();
			break;
		}
	}
}

void Onion::UpdateAnimation()
{
	switch (m_State)
	{
		case Onion::STATE::INTRO:
		{
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_onion_intro_2")
				return;

			m_Animator->Play(L"veggie_onion_intro_1", false);
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_onion_intro_1" && m_Animator->IsCurAnimationFinished())
				m_Animator->Play(L"veggie_onion_intro_2", false);
	
			break;
		}
		case Onion::STATE::IDLE:
		{
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_onion_idle_2")
			{
				if (m_Animator->IsCurAnimationFinished())
					m_Animator->Play(L"veggie_onion_idle_1", false);
				else
					return;
			}
			else
				m_Animator->Play(L"veggie_onion_idle_1", false);

			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_onion_idle_1" && m_Animator->IsCurAnimationFinished())
				m_Animator->Play(L"veggie_onion_idle_2", false);

			break;
		}
		case Onion::STATE::CRY_INTRO:
		{
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_onion_cry_intro_2")
				return;

			m_Animator->Play(L"veggie_onion_cry_intro_1", false);
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_onion_cry_intro_1" && m_Animator->IsCurAnimationFinished())
				m_Animator->Play(L"veggie_onion_cry_intro_2", false);

			break;
		}
		case Onion::STATE::CRY:
		{
			m_Animator->Play(L"veggie_onion_cry_loop", true, true);
			break;
		}
		case Onion::STATE::CRY_OUTRO:
		{
			m_Animator->Play(L"veggie_onion_cry_outro", false);
			break;
		}
		case Onion::STATE::DEATH:
		{
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_onion_death_leave_2")
				return;

			m_Animator->Play(L"veggie_onion_death_leave_1", false);
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_onion_death_leave_1" && m_Animator->IsCurAnimationFinished())
				m_Animator->Play(L"veggie_onion_death_leave_2", false);

			break;
		}
	}
}

void Onion::MoveAndAction()
{
	if (m_State == STATE::CRY)
	{
		if ((1 / m_DropTearFrequency) < m_acctimeSinceLastTearDrop)
		{
			DropTear();
		}
	}

	m_acctimeSinceLastTearDrop += DT;
}

void Onion::OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider)
{
	CObj* otherObj = _pOtherCollider->GetOwner();
	LAYER_TYPE layer_type = otherObj->GetLayerType();

	if (layer_type == LAYER_TYPE::PLAYER_MISSILE)
	{
		CMissile* player_missile = static_cast<CMissile*>(otherObj);
		m_iHP -= player_missile->GetOffensePower();
		player_missile->SelfDestruct();
	}
}

void Onion::DropTear()
{
	// TODO : ·£´ýÇÑ Áö¿ª¿¡ ´«¹° ½ºÆù
}

void Onion::LoadAnimation()
{
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\intro\\veggie_onion_intro_1.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\intro\\veggie_onion_intro_2.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\idle\\veggie_onion_idle_1.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\idle\\veggie_onion_idle_2.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\cry_intro\\veggie_onion_cry_intro_1.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\cry_intro\\veggie_onion_cry_intro_2.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\cry_loop\\veggie_onion_cry_loop.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\cry_outro\\veggie_onion_cry_outro.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\death\\veggie_onion_death_leave_1.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\death\\veggie_onion_death_leave_2.anim");
}