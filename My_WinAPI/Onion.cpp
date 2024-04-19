#include "pch.h"
#include "Onion.h"

#include "CEffect.h"
#include "CMissile.h"
#include "Onion_TearDrop.h"
#include "CRandomMgr.h"

Onion::Onion()
{
	m_iHP = 5;

	m_BodyCollider = AddComponent(new CCollider);
	m_BodyCollider->SetScale(Vec2(250, 400));

	m_Animator = AddComponent(new CAnimator);

	// TearDrop
	m_TearDrop = new Onion_TearDrop;
}

Onion::~Onion()
{
	Safe_Del_Map(m_mapEffect);
	delete m_TearDrop;
	m_Onion_TearLoop->SelfDestruct();
}

void Onion::begin()
{
	LoadAnimation();
	m_Animator->Play(L"veggie_onion_intro_1", false);

	// TearLoop 이펙트 설정
	m_Onion_TearLoop = new Onion_TearLoop;
	m_Onion_TearLoop->SetPos(Vec2(0, -322));
	SpawnObject(LAYER_TYPE::EFFECT, m_Onion_TearLoop);



	// 이펙트 추가
	auto effect = new CEffect;
	effect->SetName(L"veggie_onion_tears_intro_L");
	effect->SetAnimation(L"animation\\Boss\\Veggie\\onion\\tears\\L\\intro\\veggie_onion_tears_intro_L.anim");
	m_mapEffect.insert(make_pair(effect->GetName(), effect));

	effect = new CEffect;
	effect->SetName(L"veggie_onion_tears_outro_L");
	effect->SetAnimation(L"animation\\Boss\\Veggie\\onion\\tears\\L\\outro\\veggie_onion_tears_outro_L.anim");
	m_mapEffect.insert(make_pair(effect->GetName(), effect));



	effect = new CEffect;
	effect->SetName(L"veggie_onion_tears_intro_R");
	effect->SetAnimation(L"animation\\Boss\\Veggie\\onion\\tears\\R\\intro\\veggie_onion_tears_intro_R.anim");
	m_mapEffect.insert(make_pair(effect->GetName(), effect));

	effect = new CEffect;
	effect->SetName(L"veggie_onion_tears_outro_R");
	effect->SetAnimation(L"animation\\Boss\\Veggie\\onion\\tears\\R\\outro\\veggie_onion_tears_outro_R.anim");
	m_mapEffect.insert(make_pair(effect->GetName(), effect));

	effect = new CEffect;
	effect->SetName(L"boss_explosion");
	effect->SetAnimation(L"animation\\Boss\\boss_explosion\\boss_explosion.anim");
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
			{
				m_State = STATE::CRY;


				SpawnEffect(L"veggie_onion_tears_intro_L", Vec2(-90, -156));
				SpawnEffect(L"veggie_onion_tears_intro_R", Vec2(90, -156));
			}
			break;
		}
		case STATE::CRY:
		{
			m_accCryTime += DT;

			if (0.4 < m_accCryTime && !m_Onion_TearLoop->IsActive())
			{
				m_Onion_TearLoop->Start();
			}

			if (3 < m_accCryTime && m_Animator->IsCurAnimationFinished())
			{
				m_accCryTime = 0;
				m_State = STATE::CRY_OUTRO;

				m_Onion_TearLoop->Stop();

				SpawnEffect(L"veggie_onion_tears_outro_L", Vec2(-316, -253));
				SpawnEffect(L"veggie_onion_tears_outro_R", Vec2(316, -253));
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
			m_accTimeSinceLastExplosionFX += DT;
			if (1 / m_ExplosionFX_Frequency < m_accTimeSinceLastExplosionFX)
			{
				m_accTimeSinceLastExplosionFX = 0;
				auto posX = CRandomMgr::GetInstance().GetRandomFloat_from_UniformDist(m_Pos.x - 150, m_Pos.x + 150);
				auto posY = CRandomMgr::GetInstance().GetRandomFloat_from_UniformDist(m_Pos.y - 150, m_Pos.y + 150);

				SpawnEffect(L"boss_explosion", Vec2(posX, posY));
			}

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
			m_acctimeSinceLastTearDrop = 0;
			return;
		}
	}

	m_acctimeSinceLastTearDrop += DT;
}

void Onion::SpawnEffect(const wstring& _effectName, Vec2 _pos)
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
	// TODO : 랜덤한 지역에 눈물 스폰
	bool spawn_right_side = CRandomMgr::GetInstance().GetRandomBool(0.5);
	float posX = 0;
	if (spawn_right_side)
	{
		posX = CRandomMgr::GetInstance().GetRandomFloat_from_UniformDist(-650, -200);
	}
	else
	{
		posX = CRandomMgr::GetInstance().GetRandomFloat_from_UniformDist(200, 650);
	}

	auto tearDrop_clone = m_TearDrop->Clone();
	tearDrop_clone->SetPos(Vec2(posX, -360));
	SpawnObject(LAYER_TYPE::ENEMY_MISSILE, tearDrop_clone);
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