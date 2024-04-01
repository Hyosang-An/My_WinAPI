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

CPlayer::CPlayer() :
	m_fSpeed(500.f),
	m_Texture{},
	m_bFacingRight(true),
	m_CurShootingDir(SHOOTING_DIR::RIGHT),
	m_CurBaseState(BASE_STATE::IDLE),
	m_CurActionState(ACTION_STATE::NONE),
	m_PrevShootingDir(SHOOTING_DIR::RIGHT),
	m_PrevBaseState(m_CurBaseState),
	m_PrevActionState(ACTION_STATE::NONE)
{
	m_eType = LAYER_TYPE::PLAYER;

	m_Rigidbody = AddComponent(new CRigidbody);
	m_Rigidbody->SetMaxWalkSpeed(200);
	m_Rigidbody->SetFriction(2000);
	m_Rigidbody->SetMaxGravitySpeed(800);


	// !!중요!! Collider가 Rigidbody보다 항상 컴포넌트 벡터 상에서 뒤에 위치해야 함!! 그래야 최종 오브젝트 위치를 반영하여 Collider 위치 업데이트 가능
	m_PlayerCollider = AddComponent(new CCollider);
	m_PlayerCollider->SetName(L"Player Collider");
	m_PlayerCollider->SetOffsetPos(Vec2(0.f, 0.f));
	m_PlayerCollider->SetScale(Vec2(60.f, 100.f));


	
	// 콜백함수 설정
	m_Rigidbody->SetGroundCallbackFunc([this]() {this->EnterGround(); });
	m_Rigidbody->SetAirCallbackFunc([this]() {this->LeaveGround(); });

	m_Animator = AddComponent(new CAnimator);


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

void CPlayer::UpdateState()
{
	// Hitted 및 무적 상태 설정
	// ========================================================================
	static float invincibleTime = 0;
	if (m_CurActionState == ACTION_STATE::HITTED)
	{
		if (m_PrevActionState != ACTION_STATE::HITTED)
		{
			invincibleTime = 0;
			m_bInvincibleState = true;
		}

		invincibleTime += DT;

		static float HittedTime = 0;
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
		static float DashTime = 0;

		if (m_DashDuration < DashTime)
		{
			DashTime = 0;
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
			// 방향키 안누르면 Idle
			if (!leftPressed && !rightPressed && !upPressed && !downPressed)
				m_CurBaseState = BASE_STATE::IDLE;

			// 아래 키 누르면 무조건 duck 모드
			else if (downPressed)
				m_CurBaseState = BASE_STATE::DUCK;

			// 좌우 방향키 누르면 run
			else if (leftPressed || rightPressed)
				m_CurBaseState = BASE_STATE::RUN;

			// C키 누르면 고정 모드
			if (KEY_PRESSED(KEY::_C))
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
	}

	// 플랫폼 내려가기
	if (m_CurBaseState == BASE_STATE::DUCK && m_bOnPlatform && KEY_JUST_PRESSED(KEY::_Z))
	{
		m_bOnPlatform = false;
		m_Rigidbody->SetGround(false);
		return;
	}


	// Jump State 설정
	// ========================================================================
	static float m_JumpingTime = 0;
	if (m_Rigidbody->IsOnGround() && KEY_JUST_PRESSED(KEY::_Z))
	{
		LOG(LOG_TYPE::DBG_WARNING, L"JUMP_START");
		m_JumpingTime = 0;
		m_CurJumpState = JUMP_STATE::JUMP_START;
	}
	else if ((m_CurJumpState == JUMP_STATE::JUMP_START || m_CurJumpState == JUMP_STATE::JUMPING) && KEY_PRESSED(KEY::_Z))
	{
		LOG(LOG_TYPE::DBG_LOG, L"JUMPING");
		m_CurJumpState = JUMP_STATE::JUMPING;
		m_JumpingTime += DT;

		if (m_HighJumpKeyTime < m_JumpingTime)
		{
			LOG(LOG_TYPE::DBG_ERROR, L"NONE");
			m_JumpingTime = 0;
			m_CurJumpState = JUMP_STATE::NONE;
		}
	}
	else if ((m_CurJumpState == JUMP_STATE::JUMPING && KEY_RELEASED(KEY::_Z)) || m_Rigidbody->IsOnGround())
	{
		LOG(LOG_TYPE::DBG_LOG, L"NONE");
		m_JumpingTime = 0;
		m_CurJumpState = JUMP_STATE::NONE;
	}


	// Parry State 설정
	// ========================================================================
	static float parryTime = 0;

	// Parry 시작 조건
	if (!m_Rigidbody->IsOnGround() && KEY_JUST_PRESSED(KEY::_Z) && m_ParryCount > 0)
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
	if (m_Rigidbody->IsOnGround() || m_CurActionState == ACTION_STATE::HITTED)
	{
		m_CurParryState = PARRY_STATE::NONE;
	}

	if (m_Rigidbody->IsOnGround())
		m_ParryCount = 1;
	

	// SHOOTING 설정
	// ========================================================================
	if (KEY_PRESSED(KEY::_X))
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

void CPlayer::MoveAndAction()
{
	float runspeed = 200;
	float dashspeed = 300;

	if (!KEY_PRESSED(KEY::RIGHT) && !KEY_PRESSED(KEY::LEFT))
		m_Rigidbody->SetVelocity_X(0);

	// 점프
	switch (m_CurJumpState)
	{
		case JUMP_STATE::NONE:
			break;
		case JUMP_STATE::JUMP_START:
			m_Rigidbody->AddVelocity(Vec2(0, -300));
			break;
		case JUMP_STATE::JUMPING:
			m_Rigidbody->AddForce(Vec2(0, -300));
			break;
		default:
			break;
	}

	// 기본 상태
	switch (m_CurBaseState)
	{
		case BASE_STATE::FIXED:
			m_Rigidbody->SetVelocity_X(0);
			break;
		case BASE_STATE::RUN:
		{
			if (m_bFacingRight)
				m_Rigidbody->AddVelocity(Vec2(runspeed, 0));
			else
				m_Rigidbody->AddVelocity(Vec2(-runspeed, 0));
		}
		break;
		case BASE_STATE::DASH:
		{
			if (m_bFacingRight)
				m_Rigidbody->AddVelocity(Vec2(dashspeed, 0));
			else
				m_Rigidbody->AddVelocity(Vec2(-dashspeed, 0));
		}
		break;
		case BASE_STATE::AIRBONE:
		{
			if (m_bFacingRight && KEY_PRESSED(KEY::RIGHT))
				m_Rigidbody->AddVelocity(Vec2(runspeed, 0));
			else if (KEY_PRESSED(KEY::LEFT))
				m_Rigidbody->AddVelocity(Vec2(-runspeed, 0));
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
			static float timeSinceLastShot = 0;

			if ((1.f / shootingFrequency) <= timeSinceLastShot)
			{
				Shoot(m_CurShootingDir);
				timeSinceLastShot = 0;
			}

			timeSinceLastShot += DT;
			break;
		}
		case ACTION_STATE::HITTED:
			break;
		default:
			break;
	}
}

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
				static float duckingTime = 0;

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
				float duckingDuration = 0.2;
				static float duckingTime = 0;

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
	CObj::render();

	wchar_t szBuff[255]{};
	swprintf_s(szBuff, L"ShootingDir : %dBase State : %d, Action State : %d ", (int)m_CurShootingDir, (int)m_CurBaseState, (int)m_CurActionState);

	wstring strShootingDir = L"Shooting Dir : " + std::to_wstring((int)m_CurShootingDir);
	wstring strBaseState = L"Base State : " + std::to_wstring((int)m_CurBaseState);
	wstring strActionState = L"Action State : " + std::to_wstring((int)m_CurActionState);

	TextOut(SUBDC, 10, 10, strShootingDir.c_str(), strShootingDir.length());
	TextOut(SUBDC, 10, 25, strBaseState.c_str(), strBaseState.length());
	TextOut(SUBDC, 10, 40, strActionState.c_str(), strActionState.length());
}