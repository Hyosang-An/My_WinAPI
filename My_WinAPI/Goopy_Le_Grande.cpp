#include "pch.h"
#include "Goopy_Le_Grande.h"

#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CLevel_Goopy_Le_Grande.h"
#include "Question_Mark.h"
#include "CEffect.h"
#include "CMissile.h"

Goopy_Le_Grande::Goopy_Le_Grande()
{
	SetName(L"Goopy Le Grande");

	// Rigidbody 설정
	m_Rigidbody = AddComponent(new CRigidbody);
	m_Rigidbody->SetMaxGravitySpeed(2000);

	// 콜백함수 설정
	m_Rigidbody->SetGroundCallbackFunc([this]() {this->EnterGround(); });
	m_Rigidbody->SetAirCallbackFunc([this]() {this->LeaveGround(); });

	// 애니메이터 설정
	m_Animator = AddComponent(new CAnimator);

	// 충돌체 설정
	m_BodyCollider = AddComponent(new CCollider);
	m_BodyCollider->SetName(L"Body Collider");
	m_BodyCollider->SetScale(Vec2(150, 200));

	m_PunchCollider = AddComponent(new CCollider);
	m_PunchCollider->SetName(L"Punch Collider");
	m_PunchCollider->SetScale(Vec2(500, 261));
	m_PunchCollider->SetActive(false);

	m_SmashCollider = AddComponent(new CCollider);
	m_SmashCollider->SetName(L"Smash Collider");
	m_SmashCollider->SetOffsetPos(Vec2(0, 200));
	m_SmashCollider->SetScale(Vec2(270 + 46* 2, 150));
	m_SmashCollider->SetActive(false);

	m_TombBottomCollider = AddComponent(new CCollider);
	m_TombBottomCollider->SetName(L"Tomb Bottom Collider");
	m_TombBottomCollider->SetOffsetPos(Vec2(0, 200));
	m_TombBottomCollider->SetScale(Vec2(250, 150));
	m_TombBottomCollider->SetActive(false);
}

Goopy_Le_Grande::~Goopy_Le_Grande()
{
	Safe_Del_Map(m_mapEffect);
}

void Goopy_Le_Grande::begin()
{
	m_player = static_cast<CPlayer*>(CLevelMgr::GetInstance().GetCurrentLevel()->GetObjvecOfLayer(LAYER_TYPE::PLAYER)[0]);

	LoadAnimation();
	m_Animator->Play(L"slime_intro_L", false);

	// 이펙트 추가
	CEffect* effect = new CEffect;
	effect->SetName(L"Ph1_Dust");
	effect->SetAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Dust\\A\\lg_slime_dust_a.anim");
	m_mapEffect.insert(make_pair(effect->GetName(), effect));

	effect = new CEffect;
	effect->SetName(L"Ph2_Dust");
	effect->SetAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Dust\\B\\lg_slime_dust_b.anim");
	m_mapEffect.insert(make_pair(effect->GetName(), effect));

	effect = new CEffect;
	effect->SetName(L"Ph3_Intro_Dust");
	effect->SetAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Dust(Intro)\\slime_tomb_dust.anim");
	m_mapEffect.insert(make_pair(effect->GetName(), effect));

	effect = new CEffect;
	effect->SetName(L"Ph3_Smash_Dust");
	effect->SetAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Smash\\Dust\\slime_tomb_smash_dust.anim");
	m_mapEffect.insert(make_pair(effect->GetName(), effect)); 

	effect = new CEffect;
	effect->SetName(L"Ph3_Move_Dust_L");
	effect->SetAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Move\\GroundFX\\Dust\\slime_tomb_groundfx_L.anim", true);
	effect->SetParentAndOffset(this, Vec2(0, 246));
	m_mapEffect.insert(make_pair(effect->GetName(), effect));

	effect = new CEffect;
	effect->SetName(L"Ph3_Move_Dust_R");
	effect->SetAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 3\\Move\\GroundFX\\Dust\\slime_tomb_groundfx_R.anim", true);
	effect->SetParentAndOffset(this, Vec2(0, 246));
	m_mapEffect.insert(make_pair(effect->GetName(), effect));
}

void Goopy_Le_Grande::tick()
{
	UpdateState();
	UpdateAnimation();
	MoveAndAction();

	m_PrevBaseState = m_CurBaseState;
}

// ============================================================================================================================================================
// ========================== UpdateState() ===============================================================================================================
// ============================================================================================================================================================

void Goopy_Le_Grande::UpdateState()
{
	switch (m_PhaseState)
	{
		case PHASE_STATE::PHASE1:
			Phase1_Update();
			break;
		case PHASE_STATE::PHASE2:
			Phase2_Update();
			break;
		case PHASE_STATE::PHASE3:
			Phase3_Update();
			break;
		default:
			break;
	}
}

// ============================================================================================================================================================
// ========================== Phase1_Update() ===============================================================================================================
// ============================================================================================================================================================

void Goopy_Le_Grande::Phase1_Update()
{
	if (m_Rigidbody->IsOnGround() && m_CurBaseState != BASE_STATE::PUNCH)
	{
		if (m_iHP <= 0 && m_CurBaseState != BASE_STATE::TRANSITION_TO_PH2)
		{
			if ((m_player->GetPos() - GetPos()).x >= 0)
				m_bFacingRight = true;
			else
				m_bFacingRight = false;

			m_CurBaseState = BASE_STATE::TRANSITION_TO_PH2;
			return;
		}
	}

	if (m_CurBaseState != BASE_STATE::PUNCH)
		m_PunchCollider->SetActive(false);

	switch (m_CurBaseState)
	{
		case BASE_STATE::INTRO:
		{
			if (m_Animator->IsCurAnimationFinished())
			{
				m_CurBaseState = BASE_STATE::JUMP;
				m_iJumpCnt++;
			}
			break;
		}
		case BASE_STATE::JUMP:
			if (m_Rigidbody->GetVelocity().y < 0)
				m_CurBaseState = BASE_STATE::AIR_UP;
			break;
		case BASE_STATE::AIR_UP:
			if (m_Rigidbody->GetVelocity().y >= -50)
				m_CurBaseState = BASE_STATE::UP_DOWN_TRANSITION;
			break;
		case BASE_STATE::UP_DOWN_TRANSITION:
			if (m_Animator->IsCurAnimationFinished())
				m_CurBaseState = BASE_STATE::AIR_DOWN;
			break;
		case BASE_STATE::AIR_DOWN:
		{
			if (m_Rigidbody->IsOnGround())
			{
				SpawnEffect(L"Ph1_Dust", m_Pos + Vec2(0, 80));

				// 점프 하는 경우
				if (m_iJumpCnt < m_iMaxJumpCnt)
				{
					m_CurBaseState = BASE_STATE::JUMP;
					m_iJumpCnt++;
				}
				// 펀치 하는 경우
				else
				{
					m_CurBaseState = BASE_STATE::PUNCH;
					if ((m_player->GetPos() - GetPos()).x >= 0)
					{
						m_bFacingRight = true;
						m_PunchCollider->SetOffsetPos(Vec2(336, -105));
					}
					else
					{
						m_bFacingRight = false;
						m_PunchCollider->SetOffsetPos(Vec2(-336, -105));
					}
					m_iJumpCnt = 0;
				}
			}
			break;
		}

		case BASE_STATE::PUNCH:
		{
			// 펀치가 끝나면 다시 점프
			if (m_Animator->IsCurAnimationFinished())
			{
				m_CurBaseState = BASE_STATE::JUMP;
				m_iJumpCnt = 1;
			}

			// 펀치할 때 m_PunchCollider 설정
			else if (m_Animator->GetCurAnimationFrmIdx() >= 9 && m_Animator->GetCurAnimationFrmIdx() <= 10)
				m_PunchCollider->SetActive(true);
			else
				m_PunchCollider->SetActive(false);

			break;
		}
		case BASE_STATE::TRANSITION_TO_PH2:
		{
			// 물음표 생성
			if ((m_Animator->GetCurAnimation()->GetName() == L"slime_morph_2_L" || m_Animator->GetCurAnimation()->GetName() == L"slime_morph_2_R") && m_Animator->GetCurAnimationFrmIdx() == 10 && !m_bSpawn_question)
			{
				m_bSpawn_question = true;
				CObj* question_mark = new Question_Mark;
				question_mark->SetPos(m_Pos + Vec2(-110, -100));
				SpawnObject(LAYER_TYPE::NEUTRAL_OBJ, question_mark);

				question_mark = new Question_Mark;
				question_mark->SetPos(m_Pos + Vec2(110, -100));
				SpawnObject(LAYER_TYPE::NEUTRAL_OBJ, question_mark);


				question_mark = new Question_Mark;
				question_mark->SetPos(m_Pos + Vec2(0, -200));
				SpawnObject(LAYER_TYPE::NEUTRAL_OBJ, question_mark);
			}

			// 페이즈 2로 전환
			if ((m_Animator->GetCurAnimation()->GetName() == L"slime_morph_2_L" || m_Animator->GetCurAnimation()->GetName() == L"slime_morph_2_R") && m_Animator->IsCurAnimationFinished())
			{
				m_PhaseState = PHASE_STATE::PHASE2;
				m_CurBaseState = BASE_STATE::IDLE;
				m_iHP = 5;

				m_BodyCollider->SetScale(Vec2(150 + 122, 200 + 132));
				m_BodyCollider->SetOffsetPos(Vec2(0, 0));
			}
			break;
		}
		default:
			break;
	}
}

// ============================================================================================================================================================
// ========================== Phase2_Update() ===============================================================================================================
// ============================================================================================================================================================

void Goopy_Le_Grande::Phase2_Update()
{
	if (m_Rigidbody->IsOnGround() && m_CurBaseState != BASE_STATE::PUNCH)
	{
		if (m_iHP <= 0 && m_CurBaseState != BASE_STATE::DEATH)
		{
			m_CurBaseState = BASE_STATE::DEATH;
			return;
		}
	}

	if (m_CurBaseState != BASE_STATE::PUNCH)
		m_PunchCollider->SetActive(false);

	switch (m_CurBaseState)
	{
		case BASE_STATE::IDLE:
		{
			if (1.2 < m_accIdleTime)
			{
				m_accIdleTime = 0;
				m_CurBaseState = BASE_STATE::JUMP;
				m_iJumpCnt++;
				break;
			}
			m_accIdleTime += DT;
			break;
		}
		case BASE_STATE::JUMP:
			if (m_Rigidbody->GetVelocity().y < 0)
				m_CurBaseState = BASE_STATE::AIR_UP;
			break;
		case BASE_STATE::AIR_UP:
			if (m_Rigidbody->GetVelocity().y >= -50)
				m_CurBaseState = BASE_STATE::UP_DOWN_TRANSITION;
			break;
		case BASE_STATE::UP_DOWN_TRANSITION:
			if (m_Animator->IsCurAnimationFinished())
				m_CurBaseState = BASE_STATE::AIR_DOWN;
			break;
		case BASE_STATE::AIR_DOWN:
		{
			if (m_Rigidbody->IsOnGround())
			{
				SpawnEffect(L"Ph2_Dust", m_Pos + Vec2(0, 220));

				// 점프 하는 경우
				if (m_iJumpCnt < m_iMaxJumpCnt)
				{
					m_CurBaseState = BASE_STATE::JUMP;
					m_iJumpCnt++;
				}
				// 펀치 하는 경우
				else
				{
					m_PunchCollider->SetScale(Vec2(400, 182));
					m_CurBaseState = BASE_STATE::PUNCH;
					if ((m_player->GetPos() - GetPos()).x >= 0)
					{
						m_bFacingRight = true;
						m_PunchCollider->SetOffsetPos(Vec2(378, -15));
					}
					else
					{
						m_bFacingRight = false;
						m_PunchCollider->SetOffsetPos(Vec2(-378, -15));
					}
					m_iJumpCnt = 0;
				}
			}
			break;
		}
		case BASE_STATE::PUNCH:
		{
			// 펀치가 끝나면 다시 점프
			auto& curAnimName = m_Animator->GetCurAnimation()->GetName();
			if ((curAnimName == L"lg_slime_punch_2_L" || curAnimName == L"lg_slime_punch_2_R") &&
				m_Animator->IsCurAnimationFinished())
			{
				m_CurBaseState = BASE_STATE::JUMP;
				m_iJumpCnt = 1;
			}

			// 펀치할 때 m_PunchCollider 설정
			else if ((curAnimName == L"lg_slime_punch_2_L" || curAnimName == L"lg_slime_punch_2_R") &&
				m_Animator->GetCurAnimationFrmIdx() >= 5 &&
				m_Animator->GetCurAnimationFrmIdx() <= 8)
				m_PunchCollider->SetActive(true);
			else
				m_PunchCollider->SetActive(false);

			break;
		}

		case BASE_STATE::DEATH:
		{
			m_accDeathTime += DT;

			if (m_bSpawn3Phase == false && 1.5 < m_accDeathTime)
			{
				m_bSpawn3Phase = true;
				m_accDeathTime = 0;

				auto phase3_boss = new Goopy_Le_Grande;
				phase3_boss->SetName(L"Goopy Le Grande Phase3");
				phase3_boss->SetPhase3Intro();
				phase3_boss->SetPos(Vec2(GetPos().x, -1500));
				if (CLevel_Goopy_Le_Grande* Level_Goopy_Le_Grande = dynamic_cast<CLevel_Goopy_Le_Grande*>(CLevelMgr::GetInstance().GetCurrentLevel()))
					Level_Goopy_Le_Grande->ChangeBoss(phase3_boss);
				SpawnObject(LAYER_TYPE::BOSS, phase3_boss);
			}

			break;
		}
		default:
			break;
	}
}

// ============================================================================================================================================================
// ========================== Phase3_Update() ===============================================================================================================
// ============================================================================================================================================================

void Goopy_Le_Grande::Phase3_Update()
{
	// 화면 테두리와 충돌한 경우
	if ((m_TombBottomCollider->GetFinalPos().x - m_TombBottomCollider->GetScale().x * 0.5f) < CCamera::GetInstance().GetLeftTopPos().x)
	{
		auto diff = -(m_TombBottomCollider->GetFinalPos().x - m_TombBottomCollider->GetScale().x * 0.5f) + CCamera::GetInstance().GetLeftTopPos().x;
		m_Pos.x += diff;
		m_CurBaseState = BASE_STATE::TURN_LEFT_TO_RIGHT;
		m_bFacingRight = true;
	}
	else if ((m_TombBottomCollider->GetFinalPos().x + m_TombBottomCollider->GetScale().x * 0.5f) > (CCamera::GetInstance().GetLeftTopPos().x + CEngine::GetInstance().GetResolution().x))
	{
		auto diff = (m_TombBottomCollider->GetFinalPos().x + m_TombBottomCollider->GetScale().x * 0.5f) - (CCamera::GetInstance().GetLeftTopPos().x + CEngine::GetInstance().GetResolution().x);
		m_Pos.x -= diff;
		m_CurBaseState = BASE_STATE::TURN_RIGHT_TO_LEFT;
		m_bFacingRight = false;
	}

	if (m_iHP <= 0 && m_CurBaseState != BASE_STATE::DEATH)
	{
		m_CurBaseState = BASE_STATE::DEATH;
		return;
	}

	if (m_CurBaseState != BASE_STATE::SMASH)
		m_SmashCollider->SetActive(false);

	if (m_CurBaseState != BASE_STATE::MOVE)
	{
		// FX 삭제
		if (m_3Ph_move_dust_effect_L != nullptr)
		{
			m_3Ph_move_dust_effect_L->SelfDestruct(); 
			m_3Ph_move_dust_effect_L = nullptr;
		}
		if (m_3Ph_move_dust_effect_R != nullptr)
		{
			m_3Ph_move_dust_effect_R->SelfDestruct(); 
			m_3Ph_move_dust_effect_R = nullptr;
		}
	}

	switch (m_CurBaseState)
	{
		case BASE_STATE::INTRO:
		{
			m_TombBottomCollider->SetActive(true);

			if (m_Rigidbody->IsOnGround() && !m_bSpawn_3ph_intro_effect)
			{
				m_bSpawn_3ph_intro_effect = true;
				SpawnEffect(L"Ph3_Intro_Dust", m_Pos + Vec2(0, 220));
			}

			// Intro 종료
			if (m_Animator->GetCurAnimation()->GetName() == L"slime_tomb_trans" && m_Animator->IsCurAnimationFinished())
			{
				m_CurBaseState = BASE_STATE::MOVE;

				if ((m_player->GetPos() - m_Pos).x < 0)
				{
					m_bFacingRight = false;
					// FX
					auto iter = m_mapEffect.find(L"Ph3_Move_Dust_L");
					m_3Ph_move_dust_effect_L = iter->second->Clone();
					m_3Ph_move_dust_effect_L->PlayEffect();
					SpawnObject(LAYER_TYPE::EFFECT, m_3Ph_move_dust_effect_L);
				}
				else
				{
					m_bFacingRight = true;
					// FX
					auto iter = m_mapEffect.find(L"Ph3_Move_Dust_R");
					m_3Ph_move_dust_effect_R = iter->second->Clone();
					m_3Ph_move_dust_effect_R->PlayEffect();
					SpawnObject(LAYER_TYPE::EFFECT, m_3Ph_move_dust_effect_R);
				}
			}

			break;
		}

		case BASE_STATE::MOVE:
		{
			m_accMovingTime += DT;

			if (m_SmashTime < m_accMovingTime && abs((m_player->GetPos() - m_Pos).x) < 10)
			{
				m_accMovingTime = 0;
				m_CurBaseState = BASE_STATE::SMASH;
			}

			break;
		}

		case BASE_STATE::TURN_MID_TO_LEFT:
		{
			if (m_Animator->IsCurAnimationFinished())
			{
				m_CurBaseState = BASE_STATE::MOVE;

				// FX
				auto iter = m_mapEffect.find(L"Ph3_Move_Dust_L");
				m_3Ph_move_dust_effect_L = iter->second->Clone();
				m_3Ph_move_dust_effect_L->PlayEffect();
				SpawnObject(LAYER_TYPE::EFFECT, m_3Ph_move_dust_effect_L);
			}
			break;
		}

		case BASE_STATE::TURN_MID_TO_RIGHT:
		{
			if (m_Animator->IsCurAnimationFinished())
			{
				m_CurBaseState = BASE_STATE::MOVE;

				// FX
				auto iter = m_mapEffect.find(L"Ph3_Move_Dust_R");
				m_3Ph_move_dust_effect_R = iter->second->Clone();
				m_3Ph_move_dust_effect_R->PlayEffect();
				SpawnObject(LAYER_TYPE::EFFECT, m_3Ph_move_dust_effect_R);
			}
			break;
		}

		case BASE_STATE::TURN_LEFT_TO_RIGHT:
		{
			if (m_Animator->GetCurAnimation()->GetName() == L"slime_tomb_trans_mid_to_right" && m_Animator->IsCurAnimationFinished())
			{
				m_CurBaseState = BASE_STATE::MOVE;

				// FX
				auto iter = m_mapEffect.find(L"Ph3_Move_Dust_R");
				m_3Ph_move_dust_effect_R = iter->second->Clone();
				m_3Ph_move_dust_effect_R->PlayEffect();
				SpawnObject(LAYER_TYPE::EFFECT, m_3Ph_move_dust_effect_R);
			}
			break;
		}

		case BASE_STATE::TURN_RIGHT_TO_LEFT:
		{
			if (m_Animator->GetCurAnimation()->GetName() == L"slime_tomb_trans_mid_to_left" && m_Animator->IsCurAnimationFinished())
			{
				m_CurBaseState = BASE_STATE::MOVE;

				// FX
				auto iter = m_mapEffect.find(L"Ph3_Move_Dust_L");
				m_3Ph_move_dust_effect_L = iter->second->Clone();
				m_3Ph_move_dust_effect_L->PlayEffect();
				SpawnObject(LAYER_TYPE::EFFECT, m_3Ph_move_dust_effect_L);
			}
			break;
		}

		case BASE_STATE::SMASH:
		{
			// Smash 할 때 충돌체 설정
			if (m_Animator->GetCurAnimation()->GetName() == L"slime_tomb_smash_2" && m_Animator->GetCurAnimationFrmIdx() <= 1)
			{
				if (!m_bSpawn_smash_effect)
				{
					m_bSpawn_smash_effect = true;
					SpawnEffect(L"Ph3_Smash_Dust", m_Pos + Vec2(0, 220));
				}
				m_SmashCollider->SetActive(true);
			}
			
			else
				m_SmashCollider->SetActive(false);

			if (m_Animator->GetCurAnimation()->GetName() == L"slime_tomb_smash_2" && m_Animator->IsCurAnimationFinished())
			{
				m_bSpawn_smash_effect = false;

				if ((m_player->GetPos() - m_Pos).x < 0)
				{
					m_CurBaseState = BASE_STATE::TURN_MID_TO_LEFT;
					m_bFacingRight = false;
				}
				else
				{
					m_CurBaseState = BASE_STATE::TURN_MID_TO_RIGHT;
					m_bFacingRight = true;
				}
			}
			break;
		}

		case BASE_STATE::DEATH:
		{
			if (m_bClear == false)
			{
				CLevelMgr::GetInstance().GetCurrentLevel()->LevelClear();
				m_bClear = true;
			}
			break;
		}
	}
}

// ============================================================================================================================================================
// ========================== UpdateAnimation() ===============================================================================================================
// ============================================================================================================================================================

void Goopy_Le_Grande::UpdateAnimation()
{
	switch (m_PhaseState)
	{
		case PHASE_STATE::PHASE1:
		{
			// 왼쪽을 보고 있는 경우
			if (!m_bFacingRight)
			{
				switch (m_CurBaseState)
				{
					case BASE_STATE::INTRO:
						break;
					case BASE_STATE::JUMP:
						m_Animator->Play(L"slime_jump_L", false);
						break;
					case BASE_STATE::AIR_UP:
						m_Animator->Play(L"slime_air_up_L", true);
						break;
					case BASE_STATE::UP_DOWN_TRANSITION:
						m_Animator->Play(L"slime_up_down_trans_L", false);
						break;
					case BASE_STATE::AIR_DOWN:
						m_Animator->Play(L"slime_air_down_L", true);
						break;
					case BASE_STATE::PUNCH:
						m_Animator->Play(L"slime_punch_L", false);
						break;
					case BASE_STATE::TRANSITION_TO_PH2:
					{
						if (m_Animator->GetCurAnimation()->GetName() == L"slime_morph_2_L")
							break;

						m_Animator->Play(L"slime_morph_1_L", false);
						if (m_Animator->GetCurAnimation()->GetName() == L"slime_morph_1_L" && m_Animator->IsCurAnimationFinished())
							m_Animator->Play(L"slime_morph_2_L", false);
						break;
					}
					default:
						break;
				}
			}
			// 오른쪽을 보고 있는 경우
			else
			{
				switch (m_CurBaseState)
				{
					case BASE_STATE::INTRO:
						break;
					case BASE_STATE::JUMP:
						m_Animator->Play(L"slime_jump_R", false);
						break;
					case BASE_STATE::AIR_UP:
						m_Animator->Play(L"slime_air_up_R", true);
						break;
					case BASE_STATE::UP_DOWN_TRANSITION:
						m_Animator->Play(L"slime_up_down_trans_R", false);
						break;
					case BASE_STATE::AIR_DOWN:
						m_Animator->Play(L"slime_air_down_R", true);
						break;
					case BASE_STATE::PUNCH:
						m_Animator->Play(L"slime_punch_R", false);
						break;
					case BASE_STATE::TRANSITION_TO_PH2:
					{
						if (m_Animator->GetCurAnimation()->GetName() == L"slime_morph_2_R")
							break;

						m_Animator->Play(L"slime_morph_1_R", false);
						if (m_Animator->GetCurAnimation()->GetName() == L"slime_morph_1_R" && m_Animator->IsCurAnimationFinished())
							m_Animator->Play(L"slime_morph_2_R", false);
						break;
					}
					default:
						break;
				}
			}

			break;
		}

		case PHASE_STATE::PHASE2:
		{
			// 왼쪽을 보는 경우
			if (!m_bFacingRight)
			{
				switch (m_CurBaseState)
				{
					case BASE_STATE::IDLE:
						m_Animator->Play(L"lg_slime_idle_L", true, true);
						break;
					case BASE_STATE::JUMP:
						m_Animator->Play(L"lg_slime_jump_L", false);
						break;
					case BASE_STATE::AIR_UP:
						m_Animator->Play(L"lg_slime_air_up_L", true);
						break;
					case BASE_STATE::UP_DOWN_TRANSITION:
						m_Animator->Play(L"lg_slime_up_down_trans_L", false);
						break;
					case BASE_STATE::AIR_DOWN:
						m_Animator->Play(L"lg_slime_air_down_L", true);
						break;
					case BASE_STATE::PUNCH:
					{
						if (m_Animator->GetCurAnimation()->GetName() == L"lg_slime_punch_2_L")
							break;

						m_Animator->Play(L"lg_slime_punch_1_L", false);
						if (m_Animator->GetCurAnimation()->GetName() == L"lg_slime_punch_1_L" && m_Animator->IsCurAnimationFinished())
							m_Animator->Play(L"lg_slime_punch_2_L", false);
						break;
					}
					case BASE_STATE::DEATH:
						m_Animator->Play(L"lg_slime_death_L", true);
						break;
					default:
						break;
				}
			}
			// 오른쪽을 보는 경우
			else
			{
				switch (m_CurBaseState)
				{
					case BASE_STATE::IDLE:
						m_Animator->Play(L"lg_slime_idle_R", true, true);
						break;
					case BASE_STATE::JUMP:
						m_Animator->Play(L"lg_slime_jump_R", false);
						break;
					case BASE_STATE::AIR_UP:
						m_Animator->Play(L"lg_slime_air_up_R", true);
						break;
					case BASE_STATE::UP_DOWN_TRANSITION:
						m_Animator->Play(L"lg_slime_up_down_trans_R", false);
						break;
					case BASE_STATE::AIR_DOWN:
						m_Animator->Play(L"lg_slime_air_down_R", true);
						break;
					case BASE_STATE::PUNCH:
					{
						if (m_Animator->GetCurAnimation()->GetName() == L"lg_slime_punch_2_R")
							break;

						m_Animator->Play(L"lg_slime_punch_1_R", false);
						if (m_Animator->GetCurAnimation()->GetName() == L"lg_slime_punch_1_R" && m_Animator->IsCurAnimationFinished())
							m_Animator->Play(L"lg_slime_punch_2_R", false);

						break;
					}
					case BASE_STATE::DEATH:
						m_Animator->Play(L"lg_slime_death_R", true);
						break;
					default:
						break;
				}
			}

			break;
		}

		case PHASE_STATE::PHASE3:
		{
			switch (m_CurBaseState)
			{
				case BASE_STATE::INTRO:
				{
					const auto& anim_name = m_Animator->GetCurAnimation()->GetName();

					// 낙하 중
					if (!m_Rigidbody->IsOnGround())
						m_Animator->Play(L"slime_tomb_fall", false);

					// 낙하 후
					else
					{
						if (anim_name == L"slime_tomb_trans")
							break;

						m_Animator->Play(L"slime_tomb_slam", false);

						if (anim_name == L"slime_tomb_slam" && m_Animator->IsCurAnimationFinished())
							m_Animator->Play(L"slime_tomb_trans", true, true);
					}
					break;
				}

				case BASE_STATE::MOVE:
				{
					if (m_bFacingRight)
						m_Animator->Play(L"slime_tomb_rt_move_R", true, true);
					else
						m_Animator->Play(L"slime_tomb_lt_move_L", true, true);
					break;
				}

				case BASE_STATE::TURN_MID_TO_LEFT:
					m_Animator->Play(L"slime_tomb_trans_mid_to_left", false);
					break;

				case BASE_STATE::TURN_MID_TO_RIGHT:
					m_Animator->Play(L"slime_tomb_trans_mid_to_right", false);
					break;

				case BASE_STATE::TURN_LEFT_TO_RIGHT:
				{
					if (m_Animator->GetCurAnimation()->GetName() == L"slime_tomb_trans_mid_to_right")
						break;

					m_Animator->Play(L"slime_tomb_trans_left_to_mid", false);

					if (m_Animator->IsCurAnimationFinished())
						m_Animator->Play(L"slime_tomb_trans_mid_to_right", false);
					break;
				}

				case BASE_STATE::TURN_RIGHT_TO_LEFT:
				{
					if (m_Animator->GetCurAnimation()->GetName() == L"slime_tomb_trans_mid_to_left")
						break;

					m_Animator->Play(L"slime_tomb_trans_right_to_mid", false);

					if (m_Animator->IsCurAnimationFinished())
						m_Animator->Play(L"slime_tomb_trans_mid_to_left", false);
					break;
				}

				case BASE_STATE::SMASH:
				{
					if (m_Animator->GetCurAnimation()->GetName() == L"slime_tomb_smash_2")
						break;

					m_Animator->Play(L"slime_tomb_smash_1", false);

					if (m_Animator->GetCurAnimation()->GetName() == L"slime_tomb_smash_1" && m_Animator->IsCurAnimationFinished())
						m_Animator->Play(L"slime_tomb_smash_2", false);

					break;
				}

				case BASE_STATE::DEATH:
					m_Animator->Play(L"slime_tomb_death", true, true);
					break;

			}
			
			break;
		}
	}

}

// ============================================================================================================================================================
// ========================== MoveAndAction() ===============================================================================================================
// ============================================================================================================================================================

void Goopy_Le_Grande::MoveAndAction()
{
	switch (m_PhaseState)
	{
		case PHASE_STATE::PHASE1:
		{
			// 화면 테두리와 충돌한 경우
			if ((m_BodyCollider->GetFinalPos().x - m_BodyCollider->GetScale().x * 0.5f) < CCamera::GetInstance().GetLeftTopPos().x)
			{
				auto diff = - (m_BodyCollider->GetFinalPos().x - m_BodyCollider->GetScale().x * 0.5f) + CCamera::GetInstance().GetLeftTopPos().x;
				m_Pos.x += diff;
				m_Rigidbody->SetVelocity_X(-1 * m_Rigidbody->GetVelocity().x);
				m_bFacingRight = !m_bFacingRight;
			}
			else if ((m_BodyCollider->GetFinalPos().x + m_BodyCollider->GetScale().x * 0.5f) > (CCamera::GetInstance().GetLeftTopPos().x + CEngine::GetInstance().GetResolution().x))
			{
				auto diff = (m_BodyCollider->GetFinalPos().x + m_BodyCollider->GetScale().x * 0.5f) - (CCamera::GetInstance().GetLeftTopPos().x + CEngine::GetInstance().GetResolution().x);
				m_Pos.x -= diff;
				m_Rigidbody->SetVelocity_X(-1 * m_Rigidbody->GetVelocity().x);
				m_bFacingRight = !m_bFacingRight;
			}

			switch (m_CurBaseState)
			{
				case BASE_STATE::INTRO:
					break;
				case BASE_STATE::JUMP:
				{
					if (m_Animator->IsCurAnimationFinished())
					{
						// 랜덤으로 점프 속도 선택
						// TODO

						if (!m_bFacingRight)
							m_Rigidbody->SetVelocity(Vec2(-m_SlimeHorizontalSpeed, m_vecJumpSpeed[0]));
						else
							m_Rigidbody->SetVelocity(Vec2(m_SlimeHorizontalSpeed, m_vecJumpSpeed[0]));
					}
					else
					{
						m_Rigidbody->SetVelocity(Vec2(0, 0));
					}
					break;
				}
				case BASE_STATE::AIR_UP:
					break;
				case BASE_STATE::UP_DOWN_TRANSITION:
					break;
				case BASE_STATE::AIR_DOWN:
					break;
				case BASE_STATE::PUNCH:
					m_Rigidbody->SetVelocity(Vec2(0, 0));
					break;
				case BASE_STATE::TRANSITION_TO_PH2:
					m_Rigidbody->SetVelocity(Vec2(0, 0));
					break;
				default:
					break;
			}

			break;
		}

		case PHASE_STATE::PHASE2:
		{
			// 화면 테두리와 충돌한 경우
			if ((m_BodyCollider->GetFinalPos().x - m_BodyCollider->GetScale().x * 0.5f) < CCamera::GetInstance().GetLeftTopPos().x)
			{
				auto diff_X = -(m_BodyCollider->GetFinalPos().x - m_BodyCollider->GetScale().x * 0.5f) + CCamera::GetInstance().GetLeftTopPos().x;
				m_Pos.x += diff_X;
				m_Rigidbody->SetVelocity_X(-1 * m_Rigidbody->GetVelocity().x);
				m_bFacingRight = !m_bFacingRight;
			}
			else if ((m_BodyCollider->GetFinalPos().x + m_BodyCollider->GetScale().x * 0.5f) > (CCamera::GetInstance().GetLeftTopPos().x + CEngine::GetInstance().GetResolution().x))
			{
				auto diff = (m_BodyCollider->GetFinalPos().x + m_BodyCollider->GetScale().x * 0.5f) - (CCamera::GetInstance().GetLeftTopPos().x + CEngine::GetInstance().GetResolution().x);
				m_Pos.x -= diff;
				m_Rigidbody->SetVelocity_X(-1 * m_Rigidbody->GetVelocity().x);
				m_bFacingRight = !m_bFacingRight;
			}

			switch (m_CurBaseState)
			{
				case BASE_STATE::JUMP:
				{
					if (m_Animator->IsCurAnimationFinished())
					{
						// 랜덤으로 점프 속도 선택
						// TODO

						if (!m_bFacingRight)
							m_Rigidbody->SetVelocity(Vec2(-m_SlimeHorizontalSpeed, m_vecJumpSpeed[0]));
						else
							m_Rigidbody->SetVelocity(Vec2(m_SlimeHorizontalSpeed, m_vecJumpSpeed[0]));
					}
					else
					{
						m_Rigidbody->SetVelocity(Vec2(0, 0));
					}
					break;
				}

				case BASE_STATE::AIR_UP:
					break;
				case BASE_STATE::UP_DOWN_TRANSITION:
					break;
				case BASE_STATE::AIR_DOWN:
					break;
				case BASE_STATE::PUNCH:
					m_Rigidbody->SetVelocity_X(0);
					break;
				case BASE_STATE::DEATH:
					m_Rigidbody->SetVelocity_X(0);
					break;
				default:
					break;
			}

			break;
		}

		case PHASE_STATE::PHASE3:
		{
			switch (m_CurBaseState)
			{
				case BASE_STATE::INTRO:
					if (!m_Rigidbody->IsOnGround())
						m_Rigidbody->AddForce(Vec2(0, 500));
					m_Rigidbody->SetVelocity_X(0);
					break;

				case BASE_STATE::MOVE:
				{
					if (m_bFacingRight)
						m_Rigidbody->SetVelocity_X(m_TombHorizontalSpeed);
					else
						m_Rigidbody->SetVelocity_X(-m_TombHorizontalSpeed);
					break;
				}

				case BASE_STATE::TURN_MID_TO_LEFT:
					m_Rigidbody->SetVelocity_X(0);
					break;				
				case BASE_STATE::TURN_MID_TO_RIGHT:
					m_Rigidbody->SetVelocity_X(0);
					break;
				case BASE_STATE::TURN_LEFT_TO_RIGHT:
					m_Rigidbody->SetVelocity_X(0);
					break;
				case BASE_STATE::TURN_RIGHT_TO_LEFT:
					m_Rigidbody->SetVelocity_X(0);
					break;
				case BASE_STATE::SMASH:
					m_Rigidbody->SetVelocity_X(0);
					break;
				case BASE_STATE::DEATH:
					m_Rigidbody->SetVelocity_X(0);
					break;
			}

			break;
		}
		default:
			break;
	}
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
	// Phase 1 ======================================================================
	// L
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Intro\\slime_intro_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Down\\slime_air_down_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Up\\slime_air_up_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Jump\\slime_jump_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Punch\\slime_punch_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_1_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_2_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Up Down Transition\\slime_up_down_trans_L.anim");

	// R
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Air Down\\slime_air_down_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Air Up\\slime_air_up_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Jump\\slime_jump_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Punch\\slime_punch_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Transition To Ph2\\slime_morph_1_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Transition To Ph2\\slime_morph_2_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Up Down Transition\\slime_up_down_trans_R.anim");

	


	// Phase 2 ======================================================================
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Idle\\lg_slime_idle_L.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Jump\\lg_slime_jump_L.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Air Up\\lg_slime_air_up_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Air Down\\lg_slime_air_down_L.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Punch\\lg_slime_punch_1_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Punch\\lg_slime_punch_2_L.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Up Down Transition\\lg_slime_up_down_trans_L.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Death\\lg_slime_death_L.anim");

	// R
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Idle\\lg_slime_idle_R.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Jump\\lg_slime_jump_R.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Air Up\\lg_slime_air_up_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Air Down\\lg_slime_air_down_R.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Punch\\lg_slime_punch_1_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Punch\\lg_slime_punch_2_R.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Up Down Transition\\lg_slime_up_down_trans_R.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Death\\lg_slime_death_R.anim");



	// Phase 3 ======================================================================
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Intro\\slime_tomb_fall.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Intro\\slime_tomb_slam.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Intro\\Transition\\slime_tomb_trans.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Death\\slime_tomb_death.anim");

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Smash\\slime_tomb_smash_1.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Smash\\slime_tomb_smash_2.anim");

	// L
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Move\\Left\\slime_tomb_lt_move_L.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Move\\Left\\Trans\\slime_tomb_trans_left_to_mid.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Move\\Left\\Trans\\slime_tomb_trans_mid_to_left.anim");

	// R
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 3\\Move\\Right\\slime_tomb_rt_move_R.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 3\\Move\\Right\\Trans\\slime_tomb_trans_right_to_mid.anim");
	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 3\\Move\\Right\\Trans\\slime_tomb_trans_mid_to_right.anim");




}

void Goopy_Le_Grande::SpawnEffect(const wstring& _effectName, Vec2 _pos)
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
	// effect_clone->PlayEffect();

	SpawnObject(LAYER_TYPE::EFFECT, effect_clone);
}

void Goopy_Le_Grande::SpawnEffectAttachedToParent(const wstring& _effectName)
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
	auto new_effect = iter->second->Clone();
	// new_effect->PlayEffect();

	SpawnObject(LAYER_TYPE::EFFECT, new_effect);
}

void Goopy_Le_Grande::EnterGround()
{
}

void Goopy_Le_Grande::LeaveGround()
{
}

void Goopy_Le_Grande::OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider)
{
	CObj* otherObj = _pOtherCollider->GetOwner();
	LAYER_TYPE layer_type = otherObj->GetLayerType();

	switch (layer_type)
	{
		case LAYER_TYPE::WALL:
		{
			// 1, 2 페이즈
			if (m_PhaseState != PHASE_STATE::PHASE3)
			{
				// Bodycollider인 경우에만 방향 전환
				if (_pOtherCollider != m_BodyCollider)
					return;

				m_Rigidbody->SetVelocity_X(-1 * m_Rigidbody->GetVelocity().x);
				m_bFacingRight = !m_bFacingRight;
				break;
			}

			// 3 페이즈
			else
			{
				if (m_bFacingRight)
				{
					m_CurBaseState = BASE_STATE::TURN_RIGHT_TO_LEFT;
					m_bFacingRight = false;
				}
				else
				{
					m_CurBaseState = BASE_STATE::TURN_LEFT_TO_RIGHT;
					m_bFacingRight = true;
				}

			}

			break;
		}

		case LAYER_TYPE::PLAYER_MISSILE:
		{
			// 예외
			if (_myCollider == m_TombBottomCollider)
				return;

			CMissile* player_missile = static_cast<CMissile*>(otherObj);
			m_iHP -= player_missile->GetOffensePower();
			player_missile->SelfDestruct();
			break;
		}

		case LAYER_TYPE::BOSS:
		{
			if (otherObj->GetName() == L"Goopy Le Grande Phase3")
			{
				// TODO
				// 터지는 이펙트 오브젝트 생성

				this->SelfDestruct();
			}
			break;
		}
	}
}

void Goopy_Le_Grande::OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider)
{
}

void Goopy_Le_Grande::OnCollisionExit(CCollider* _myCollider, CCollider* _pOtherCollider)
{
}

