#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CKeyMgr.h"
#include "CCollider.h"
#include "CDbgRenderer.h"
#include "CEngine.h"
#include "CGuidedMissile.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	m_eType = LAYER_TYPE::PLAYER;

	// !!중요!! Collider가 Rigidbody보다 항상 컴포넌트 벡터 상에서 뒤에 위치해야 함!! 그래야 최종 오브젝트 위치를 반영하여 Collider 위치 업데이트 가능
	m_PlayerCollider = AddComponent(new CCollider);
	m_PlayerCollider->SetName(L"Player Collider");
	m_PlayerCollider->SetOffsetPos(Vec2(0.f, 20.f));
	m_PlayerCollider->SetScale(Vec2(60.f, 100.f));

	m_Rigidbody = AddComponent(new CRigidbody);
	m_Rigidbody->SetMaxWalkSpeed(m_RunSpeed);
	//m_Rigidbody->SetFriction(2000);
	//m_Rigidbody->SetMaxGravitySpeed(800);

	// 콜백함수 설정
	m_Rigidbody->SetGroundCallbackFunc([this]() {this->EnterGround(); });
	m_Rigidbody->SetAirCallbackFunc([this]() {this->LeaveGround(); });

	m_Animator = AddComponent(new CAnimator);

	CCamera::GetInstance().SetPlayerToCamera(this);


	

	// .json으로 부터 불러오기
	//{
	//	// R

	//	//Idle
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Idle\\cuphead_idle_R.json", 10);

	//	// Run
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Run\\Normal\\cuphead_run_R.json", 24);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Run\\Shooting\\Diagonal Up\\cuphead_run_shoot_diagonal_up_R.json", 24);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Run\\Shooting\\Straight\\cuphead_run_shoot_R.json", 24);

	//	// Shoot
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_down_R.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Shoot\\Diagonal Up\\cuphead_shoot_diagonal_up_R.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Shoot\\Down\\cuphead_shoot_down_R.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Shoot\\Straight\\cuphead_shoot_straight_R.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Shoot\\Up\\cuphead_shoot_up_R.json", 6);

	//	// Aim
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Aim\\Diagonal Down\\cuphead_aim_diagonal_down_R.json", 10);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Aim\\Diagonal Up\\cuphead_aim_diagonal_up_R.json", 10);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Aim\\Down\\cuphead_aim_down_R.json", 10);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Aim\\Straight\\cuphead_aim_straight_R.json", 10);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Aim\\Up\\cuphead_aim_up_R.json", 10);

	//	// Duck
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Duck\\Idle\\cuphead_duck_idle_R.json", 12);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Duck\\Idle\\cuphead_duck_R.json", 14);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Duck\\Shoot\\cuphead_duck_shoot_boil_R.json", 12);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Duck\\Shoot\\cuphead_duck_shoot_R.json", 12);

	//	// Dash
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Dash\\Ground\\cuphead_dash_R.json", 12);

	//	// Jump
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Jump\\Cuphead\\cuphead_jump_R.json", 24);

	//	// Parrying
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Parry\\Hand\\cuphead_parry_R.json", 24);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Parry\\Hand\\cuphead_parry_pink_R.json", 24);






	//	// L

	//	//Idle
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Idle\\cuphead_idle_L.json", 10);

	//	// Run
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Run\\Normal\\cuphead_run_L.json", 24);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Run\\Shooting\\Diagonal Up\\cuphead_run_shoot_diagonal_up_L.json", 24);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Run\\Shooting\\Straight\\cuphead_run_shoot_L.json", 24);

	//	// Shoot
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_down_L.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Diagonal Up\\cuphead_shoot_diagonal_up_L.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Down\\cuphead_shoot_down_L.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Straight\\cuphead_shoot_straight_L.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Up\\cuphead_shoot_up_L.json", 6);

	//	// Aim
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Aim\\Diagonal Down\\cuphead_aim_diagonal_down_L.json", 10);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Aim\\Diagonal Up\\cuphead_aim_diagonal_up_L.json", 10);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Aim\\Down\\cuphead_aim_down_L.json", 10);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Aim\\Straight\\cuphead_aim_straight_L.json", 10);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Aim\\Up\\cuphead_aim_up_L.json", 10);

	//	// Duck
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Duck\\Idle\\cuphead_duck_idle_L.json", 12);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Duck\\Idle\\cuphead_duck_L.json", 14);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Duck\\Shoot\\cuphead_duck_shoot_boil_L.json", 12);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Duck\\Shoot\\cuphead_duck_shoot_L.json", 12);

	//	// Dash
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Dash\\Ground\\cuphead_dash_L.json", 12);

	//	// Jump
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Jump\\Cuphead\\cuphead_jump_L.json", 24);

	//	// Parrying
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Parry\\Hand\\cuphead_parry_L.json", 24);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Parry\\Hand\\cuphead_parry_pink_L.json", 24);


	//	m_Animator->Play(L"cuphead_idle_R", true, true);
	//}

	// .anim으로 부터 불러오기
	{
		// R

		//Idle
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Idle\\cuphead_idle_R.anim");
					
		// Run		
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Run\\Normal\\cuphead_run_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Run\\Shooting\\Diagonal Up\\cuphead_run_shoot_diagonal_up_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Run\\Shooting\\Straight\\cuphead_run_shoot_R.anim");
					
		// Shoot	
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_down_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Shoot\\Diagonal Up\\cuphead_shoot_diagonal_up_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Shoot\\Down\\cuphead_shoot_down_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Shoot\\Straight\\cuphead_shoot_straight_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Shoot\\Up\\cuphead_shoot_up_R.anim");
					
		// Aim		
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Aim\\Diagonal Down\\cuphead_aim_diagonal_down_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Aim\\Diagonal Up\\cuphead_aim_diagonal_up_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Aim\\Down\\cuphead_aim_down_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Aim\\Straight\\cuphead_aim_straight_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Aim\\Up\\cuphead_aim_up_R.anim");
					
		// Duck		
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Duck\\Idle\\cuphead_duck_idle_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Duck\\Idle\\cuphead_duck_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Duck\\Shoot\\cuphead_duck_shoot_boil_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Duck\\Shoot\\cuphead_duck_shoot_R.anim");
					
		// Dash		
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Dash\\Ground\\cuphead_dash_R.anim");

		// Jump
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Jump\\Cuphead\\cuphead_jump_R.anim");

		// Parrying
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Parry\\Hand\\cuphead_parry_R.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Parry\\Hand\\cuphead_parry_pink_R.anim");





		//L

		// Idle
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Idle\\cuphead_idle_L.anim");

		// Run
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Run\\Normal\\cuphead_run_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Run\\Shooting\\Diagonal Up\\cuphead_run_shoot_diagonal_up_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Run\\Shooting\\Straight\\cuphead_run_shoot_L.anim");
					
		// Shoot	
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_down_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Diagonal Up\\cuphead_shoot_diagonal_up_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Down\\cuphead_shoot_down_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Straight\\cuphead_shoot_straight_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Up\\cuphead_shoot_up_L.anim");
					
		// Aim		
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Aim\\Diagonal Down\\cuphead_aim_diagonal_down_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Aim\\Diagonal Up\\cuphead_aim_diagonal_up_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Aim\\Down\\cuphead_aim_down_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Aim\\Straight\\cuphead_aim_straight_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Aim\\Up\\cuphead_aim_up_L.anim");
					
		// Duck		
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Duck\\Idle\\cuphead_duck_idle_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Duck\\Idle\\cuphead_duck_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Duck\\Shoot\\cuphead_duck_shoot_boil_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Duck\\Shoot\\cuphead_duck_shoot_L.anim");
					
		// Dash		
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Dash\\Ground\\cuphead_dash_L.anim");

		// Jump
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Jump\\Cuphead\\cuphead_jump_L.anim");

		// Parrying
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Parry\\Hand\\cuphead_parry_L.anim");
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_L\\Parry\\Hand\\cuphead_parry_pink_L.anim");
	}

	m_Animator->Play(L"cuphead_idle_R", true, true);
}

CPlayer::CPlayer(const CPlayer& _other)
{
	m_Rigidbody = AddComponent(new CRigidbody(*_other.m_Rigidbody));
	m_PlayerCollider = AddComponent(new CCollider(*_other.m_PlayerCollider));
	m_Animator = AddComponent(new CAnimator(*_other.m_Animator));
}

CPlayer::~CPlayer()
{
}






void CPlayer::begin()
{
}

void CPlayer::tick()
{
	UpdateState();
	MoveAndAction();
	UpdateAnimation();

	m_PrevShootingDir = m_CurShootingDir;
	m_PrevBaseState = m_CurBaseState;
	m_PrevJumpState = m_CurJumpState;
	m_PrevParryState = m_CurParryState;
	m_PrevActionState = m_CurActionState;
}

// ============================================================================================================================================================
// ========================== UpdateState() ===============================================================================================================
// ============================================================================================================================================================

void CPlayer::UpdateState()
{
	// Hitted 및 무적 상태 설정
	// ========================================================================
	if (m_CurBaseState == BASE_STATE::HITTED)
	{
		if (m_PrevBaseState != BASE_STATE::HITTED)
		{
			invincibleTime = 0;
			m_bInvincibleState = true;
		}

		invincibleTime += DT;

		if (HittedTime < m_HittedDuration)
		{
			HittedTime += DT;
			return;
		}

		// hitted 상태 해제
		m_CurActionState = ACTION_STATE::NONE;
	}

	// 무적 지속시간이 끝나면 무적모드 해제
	if (m_InvincibleDuratoin < invincibleTime)
		m_bInvincibleState = false;

	// Dash 상태 설정
	// ========================================================================
	if (m_CurBaseState == BASE_STATE::DASH)
	{
		auto dt = DT;

		// 대쉬 지속시간 끝남
		if (m_DashDuration < DashTime)
		{
			DashTime = 0;
			m_Rigidbody->SetVelocity_X(0);
			if (m_Rigidbody->IsOnGround())
				m_CurBaseState = BASE_STATE::AIRBONE;
			else
				m_CurBaseState = BASE_STATE::IDLE;
		}
		DashTime += DT;

		// 총 쏘는 상태 해제
		if (m_CurActionState == ACTION_STATE::SHOOTING)
			m_CurActionState = ACTION_STATE::NONE;

		return;
	}

	
	// 바라보는 방향 전환 (두 케이스 모두 아니라면 기존 방향 유지)
	// ========================================================================

	bool leftPressed = KEY_PRESSED(KEY::LEFT);
	bool rightPressed = KEY_PRESSED(KEY::RIGHT);
	bool upPressed = KEY_PRESSED(KEY::UP);
	bool downPressed = KEY_PRESSED(KEY::DOWN);

	// 바라보는 방향 전환 (두 케이스 모두 아니라면 기존 방향 유지)
	if (m_bFacingRight && leftPressed && !rightPressed)
		m_bFacingRight = false;
	else if (!m_bFacingRight && !leftPressed && rightPressed)
		m_bFacingRight = true;


	// Base State 설정
	// ========================================================================
	{
		// 땅 위에 있는 경우
		if (m_Rigidbody->IsOnGround())
		{
			// 좌우 방향키 안누르면 Idle
			if (!leftPressed && !rightPressed && !downPressed)
				m_CurBaseState = BASE_STATE::IDLE;

			// 아래 키 누르면 무조건 duck 모드
			else if (downPressed)
				m_CurBaseState = BASE_STATE::DUCK;

			// 좌우 방향키 누르면 run
			else if (leftPressed || rightPressed)
				m_CurBaseState = BASE_STATE::RUN;

			// C키 누르면 고정 모드
			if (KEY_PRESSED(KEY::C))
				m_CurBaseState = BASE_STATE::FIXED;
		}

		// 땅 위에 있지 않은 경우 (공중에 뜬 경우)
		else
		{
			m_CurBaseState = BASE_STATE::AIRBONE;
		}

		// Shift 키 누르면 대쉬
		if (KEY_JUST_PRESSED(KEY::SHIFT))
		{
			if (m_Rigidbody->IsOnGround())
				m_CurBaseState = BASE_STATE::DASH;

			else if (!m_bAirboneDashed)
			{
				m_CurBaseState = BASE_STATE::DASH;
				m_bAirboneDashed = true;
			}
		}

		if (m_Rigidbody->IsOnGround())
			m_bAirboneDashed = false;

		// Duck 상태 일 때 충돌체 설정
		if (m_CurBaseState == BASE_STATE::DUCK)
		{
			m_PlayerCollider->SetScale(Vec2(60, 30));
			m_PlayerCollider->SetOffsetPos(Vec2(0, 55));
		}
		else
		{
			m_PlayerCollider->SetScale(Vec2(60.f, 100.f));
			m_PlayerCollider->SetOffsetPos(Vec2(0.f, 20.f));
		}
	}

	// 플랫폼 내려가기
	if (m_CurBaseState == BASE_STATE::DUCK && m_bOnPlatform && KEY_JUST_PRESSED(KEY::Z))
	{
		m_bOnPlatform = false;
		m_Rigidbody->SetOnGround(false);
		return;
	}


	// Jump State 설정
	// ========================================================================
	if (m_Rigidbody->IsOnGround() && KEY_JUST_PRESSED(KEY::Z))
	{
		// LOG(LOG_TYPE::DBG_WARNING, L"JUMP_START");
		m_JumpingTime = 0;
		m_CurJumpState = JUMP_STATE::JUMP_START;
	}
	else if ((m_CurJumpState == JUMP_STATE::JUMP_START || m_CurJumpState == JUMP_STATE::JUMPING) && KEY_PRESSED(KEY::Z))
	{
		// LOG(LOG_TYPE::DBG_LOG, L"JUMPING");
		m_CurJumpState = JUMP_STATE::JUMPING;
		m_JumpingTime += DT;

		if (m_HighJumpKeyTime < m_JumpingTime)
		{
			// LOG(LOG_TYPE::DBG_ERROR, L"NONE");
			m_JumpingTime = 0;
			m_CurJumpState = JUMP_STATE::NONE;
		}

		//if (m_Rigidbody->GetVelocity().y >=0 )
		//{
		//	// LOG(LOG_TYPE::DBG_ERROR, L"NONE");
		//	m_JumpingTime = 0;
		//	m_CurJumpState = JUMP_STATE::NONE;
		//}
	}
	else if (((m_CurJumpState == JUMP_STATE::JUMP_START || m_CurJumpState == JUMP_STATE::JUMPING) && KEY_RELEASED(KEY::Z)) || m_Rigidbody->IsOnGround())
	{
		// LOG(LOG_TYPE::DBG_LOG, L"NONE");
		m_JumpingTime = 0;
		m_CurJumpState = JUMP_STATE::NONE;
	}


	// Parry State 설정
	// ========================================================================

	// Parry 시작 조건
	if (!m_Rigidbody->IsOnGround() && KEY_JUST_PRESSED(KEY::Z) && m_ParryCount > 0)
	{
		parryTime = 0;
		parryTime += DT;
		m_ParryCount--;
		m_CurParryState = PARRY_STATE::PARRY;
	}

	else if (m_CurParryState == PARRY_STATE::PARRY || m_CurParryState == PARRY_STATE::PARRY_PINK)
	{
		// Parry 끝나는 조건
		if (m_ParryDuration < parryTime)
			m_CurParryState = PARRY_STATE::NONE;

		else
			parryTime += DT;
	}

	// Parry 끝나는 조건
	if (m_Rigidbody->IsOnGround() || m_CurBaseState == BASE_STATE::HITTED)
	{
		m_CurParryState = PARRY_STATE::NONE;
	}

	if (m_Rigidbody->IsOnGround())
		m_ParryCount = 1;
	

	// SHOOTING 설정
	// ========================================================================
	if (KEY_PRESSED(KEY::X))
	{
		m_CurActionState = ACTION_STATE::SHOOTING;
	}
	else
	{
		m_CurActionState = ACTION_STATE::NONE;
	}


	// ShootingDir 설정
	// ========================================================================
	{
		// 오른쪽을 보고 있는 경우
		if (m_bFacingRight)
		{
			if ((!leftPressed && !upPressed && !downPressed) || m_CurBaseState == BASE_STATE::DUCK)
				m_CurShootingDir = SHOOTING_DIR::RIGHT;
			else if (upPressed && !rightPressed)
				m_CurShootingDir = SHOOTING_DIR::UP;
			else if (downPressed && !rightPressed && (m_CurBaseState == BASE_STATE::FIXED || !m_Rigidbody->IsOnGround()))
				m_CurShootingDir = SHOOTING_DIR::DOWN;
			else if (upPressed && rightPressed)
				m_CurShootingDir = SHOOTING_DIR::UP_RIGHT;
			else if (downPressed && rightPressed && (m_CurBaseState == BASE_STATE::FIXED || !m_Rigidbody->IsOnGround()))
				m_CurShootingDir = SHOOTING_DIR::DOWN_RIGHT;
		}

		// 왼쪽을 보고 있는 경우
		if (!m_bFacingRight)
		{
			if ((!rightPressed && !upPressed && !downPressed) || m_CurBaseState == BASE_STATE::DUCK)
				m_CurShootingDir = SHOOTING_DIR::LEFT;
			else if (upPressed && !leftPressed)
				m_CurShootingDir = SHOOTING_DIR::UP;
			else if (downPressed && !leftPressed && (m_CurBaseState == BASE_STATE::FIXED || !m_Rigidbody->IsOnGround()))
				m_CurShootingDir = SHOOTING_DIR::DOWN;
			else if (upPressed && leftPressed)
				m_CurShootingDir = SHOOTING_DIR::UP_LEFT;
			else if (downPressed && leftPressed && (m_CurBaseState == BASE_STATE::FIXED || !m_Rigidbody->IsOnGround()))
				m_CurShootingDir = SHOOTING_DIR::DOWN_LEFT;
		}
	}
}

// ============================================================================================================================================================
// ========================== MoveAndAction() ===============================================================================================================
// ============================================================================================================================================================

void CPlayer::MoveAndAction()
{
	if (m_CurBaseState == BASE_STATE::HITTED)
		return;

	if ((KEY_RELEASED(KEY::RIGHT) && m_bFacingRight) || (KEY_RELEASED(KEY::LEFT) && !m_bFacingRight))
		m_Rigidbody->SetVelocity_X(0);

	//if (!KEY_PRESSED(KEY::RIGHT) && !KEY_PRESSED(KEY::LEFT))
	//	m_Rigidbody->SetVelocity_X(0);

	// 점프
	switch (m_CurJumpState)
	{
		case JUMP_STATE::NONE:
			break;
		case JUMP_STATE::JUMP_START:
			m_Rigidbody->AddVelocity(Vec2(0, -m_JumpSpeed));
			break;
		case JUMP_STATE::JUMPING:
		{
			if (m_JumpingTime < m_LowJumpKeyTime)
				break;
			else
				m_Rigidbody->AddForce(Vec2(0, -3100));
			break;
		}
		default:
			break;
	}

	// 기본 상태
	switch (m_CurBaseState)
	{
		case BASE_STATE::DUCK:
			m_Rigidbody->SetVelocity_X(0);
			break;
		case BASE_STATE::FIXED:
			m_Rigidbody->SetVelocity_X(0);
			break;
		case BASE_STATE::RUN:
		{
			if (m_bFacingRight)
				m_Rigidbody->AddVelocity(Vec2(m_RunSpeed, 0));
			else
				m_Rigidbody->AddVelocity(Vec2(-m_RunSpeed, 0));
		}
		break;
		case BASE_STATE::DASH:
		{
			if (m_bFacingRight)
				m_Rigidbody->SetVelocity(Vec2(m_DashSpeed, 0));
			else
				m_Rigidbody->SetVelocity(Vec2(-m_DashSpeed, 0));
		}
		break;
		case BASE_STATE::AIRBONE:
		{
			if (m_bFacingRight && KEY_PRESSED(KEY::RIGHT))
				m_Rigidbody->AddVelocity(Vec2(m_RunSpeed, 0));
			else if (KEY_PRESSED(KEY::LEFT))
				m_Rigidbody->AddVelocity(Vec2(-m_RunSpeed, 0));
			break;
		}
		case BASE_STATE::HITTED:
		{
			
			break;
		}
		case BASE_STATE::DEATH:
			break;
		default:
			break;
	}

	switch (m_CurActionState)
	{
		case ACTION_STATE::NONE:
			break;
		case ACTION_STATE::SHOOTING:
		{
			float shootingFrequency = 5;

			if ((1.f / shootingFrequency) <= timeSinceLastShot)
			{
				Shoot(m_CurShootingDir);
				timeSinceLastShot = 0;
			}
			break;
		}
		default:
			break;
	}

	timeSinceLastShot += DT;
}

// ============================================================================================================================================================
// ========================== UpdateAnimation() ===============================================================================================================
// ============================================================================================================================================================

void CPlayer::UpdateAnimation()
{
	// 패링 상태
	if (m_CurParryState != PARRY_STATE::NONE)
	{
		if (m_CurParryState == PARRY_STATE::PARRY)
		{
			if (m_bFacingRight)
				m_Animator->Play(L"cuphead_parry_R", true);
			else
				m_Animator->Play(L"cuphead_parry_L", true);
		}
		else
		{
			if (m_bFacingRight)
				m_Animator->PlayFromFrame(L"cuphead_parry_pink_R", true, m_Animator->GetCurAnimation()->GetCurFrameIdx());
			else
				m_Animator->PlayFromFrame(L"cuphead_parry_pink_L", true, m_Animator->GetCurAnimation()->GetCurFrameIdx());
		}
		return;
	}

	// 총쏘지 않는 상태
	if (m_CurActionState != ACTION_STATE::SHOOTING)
	{
		switch (m_CurBaseState)
		{
			case BASE_STATE::IDLE:
			{
				if (m_bFacingRight)
				{

					if (m_CurShootingDir == SHOOTING_DIR::UP)
						m_Animator->Play(L"cuphead_aim_up_R", true);
					else
						m_Animator->Play(L"cuphead_idle_R", true, true);
				}
				else
				{

					if (m_CurShootingDir == SHOOTING_DIR::UP)
						m_Animator->Play(L"cuphead_aim_up_L", true);
					else
						m_Animator->Play(L"cuphead_idle_L", true, true);
				}
				break;
			}
			case BASE_STATE::DUCK:
			{
				float duckingDuration = 0.5;

				if (m_PrevBaseState != BASE_STATE::DUCK)
					duckingTime = 0;

				if (m_PrevShootingDir != m_CurShootingDir || m_PrevActionState != m_CurActionState)
					duckingTime = duckingDuration;

				if (duckingTime < duckingDuration)
				{
					if (m_bFacingRight)
						m_Animator->Play(L"cuphead_duck_R", false);
					else
						m_Animator->Play(L"cuphead_duck_L", false);
				}
				else
				{
					if (m_bFacingRight)
						m_Animator->Play(L"cuphead_duck_idle_R", true, true);
					else
						m_Animator->Play(L"cuphead_duck_idle_L", true, true);
				}

				duckingTime += DT;
				break;
			}
			case BASE_STATE::FIXED:
			{
				switch (m_CurShootingDir)
				{
					case SHOOTING_DIR::LEFT:
						m_Animator->Play(L"cuphead_aim_straight_L", true, true);
						break;
					case SHOOTING_DIR::RIGHT:
						m_Animator->Play(L"cuphead_aim_straight_R", true, true);
						break;
					case SHOOTING_DIR::UP:
						if (m_bFacingRight)
							m_Animator->Play(L"cuphead_aim_up_R", true, true);
						else
							m_Animator->Play(L"cuphead_aim_up_L", true, true);
						break;
					case SHOOTING_DIR::DOWN:
						if (m_bFacingRight)
							m_Animator->Play(L"cuphead_aim_down_R", true, true);
						else
							m_Animator->Play(L"cuphead_aim_down_L", true, true);
						break;
					case SHOOTING_DIR::UP_LEFT:
						m_Animator->Play(L"cuphead_aim_diagonal_up_L", true, true);
						break;
					case SHOOTING_DIR::UP_RIGHT:
						m_Animator->Play(L"cuphead_aim_diagonal_up_R", true, true);
						break;
					case SHOOTING_DIR::DOWN_LEFT:
						m_Animator->Play(L"cuphead_aim_diagonal_down_L", true, true);
						break;
					case SHOOTING_DIR::DOWN_RIGHT:
						m_Animator->Play(L"cuphead_aim_diagonal_down_R", true, true);
						break;
					case SHOOTING_DIR::END:
						break;
					default:
						break;
				}

				break;
			}
			case BASE_STATE::RUN:
			{
				if (m_bFacingRight)
					m_Animator->Play(L"cuphead_run_R", true);
				else
					m_Animator->Play(L"cuphead_run_L", true);
				break;
			}
			case BASE_STATE::DASH:
			{
				if (m_bFacingRight)
					m_Animator->Play(L"cuphead_dash_R", true);
				else
					m_Animator->Play(L"cuphead_dash_L", true);
				break;
			}
			case BASE_STATE::AIRBONE:
			{
				if (m_bFacingRight)
					m_Animator->Play(L"cuphead_jump_R", true);
				else
					m_Animator->Play(L"cuphead_jump_L", true);
				break;
			}
			case BASE_STATE::DEATH:
				break;
			default:
				break;
		}
	}

	// 총쏘는 상태
	else
	{
		switch (m_CurBaseState)
		{
			case BASE_STATE::IDLE:
			{
				if (m_bFacingRight)
				{
					if (m_CurShootingDir == SHOOTING_DIR::RIGHT)
						m_Animator->Play(L"cuphead_shoot_straight_R", true);
					else if (m_CurShootingDir == SHOOTING_DIR::UP)
						m_Animator->Play(L"cuphead_shoot_up_R", true);
				}
				else
				{
					if (m_CurShootingDir == SHOOTING_DIR::LEFT)
						m_Animator->Play(L"cuphead_shoot_straight_L", true);
					else if (m_CurShootingDir == SHOOTING_DIR::UP)
						m_Animator->Play(L"cuphead_shoot_up_L", true);
				}
				break;
			}
			case BASE_STATE::DUCK:
			{
				float duckingDuration = 0.2f;

				if (m_PrevBaseState != BASE_STATE::DUCK)
					duckingTime = 0;

				if (m_PrevShootingDir != m_CurShootingDir || m_PrevActionState != m_CurActionState)
					duckingTime = duckingDuration;

				if (duckingTime < duckingDuration)
				{
					if (m_bFacingRight)
						m_Animator->Play(L"cuphead_duck_R", false);
					else
						m_Animator->Play(L"cuphead_duck_L", false);
				}
				else
				{
					if (m_bFacingRight)
						m_Animator->Play(L"cuphead_duck_shoot_R", true);
					else
						m_Animator->Play(L"cuphead_duck_shoot_L", true);
				}
				duckingTime += DT;

				break;
			}
			case BASE_STATE::FIXED:
			{
				switch (m_CurShootingDir)
				{
					case SHOOTING_DIR::LEFT:
						m_Animator->Play(L"cuphead_shoot_straight_L", true);
						break;
					case SHOOTING_DIR::RIGHT:
						m_Animator->Play(L"cuphead_shoot_straight_R", true);
						break;
					case SHOOTING_DIR::UP:
						if (m_bFacingRight)
							m_Animator->Play(L"cuphead_shoot_up_R", true);
						else
							m_Animator->Play(L"cuphead_shoot_up_L", true);
						break;
					case SHOOTING_DIR::DOWN:
						if (m_bFacingRight)
							m_Animator->Play(L"cuphead_shoot_down_R", true);
						else
							m_Animator->Play(L"cuphead_shoot_down_L", true);
						break;
					case SHOOTING_DIR::UP_LEFT:
						m_Animator->Play(L"cuphead_shoot_diagonal_up_L", true);
						break;
					case SHOOTING_DIR::UP_RIGHT:
						m_Animator->Play(L"cuphead_shoot_diagonal_up_R", true);
						break;
					case SHOOTING_DIR::DOWN_LEFT:
						m_Animator->Play(L"cuphead_shoot_diagonal_down_L", true);
						break;
					case SHOOTING_DIR::DOWN_RIGHT:
						m_Animator->Play(L"cuphead_shoot_diagonal_down_R", true);
						break;
					case SHOOTING_DIR::END:
						break;
					default:
						break;
				}
				break;
			}
			case BASE_STATE::RUN:
			{
				switch (m_CurShootingDir)
				{
					case SHOOTING_DIR::LEFT:
						m_Animator->Play(L"cuphead_run_shoot_L", true);
						break;
					case SHOOTING_DIR::RIGHT:
						m_Animator->Play(L"cuphead_run_shoot_R", true);
						break;
					case SHOOTING_DIR::UP:
						break;
					case SHOOTING_DIR::DOWN:
						break;
					case SHOOTING_DIR::UP_LEFT:
						m_Animator->Play(L"cuphead_run_shoot_diagonal_up_L", true);
						break;
					case SHOOTING_DIR::UP_RIGHT:
						m_Animator->Play(L"cuphead_run_shoot_diagonal_up_R", true);						
						break;
					case SHOOTING_DIR::DOWN_LEFT:
						break;
					case SHOOTING_DIR::DOWN_RIGHT:
						break;
					case SHOOTING_DIR::END:
						break;
					default:
						break;
				}
				break;
			}
			case BASE_STATE::DASH:
			{
				if (m_bFacingRight)
					m_Animator->Play(L"cuphead_dash_R", true);
				else
					m_Animator->Play(L"cuphead_dash_L", true);
				break;
			}
			case BASE_STATE::AIRBONE:
			{
				if (m_bFacingRight)
					m_Animator->Play(L"cuphead_jump_R", true);
				else
					m_Animator->Play(L"cuphead_jump_L", true);
				break;
			}
			case BASE_STATE::DEATH:
				break;
			default:
				break;
		}
	}
}

void CPlayer::Shoot(SHOOTING_DIR _dir)
{
	CMissile* pMissile = new CMissile;

	pMissile->SetScale(20, 20);

	switch (_dir)
	{
		case SHOOTING_DIR::LEFT:
			pMissile->SetPos(Vec2(GetPos() + Vec2(-GetScale().x * 0.5f, 0)));
			pMissile->SetAngle(PI);
			break;
		case SHOOTING_DIR::RIGHT:
			pMissile->SetPos(Vec2(GetPos() + Vec2(GetScale().x * 0.5f, 0)));
			pMissile->SetAngle(0);
			break;
		case SHOOTING_DIR::UP:
			pMissile->SetPos(Vec2(GetPos() + Vec2(0, -GetScale().y * 0.5f)));
			pMissile->SetAngle(-0.5f * PI);
			break;
		case SHOOTING_DIR::DOWN:
			pMissile->SetPos(Vec2(GetPos() + Vec2(0, GetScale().y * 0.5f)));
			pMissile->SetAngle(0.5f * PI);
			break;
		case SHOOTING_DIR::UP_LEFT:
			pMissile->SetPos(Vec2(GetPos() + Vec2(-GetScale().x * 0.5f, -GetScale().y * 0.5f)));
			pMissile->SetAngle(-0.75f * PI);
			break;
		case SHOOTING_DIR::UP_RIGHT:
			pMissile->SetPos(Vec2(GetPos() + Vec2(GetScale().x * 0.5f, -GetScale().y * 0.5f)));
			pMissile->SetAngle(-0.25f * PI);
			break;
		case SHOOTING_DIR::DOWN_LEFT:
			pMissile->SetPos(Vec2(GetPos() + Vec2(-GetScale().x * 0.5f, GetScale().y * 0.5f)));
			pMissile->SetAngle(0.75f * PI);
			break;
		case SHOOTING_DIR::DOWN_RIGHT:
			pMissile->SetPos(Vec2(GetPos() + Vec2(GetScale().x * 0.5f, GetScale().y * 0.5f)));
			pMissile->SetAngle(0.25f * PI);
			break;
		case SHOOTING_DIR::END:
			break;
		default:
			break;
	}


	pMissile->SetName(L"Player Missile");

	SpawnObject(CLevelMgr::GetInstance().GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);
}

void CPlayer::EnterGround()
{
	LOG(LOG_TYPE::DBG_WARNING, L"Grounded!!");

	m_bAirboneDashed = false;
}

void CPlayer::LeaveGround()
{
	LOG(LOG_TYPE::DBG_WARNING, L"AirBoned!!");
}

void CPlayer::render()
{
	// !디버깅
	if (KEY_JUST_PRESSED(KEY::H))
		m_bInvincibleState = !m_bInvincibleState;
	// ~디버깅

	auto anim = m_Animator->GetCurAnimation();

	// 현재 프레임 정보
	const tAnimationFrame& frm = anim->m_vecAnimFrame[anim->m_CurFrameIdx];

	// 애니메이션을 재생하고 있는 오브젝트
	CObj* pOwnerObj = m_Animator->GetOwner();

	// 오브젝트 위치
	Vec2 vRenderPos = pOwnerObj->GetRenderPos();

	const float ALPHA_MAX = 255.f;

	// 무적모드 인지 아닌지에 맞춰서 알파값 적용
	if (m_bInvincibleState)
	{
		if (ALPHA_MAX < alpha)
		{
			alpha = ALPHA_MAX;
			dir *= -1.f;
		}
		else if (alpha < 0.f)
		{
			alpha = 0;
			dir *= -1.f;
		}

		alpha += DT * 800.f * dir;
	}
	else
		alpha = ALPHA_MAX;

	// AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)alpha;
	bf.AlphaFormat = AC_SRC_ALPHA;

	// 현재 프레임 이미지를 오브젝트 위치에 렌더링
	AlphaBlend(SUBDC,
		(int)(vRenderPos.x - frm.SliceSize.x / 2.f + frm.Offset.x), (int)(vRenderPos.y - frm.SliceSize.y / 2.f + frm.Offset.y), (int)frm.SliceSize.x, (int)frm.SliceSize.y,
		anim->m_Atlas->GetDC(), (int)frm.PosInAtlas.x, (int)frm.PosInAtlas.y, (int)frm.SliceSize.x, (int)frm.SliceSize.y,
		bf);


	// !디버깅
	StatusRender();
}

void CPlayer::StatusRender()
{
	if (!CDbgRenderer::GetInstance().IsDBGMode())
		return;

	wstring strShootingDir = L"Shooting Dir : ";
	switch (m_CurShootingDir)
	{
		case SHOOTING_DIR::LEFT:
			strShootingDir += L"LEFT";
			break;
		case SHOOTING_DIR::RIGHT:
			strShootingDir += L"RIGHT";
			break;
		case SHOOTING_DIR::UP:
			strShootingDir += L"UP";
			break;
		case SHOOTING_DIR::DOWN:
			strShootingDir += L"DOWN";
			break;
		case SHOOTING_DIR::UP_LEFT:
			strShootingDir += L"UP_LEFT";
			break;
		case SHOOTING_DIR::UP_RIGHT:
			strShootingDir += L"UP_RIGHT";
			break;
		case SHOOTING_DIR::DOWN_LEFT:
			strShootingDir += L"DOWN_LEFT";
			break;
		case SHOOTING_DIR::DOWN_RIGHT:
			strShootingDir += L"DOWN_RIGHT";
			break;
		case SHOOTING_DIR::END:
			break;
		default:
			break;
	}

	wstring strBaseState = L"Base State : ";
	switch (m_CurBaseState)
	{
		case BASE_STATE::IDLE:
			strBaseState += L"IDLE";
			break;
		case BASE_STATE::DUCK:
			strBaseState += L"DUCK";
			break;
		case BASE_STATE::FIXED:
			strBaseState += L"FIXED";
			break;
		case BASE_STATE::RUN:
			strBaseState += L"RUN";
			break;
		case BASE_STATE::DASH:
			strBaseState += L"DASH";
			break;
		case BASE_STATE::AIRBONE:
			strBaseState += L"AIRBONE";
			break;
		case BASE_STATE::HITTED:
			strBaseState += L"HITTED";
			break;
		case BASE_STATE::DEATH:
			strBaseState += L"DEATH";
			break;
		default:
			break;
	}

	wstring strActionState = L"Action State : ";
	switch (m_CurActionState)
	{
		case ACTION_STATE::NONE:
			strActionState += L"NONE";
			break;
		case ACTION_STATE::SHOOTING:
			strActionState += L"SHOOTING";
			break;
		default:
			break;
	}

	TextOut(SUBDC, 10, 2, strShootingDir.c_str(), (int)strShootingDir.length());
	TextOut(SUBDC, 10, 17, strBaseState.c_str(), (int)strBaseState.length());
	TextOut(SUBDC, 10, 32, strActionState.c_str(), (int)strActionState.length());
}