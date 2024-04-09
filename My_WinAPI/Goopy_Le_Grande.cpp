#include "pch.h"
#include "Goopy_Le_Grande.h"
#include "CLevelMgr.h"
#include "CPlayer.h"

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
	m_PunchCollider->SetName(L"Punch Collider");
	m_PunchCollider->SetScale(Vec2(500, 261));
	m_PunchCollider->SetActive(false);

	m_SmashCollider = AddComponent(new CCollider);
	m_SmashCollider->SetActive(false);
}

Goopy_Le_Grande::~Goopy_Le_Grande()
{
}

void Goopy_Le_Grande::begin()
{
	m_player = static_cast<CPlayer*>(CLevelMgr::GetInstance().GetCurrentLevel()->GetObjvecOfLayer(LAYER_TYPE::PLAYER)[0]);

	LoadAnimation();
	m_Animator->Play(L"slime_intro_L", false);
}

void Goopy_Le_Grande::tick()
{
	UpdateState();
	MoveAndAction();
	UpdateAnimation();
}

// ============================================================================================================================================================
// ========================== UpdateState() ===============================================================================================================
// ============================================================================================================================================================

void Goopy_Le_Grande::UpdateState()
{
	switch (m_PhaseState)
	{
		case Goopy_Le_Grande::PHASE_STATE::PHASE1:
			Phase1_Update();
			break;
		case Goopy_Le_Grande::PHASE_STATE::PHASE2:
			break;
		case Goopy_Le_Grande::PHASE_STATE::PHASE3:
			break;
		default:
			break;
	}
}

// ============================================================================================================================================================
// ========================== MoveAndAction() ===============================================================================================================
// ============================================================================================================================================================

void Goopy_Le_Grande::MoveAndAction()
{
	switch (m_PhaseState)
	{
		case Goopy_Le_Grande::PHASE_STATE::PHASE1:
		{
			switch (m_BaseState)
			{
				case Goopy_Le_Grande::BASE_STATE::INTRO:
					break;
				case Goopy_Le_Grande::BASE_STATE::JUMP:
				{
					if (m_Animator->IsCurAnimationFinished())
					{

						if (!m_bFacingRight)
							m_Rigidbody->SetVelocity(Vec2(-m_HorizontalSpeed, m_vecJumpSpeed[0]));
						else
							m_Rigidbody->SetVelocity(Vec2(m_HorizontalSpeed, m_vecJumpSpeed[0]));
					}
					else
					{
						m_Rigidbody->SetVelocity(Vec2(0, 0));
					}
					break;
				}
				case Goopy_Le_Grande::BASE_STATE::AIR_UP:
					break;
				case Goopy_Le_Grande::BASE_STATE::UP_DOWN_TRANSITION:
					break;
				case Goopy_Le_Grande::BASE_STATE::AIR_DOWN:
					break;
				case Goopy_Le_Grande::BASE_STATE::PUNCH:
					m_Rigidbody->SetVelocity(Vec2(0, 0));
					break;
				case Goopy_Le_Grande::BASE_STATE::TRANSITION_TO_PH2:
					m_Rigidbody->SetVelocity(Vec2(0, 0));
					break;
				default:
					break;
			}

			break;
		}
		case Goopy_Le_Grande::PHASE_STATE::PHASE2:
		{
			switch (m_BaseState)
			{
				case Goopy_Le_Grande::BASE_STATE::INTRO:
					break;
				case Goopy_Le_Grande::BASE_STATE::JUMP:
					break;
				case Goopy_Le_Grande::BASE_STATE::AIR_UP:
					break;
				case Goopy_Le_Grande::BASE_STATE::UP_DOWN_TRANSITION:
					break;
				case Goopy_Le_Grande::BASE_STATE::AIR_DOWN:
					break;
				case Goopy_Le_Grande::BASE_STATE::PUNCH:
					break;
				case Goopy_Le_Grande::BASE_STATE::TRANSITION_TO_PH2:
					break;
				default:
					break;
			}

			break;
		}
		case Goopy_Le_Grande::PHASE_STATE::PHASE3:
		{
			switch (m_BaseState)
			{
				case Goopy_Le_Grande::BASE_STATE::INTRO:
					break;
				case Goopy_Le_Grande::BASE_STATE::JUMP:
					break;
				case Goopy_Le_Grande::BASE_STATE::AIR_UP:
					break;
				case Goopy_Le_Grande::BASE_STATE::UP_DOWN_TRANSITION:
					break;
				case Goopy_Le_Grande::BASE_STATE::AIR_DOWN:
					break;
				case Goopy_Le_Grande::BASE_STATE::PUNCH:
					break;
				case Goopy_Le_Grande::BASE_STATE::TRANSITION_TO_PH2:
					break;
				default:
					break;
			}

			break;
		}
		default:
			break;
	}
}

// ============================================================================================================================================================
// ========================== UpdateAnimation() ===============================================================================================================
// ============================================================================================================================================================

void Goopy_Le_Grande::UpdateAnimation()
{
	switch (m_PhaseState)
	{
		case Goopy_Le_Grande::PHASE_STATE::PHASE1:
		{
			// 왼쪽을 보고 있는 경우
			if (!m_bFacingRight)
			{
				switch (m_BaseState)
				{
					case Goopy_Le_Grande::BASE_STATE::INTRO:
						break;
					case Goopy_Le_Grande::BASE_STATE::JUMP:
						m_Animator->Play(L"slime_jump_L", false);
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_UP:
						m_Animator->Play(L"slime_air_up_L", false);
						break;
					case Goopy_Le_Grande::BASE_STATE::UP_DOWN_TRANSITION:
						m_Animator->Play(L"slime_up_down_trans_L", false);
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_DOWN:
						m_Animator->Play(L"slime_air_down_L", false);
						break;
					case Goopy_Le_Grande::BASE_STATE::PUNCH:
						m_Animator->Play(L"slime_punch_L", false);
						break;
					case Goopy_Le_Grande::BASE_STATE::TRANSITION_TO_PH2:
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
				switch (m_BaseState)
				{
					case Goopy_Le_Grande::BASE_STATE::INTRO:
						break;
					case Goopy_Le_Grande::BASE_STATE::JUMP:
						m_Animator->Play(L"slime_jump_R", false);
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_UP:
						m_Animator->Play(L"slime_air_up_R", false);
						break;
					case Goopy_Le_Grande::BASE_STATE::UP_DOWN_TRANSITION:
						m_Animator->Play(L"slime_up_down_trans_R", false);
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_DOWN:
						m_Animator->Play(L"slime_air_down_R", false);
						break;
					case Goopy_Le_Grande::BASE_STATE::PUNCH:
						m_Animator->Play(L"slime_punch_R", false);
						break;
					case Goopy_Le_Grande::BASE_STATE::TRANSITION_TO_PH2:
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

		case Goopy_Le_Grande::PHASE_STATE::PHASE2:
		{
			if (!m_bFacingRight)
			{
				switch (m_BaseState)
				{
					case Goopy_Le_Grande::BASE_STATE::INTRO:
						break;
					case Goopy_Le_Grande::BASE_STATE::JUMP:
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_UP:
						break;
					case Goopy_Le_Grande::BASE_STATE::UP_DOWN_TRANSITION:
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_DOWN:
						break;
					case Goopy_Le_Grande::BASE_STATE::PUNCH:
						break;
					case Goopy_Le_Grande::BASE_STATE::TRANSITION_TO_PH2:
						break;
					default:
						break;
				}
			}
			else
			{
				switch (m_BaseState)
				{
					case Goopy_Le_Grande::BASE_STATE::INTRO:
						break;
					case Goopy_Le_Grande::BASE_STATE::JUMP:
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_UP:
						break;
					case Goopy_Le_Grande::BASE_STATE::UP_DOWN_TRANSITION:
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_DOWN:
						break;
					case Goopy_Le_Grande::BASE_STATE::PUNCH:
						break;
					case Goopy_Le_Grande::BASE_STATE::TRANSITION_TO_PH2:
						break;
					default:
						break;
				}
			}

			break;
		}

		case Goopy_Le_Grande::PHASE_STATE::PHASE3:
		{
			if (!m_bFacingRight)
			{
				switch (m_BaseState)
				{
					case Goopy_Le_Grande::BASE_STATE::INTRO:
						break;
					case Goopy_Le_Grande::BASE_STATE::JUMP:
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_UP:
						break;
					case Goopy_Le_Grande::BASE_STATE::UP_DOWN_TRANSITION:
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_DOWN:
						break;
					case Goopy_Le_Grande::BASE_STATE::PUNCH:
						break;
					case Goopy_Le_Grande::BASE_STATE::TRANSITION_TO_PH2:
						break;
					default:
						break;
				}
			}
			else
			{
				switch (m_BaseState)
				{
					case Goopy_Le_Grande::BASE_STATE::INTRO:
						break;
					case Goopy_Le_Grande::BASE_STATE::JUMP:
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_UP:
						break;
					case Goopy_Le_Grande::BASE_STATE::UP_DOWN_TRANSITION:
						break;
					case Goopy_Le_Grande::BASE_STATE::AIR_DOWN:
						break;
					case Goopy_Le_Grande::BASE_STATE::PUNCH:
						break;
					case Goopy_Le_Grande::BASE_STATE::TRANSITION_TO_PH2:
						break;
					default:
						break;
				}
			}

			break;
		}
		default:
			break;
	}

}

// ============================================================================================================================================================
// ========================== Phase1_Update() ===============================================================================================================
// ============================================================================================================================================================

void Goopy_Le_Grande::Phase1_Update()
{
	if (m_Rigidbody->IsOnGround() && m_BaseState != BASE_STATE::PUNCH)
	{
		if (m_iHP <= 0 && m_BaseState != BASE_STATE::TRANSITION_TO_PH2)
		{
			if ((m_player->GetPos() - GetPos()).x >= 0)
				m_bFacingRight = true;
			else
				m_bFacingRight = false;

			m_BaseState = BASE_STATE::TRANSITION_TO_PH2;
			return;
		}
	}

	if (m_BaseState != BASE_STATE::PUNCH)
		m_PunchCollider->SetActive(false);

	switch (m_BaseState)
	{
		case Goopy_Le_Grande::BASE_STATE::INTRO:
		{
			if (m_Animator->IsCurAnimationFinished())
			{
				m_BaseState = BASE_STATE::JUMP;
				m_iJumpCnt++;
			}
			break;
		}
		case Goopy_Le_Grande::BASE_STATE::JUMP:
			if (m_Rigidbody->GetVelocity().y < 0)
				m_BaseState = BASE_STATE::AIR_UP;
			break;
		case Goopy_Le_Grande::BASE_STATE::AIR_UP:
			if (m_Rigidbody->GetVelocity().y >= -50)
				m_BaseState = BASE_STATE::UP_DOWN_TRANSITION;
			break;
		case Goopy_Le_Grande::BASE_STATE::UP_DOWN_TRANSITION:
			if (m_Animator->IsCurAnimationFinished())
				m_BaseState = BASE_STATE::AIR_DOWN;
			break;
		case Goopy_Le_Grande::BASE_STATE::AIR_DOWN:
			if (m_Rigidbody->IsOnGround())
			{
				// 점프 하는 경우
				if (m_iJumpCnt < m_iMaxJumpCnt)
				{
					m_BaseState = BASE_STATE::JUMP;
					m_iJumpCnt++;
				}
				// 펀치 하는 경우
				else
				{
					m_BaseState = BASE_STATE::PUNCH;
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
		case Goopy_Le_Grande::BASE_STATE::PUNCH:
		{
			if (m_Animator->IsCurAnimationFinished())
			{
				m_BaseState = BASE_STATE::JUMP;
				m_iJumpCnt = 1;
			}

			else if (m_Animator->GetCurAnimationFrmIdx() >= 9 && m_Animator->GetCurAnimationFrmIdx() <= 10)
				m_PunchCollider->SetActive(true);
			else
				m_PunchCollider->SetActive(false);

			break;
		}
		case Goopy_Le_Grande::BASE_STATE::TRANSITION_TO_PH2:
		{
			if ((m_Animator->GetCurAnimation()->GetName() == L"slime_morph_2_L" || m_Animator->GetCurAnimation()->GetName() == L"slime_morph_2_R") && m_Animator->IsCurAnimationFinished())
				m_PhaseState = PHASE_STATE::PHASE2;
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
	// 1페이즈 
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
	CObj* otherObj = _pOtherCollider->GetOwner();
	LAYER_TYPE layer_type = otherObj->GetLayerType();

	switch (layer_type)
	{
		case LAYER_TYPE::WALL:
		{
			// Bodycollider인 경우에만 방향 전환
			if (_pOtherCollider != m_BodyCollider)
				return;

			m_Rigidbody->SetVelocity_X(-1 * m_Rigidbody->GetVelocity().x);
			m_bFacingRight = !m_bFacingRight;
			break;
		}

		case LAYER_TYPE::PLAYER_MISSILE:
		{
			otherObj->Destroy();
			m_iHP--;
			break;
		}
	}
}

void Goopy_Le_Grande::OnCollisionStay(CCollider* _pOtherCollider)
{
}

void Goopy_Le_Grande::OnCollisionExit(CCollider* _pOtherCollider)
{
}

