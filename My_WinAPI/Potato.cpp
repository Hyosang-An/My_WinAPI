#include "pch.h"
#include "Potato.h"

#include "Potato_Shot.h"

Potato::Potato()
{
	m_iHP = 5;

	m_BodyCollider = AddComponent(new CCollider);
	m_BodyCollider->SetScale(Vec2(200, 500));

	m_Animator = AddComponent(new CAnimator);

	m_Shot = new Potato_Shot;
}

Potato::~Potato()
{
	Safe_Del_Map(m_mapEffect);
	delete m_Shot;
}



void Potato::begin()
{
	LoadAnimation();

	// 이펙트 추가
	auto effect = new CEffect;
	effect->SetName(L"veggie_potato_shoot_fx");
	effect->SetAnimation(L"animation\\Boss\\Veggie\\potato\\shoot_fx\\veggie_potato_shoot_fx.anim");
	m_mapEffect.insert(make_pair(effect->GetName(), effect));

	m_Shot->SetPos(m_Pos + Vec2(-200, 100));
}

void Potato::tick()
{
	UpdateState();
	UpdateAnimation();
	MoveAndAction();
}



void Potato::UpdateState()
{
	if (m_iHP <= 0)
		m_State = STATE::DEATH;

	switch (m_State)
	{
		case Potato::STATE::INTRO:
		{
			if (m_Animator->IsCurAnimationFinished())
				m_State = STATE::IDLE;
			break;
		}
		case Potato::STATE::IDLE:
		{
			m_accIdleTime += DT;
			if (2 < m_accIdleTime && m_Animator->IsCurAnimationFinished())
			{
				m_accIdleTime = 0;
				m_State = STATE::SHOOT;
			}
			break;
		}
		case Potato::STATE::SHOOT:
		{
			if (m_numberShotsRemaining == 0 && m_Animator->IsCurAnimationFinished())
			{
				m_numberShotsRemaining = 4;
				m_State = STATE::IDLE;
			}
			break;
		}
		case Potato::STATE::DEATH:
		{
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_potato_leave" && m_Animator->IsCurAnimationFinished())
				SelfDestruct();
			break;
		}
	}
}

void Potato::UpdateAnimation()
{
	switch (m_State)
	{
		case Potato::STATE::INTRO:
			m_Animator->Play(L"veggie_potato_intro", false);
			break;
		case Potato::STATE::IDLE:
			m_Animator->Play(L"veggie_potato_idle", true, true);
			break;
		case Potato::STATE::SHOOT:
			m_Animator->Play(L"veggie_potato_shoot", true);
			break;
		case Potato::STATE::DEATH:
		{
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_potato_leave")
				return;

			m_Animator->Play(L"veggie_potato_death", true);
			if (m_Animator->GetCurAnimation()->GetName() == L"veggie_potato_death" && m_Animator->IsCurAnimationFinished())
				m_Animator->Play(L"veggie_potato_leave", false);
			break;
		}
	}
}

void Potato::MoveAndAction()
{
	if (m_State == STATE::SHOOT)
	{
		if (m_Animator->GetCurAnimationFrmIdx() == 12 && m_ShootFlag == false)
		{
			m_ShootFlag = true;
			m_numberShotsRemaining--;
			Shoot();
		}
		else if (m_Animator->GetCurAnimationFrmIdx() != 12)
			m_ShootFlag = false;
	}
}

void Potato::SpawnEffect(const wstring& _effectName, Vec2 _pos)
{
	// Clone 전용 원본 이펙트
	auto iter = m_mapEffect.find(_effectName);
	if (iter == m_mapEffect.end())
	{
		wstring msg = _effectName + L"해당 이름의 이펙트 없음";
		LOG(LOG_TYPE::DBG_ERROR, msg.c_str());
		return;
	}

	// 원본을 리턴하면 곤란.
	auto effect_clone = iter->second->Clone();

	effect_clone->SetPos(_pos);

	SpawnObject(LAYER_TYPE::EFFECT, effect_clone);
}

void Potato::OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider)
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

void Potato::Shoot()
{
	auto shot_clone = m_Shot->Clone();
	SpawnObject(LAYER_TYPE::ENEMY_MISSILE, shot_clone);

	SpawnEffect(L"veggie_potato_shoot_fx", m_Pos + Vec2(-300, 120));
}

void Potato::LoadAnimation()
{
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\potato\\intro\\veggie_potato_intro.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\potato\\death\\veggie_potato_death.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\potato\\idle\\veggie_potato_idle.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\potato\\leave\\veggie_potato_leave.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\potato\\shoot\\veggie_potato_shoot.anim");
}

