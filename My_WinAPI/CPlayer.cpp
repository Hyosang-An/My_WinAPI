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
	m_ShootingDir(SHOOTING_DIR::RIGHT),
	m_CurBaseState(BASE_STATE::IDLE),
	m_CurActionState(ACTION_STATE::NONE),
	m_PrevShootingDir(SHOOTING_DIR::RIGHT),
	m_PrevBaseState(m_CurBaseState),
	m_PrevActionState(ACTION_STATE::NONE)
{
	m_eType = LAYER_TYPE::PLAYER;

	m_HeadCol = AddComponent(new CCollider);
	m_HeadCol->SetName(L"Head Collider");
	m_HeadCol->SetOffsetPos(Vec2(0, -80));
	m_HeadCol->SetScale(Vec2(30, 30));

	m_BodyCol = AddComponent(new CCollider);
	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 0.f));
	m_BodyCol->SetScale(Vec2(60.f, 60.f));

	m_Rigidbody = AddComponent(new CRigidbody);
	m_Rigidbody->SetMinWalkSpeed(200);
	m_Rigidbody->SetMaxWalkSpeed(200);
	m_Rigidbody->SetFriction(2000);

	m_Animator = AddComponent(new CAnimator);


	// .json���� ���� �ҷ�����
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

	//// Aim
	//m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Aim\\Diagonal Down\\cuphead_aim_diagonal_down_R.json", 10);
	//m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Aim\\Diagonal Up\\cuphead_aim_diagonal_up_R.json", 10);
	//m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Aim\\Down\\cuphead_aim_down_R.json", 10);
	//m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Aim\\Straight\\cuphead_aim_straight_R.json", 10);
	//m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Aim\\Up\\cuphead_aim_up_R.json", 10);

	//	// Duck
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Duck\\Idle\\cuphead_duck_idle_R.json", 12);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Duck\\Idle\\cuphead_duck_R.json", 14);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Duck\\Shoot\\cuphead_duck_shoot_boil_R.json", 12);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Duck\\Shoot\\cuphead_duck_shoot_R.json", 12);

	//	// Dash
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Dash\\Ground\\cuphead_dash_R.json", 12);





	//	// L

	//	//Idle
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Idle\\cuphead_idle_L.json", 10);
	//					
	//	// Run
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Run\\Normal\\cuphead_run_L.json", 24);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Run\\Shooting\\Diagonal Up\\cuphead_run_shoot_diagonal_up_L.json", 24);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Run\\Shooting\\Straight\\cuphead_run_shoot_L.json", 24);
	//	
	//	// Shoot
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_down_L.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Diagonal Up\\cuphead_shoot_diagonal_up_L.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Down\\cuphead_shoot_down_L.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Straight\\cuphead_shoot_straight_L.json", 6);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Shoot\\Up\\cuphead_shoot_up_L.json", 6);
	//				
	//// Aim
	//m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Aim\\Diagonal Down\\cuphead_aim_diagonal_down_L.json", 10);
	//m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Aim\\Diagonal Up\\cuphead_aim_diagonal_up_L.json", 10);
	//m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Aim\\Down\\cuphead_aim_down_L.json", 10);
	//m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Aim\\Straight\\cuphead_aim_straight_L.json", 10);
	//m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Aim\\Up\\cuphead_aim_up_L.json", 10);
	//				
	//	// Duck
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Duck\\Idle\\cuphead_duck_idle_L.json", 12);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Duck\\Idle\\cuphead_duck_L.json", 14);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Duck\\Shoot\\cuphead_duck_shoot_boil_L.json", 12);
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Duck\\Shoot\\cuphead_duck_shoot_L.json", 12);

	//	// Dash
	//	m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_L\\Dash\\Ground\\cuphead_dash_L.json", 12);




	//	m_Animator->Play(L"cuphead_idle_R", true, true);
	//}

	// .anim���� ���� �ҷ�����
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
	}

	m_Animator->Play(L"cuphead_idle_R", true, true);
}

CPlayer::~CPlayer()
{
}

void CPlayer::UpdateState()
{

	// ���� �뽬 ����� ���
	if (m_CurBaseState == BASE_STATE::DASH)
	{
		static float DashTime = 0;
		
		if (m_DashDuration < DashTime)
		{
			DashTime = 0;
			if (m_Rigidbody->IsOnGround())
				m_CurBaseState = BASE_STATE::JUMP;
			else
				m_CurBaseState = BASE_STATE::IDLE;
		}
		DashTime += DT;

		return;
	}

	bool leftPressed = KEY_PRESSED(KEY::LEFT);
	bool rightPressed = KEY_PRESSED(KEY::RIGHT);
	bool upPressed = KEY_PRESSED(KEY::UP);
	bool downPressed = KEY_PRESSED(KEY::DOWN);


	// �ٶ󺸴� ���� ��ȯ (�� ���̽� ��� �ƴ϶�� ���� ���� ����)
	if (m_bFacingRight && leftPressed && !rightPressed)
		m_bFacingRight = false;
	else if (!m_bFacingRight && !leftPressed && rightPressed)
		m_bFacingRight = true;


	// BASE_STATE ����
	{
		// �� ���� �����鼭 �뽬�� �ƴ� ���
		if (m_Rigidbody->IsOnGround())
		{
			// ����Ű �ȴ����� Idle
			if (!leftPressed && !rightPressed && !upPressed && !downPressed)
				m_CurBaseState = BASE_STATE::IDLE;

			// �Ʒ� Ű ������ ������ duck ���
			else if (downPressed)
				m_CurBaseState = BASE_STATE::DUCK;

			// �¿� ����Ű ������ run
			else if (leftPressed || rightPressed)
				m_CurBaseState = BASE_STATE::RUN;

			// ZŰ ������ ����
			if (KEY_PRESSED(KEY::_Z) && !(m_CurBaseState == BASE_STATE::DASH))
				m_CurBaseState = BASE_STATE::JUMP;

			// CŰ ������ ���� ���
			if (KEY_PRESSED(KEY::_C))
				m_CurBaseState = BASE_STATE::FIXED;

			// Shift Ű ������ �뽬
			if (KEY_JUST_PRESSED(KEY::SHIFT))
				m_CurBaseState = BASE_STATE::DASH;
		}

	}


	// ACTION_STATE ����
	// �ѽ��
	if (KEY_PRESSED(KEY::_X))
	{
		AddActionState(ACTION_STATE::SHOOTING);
	}
	else
	{
		RemoveActionState(ACTION_STATE::SHOOTING);
	}

	// ShootingDir ����
	{
		// �������� ���� �ִ� ���
		if (m_bFacingRight)
		{
			if (!leftPressed && !upPressed && !downPressed)
				m_ShootingDir = SHOOTING_DIR::RIGHT;
			else if (upPressed && !rightPressed)
				m_ShootingDir = SHOOTING_DIR::UP;
			else if (downPressed && !rightPressed && (m_CurBaseState == BASE_STATE::FIXED || !m_Rigidbody->IsOnGround()))
				m_ShootingDir = SHOOTING_DIR::DOWN;
			else if (upPressed && rightPressed)
				m_ShootingDir = SHOOTING_DIR::UP_RIGHT;
			else if (downPressed && rightPressed && (m_CurBaseState == BASE_STATE::FIXED || !m_Rigidbody->IsOnGround()))
				m_ShootingDir = SHOOTING_DIR::DOWN_RIGHT;
		}

		// ������ ���� �ִ� ���
		if (!m_bFacingRight)
		{
			if (!rightPressed && !upPressed && !downPressed)
				m_ShootingDir = SHOOTING_DIR::LEFT;
			else if (upPressed && !leftPressed)
				m_ShootingDir = SHOOTING_DIR::UP;
			else if (downPressed && !leftPressed && (m_CurBaseState == BASE_STATE::FIXED || !m_Rigidbody->IsOnGround()))
				m_ShootingDir = SHOOTING_DIR::DOWN;
			else if (upPressed && leftPressed)
				m_ShootingDir = SHOOTING_DIR::UP_LEFT;
			else if (downPressed && leftPressed && (m_CurBaseState == BASE_STATE::FIXED || !m_Rigidbody->IsOnGround()))
				m_ShootingDir = SHOOTING_DIR::DOWN_LEFT;
		}
	}
}

void CPlayer::Move()
{
	float runspeed = 50;
	float dashspeed = 300;

	switch (m_CurBaseState)
	{
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
		case BASE_STATE::JUMP:
			break;
		case BASE_STATE::DEATH:
			break;
		default:
			break;
	}
}

void CPlayer::UpdateAnimation()
{
	// ���� ������ �Ͼ�� ������ ���� �ִϸ��̼� ��� ���
	//if (m_PrevShootingDir == m_ShootingDir && m_PrevBaseState == m_CurBaseState && m_PrevActionState == m_CurActionState)
	//	return;

	// �ѽ��� �ʴ� ����
	if (!IsInActionState(ACTION_STATE::SHOOTING))
	{
		switch (m_CurBaseState)
		{
			case BASE_STATE::IDLE:
			{
				if (m_bFacingRight)
					m_Animator->Play(L"cuphead_idle_R", true, true);
				else
					m_Animator->Play(L"cuphead_idle_L", true, true);
				break;
			}
				
			case BASE_STATE::DUCK:
			{
				float duckingDuration = 0.5;
				static float duckingTime = 0;

				if (m_PrevBaseState != BASE_STATE::DUCK)
					duckingTime = 0;

				if (duckingTime < duckingDuration)
				{
					if (m_bFacingRight)
						m_Animator->Play(L"cuphead_duck_R", true);
					else
						m_Animator->Play(L"cuphead_duck_L", true);
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
				switch (m_ShootingDir)
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
			case BASE_STATE::JUMP:
				break;
			case BASE_STATE::DEATH:
				break;
			default:
				break;
		}
	}

	// �ѽ�� ����
	else
	{
		switch (m_CurBaseState)
		{
			case BASE_STATE::IDLE:
				break;
			case BASE_STATE::DUCK:
				break;
			case BASE_STATE::FIXED:
				break;
			case BASE_STATE::RUN:
				break;
			case BASE_STATE::DASH:
				break;
			case BASE_STATE::JUMP:
				break;
			case BASE_STATE::DEATH:
				break;
			default:
				break;
		}
	}
}


void CPlayer::begin()
{
}

void CPlayer::tick()
{
	UpdateState();
	UpdateAnimation();
	Move();



	m_PrevShootingDir = m_ShootingDir;
	m_PrevBaseState = m_CurBaseState;
	m_PrevActionState = m_CurActionState;
}

void CPlayer::render()
{
	CObj::render();

	wchar_t szBuff[255]{};
	swprintf_s(szBuff, L"ShootingDir : %dBase State : %d, Action State : %d ", (int)m_ShootingDir, (int)m_CurBaseState, (int)m_CurActionState);
	//swprintf_s(szBuff, L"ShootingDir :  Base State : , Action State : ");

	wstring strShootingDir = L"Shooting Dir : " + std::to_wstring((int)m_ShootingDir);
	wstring strBaseState = L"Base State : " + std::to_wstring((int)m_CurBaseState);
	wstring strActionState = L"Action State : " + std::to_wstring((int)m_CurActionState);

	TextOut(SUBDC, 10, 10, strShootingDir.c_str(), strShootingDir.length());
	TextOut(SUBDC, 10, 25, strBaseState.c_str(), strBaseState.length());
	TextOut(SUBDC, 10, 40, strActionState.c_str(), strActionState.length());
}


	//=====================================================================================
	// ���Ž� �ڵ�


	//void CPlayer::tick()
	//{
	//	auto vPos = GetPos();
	//
	//	auto prevPos = vPos;
	//
	//	bool leftPressed = KEY_PRESSED(KEY::LEFT);
	//	bool rightPressed = KEY_PRESSED(KEY::RIGHT);
	//	bool upPressed = KEY_PRESSED(KEY::UP);
	//	bool downPressed = KEY_PRESSED(KEY::DOWN);
	//
	//	// ���� �Է¿� ���� ó��
	//	static int lastInputDirection = 0;  // ������ �Է� ������ ����ϱ� ���� ����
	//	static int lastState = 0;			// ������ ���¸� ����ϱ� ���� ����
	//
	//	if (KEY_JUST_PRESSED(KEY::UP)) {
	//		lastInputDirection = 1; // ����
	//	}
	//	if (KEY_JUST_PRESSED(KEY::DOWN)) {
	//		lastInputDirection = 2; // �Ʒ���
	//	}
	//	if (KEY_JUST_PRESSED(KEY::LEFT)) {
	//		lastInputDirection = 3; // ����
	//	}
	//	if (KEY_JUST_PRESSED(KEY::RIGHT)) {
	//		lastInputDirection = 4; // ������
	//	}
	//
	//	// ����-�� �밢�� �̵� �� �ִϸ��̼� ó��
	//	if (leftPressed && upPressed) {
	//		vPos.x -= m_fSpeed * DT / sqrtf(2);
	//		vPos.y -= m_fSpeed * DT / sqrtf(2);
	//		if (lastInputDirection == 1)
	//		{
	//			m_Animator->Play(L"WALK_UP", true);
	//			lastState = 1;
	//		}
	//		if (lastInputDirection == 3)
	//		{
	//			m_Animator->Play(L"WALK_LEFT", true);
	//			lastState = 3;
	//		}
	//	}
	//	// ����-�Ʒ� �밢�� �̵� �� �ִϸ��̼� ó��
	//	else if (leftPressed && downPressed) {
	//		vPos.x -= m_fSpeed * DT / sqrtf(2);
	//		vPos.y += m_fSpeed * DT / sqrtf(2);
	//		if (lastInputDirection == 2)
	//		{
	//			m_Animator->Play(L"WALK_DOWN", true);
	//			lastState = 2;
	//		}
	//		if (lastInputDirection == 3)
	//		{
	//			m_Animator->Play(L"WALK_LEFT", true);
	//			lastState = 3;
	//		}
	//	}
	//	// ������-�� �밢�� �̵� �� �ִϸ��̼� ó��
	//	else if (rightPressed && upPressed) {
	//		vPos.x += m_fSpeed * DT / sqrtf(2);
	//		vPos.y -= m_fSpeed * DT / sqrtf(2);
	//		if (lastInputDirection == 1)
	//		{
	//			m_Animator->Play(L"WALK_UP", true);
	//			lastState = 1;
	//		}
	//		if (lastInputDirection == 4)
	//		{
	//			m_Animator->Play(L"WALK_RIGHT", true);
	//			lastState = 4;
	//		}
	//	}
	//	// ������-�Ʒ� �밢�� �̵� �� �ִϸ��̼� ó��
	//	else if (rightPressed && downPressed) {
	//		vPos.x += m_fSpeed * DT / sqrtf(2);
	//		vPos.y += m_fSpeed * DT / sqrtf(2);
	//		if (lastInputDirection == 2)
	//		{
	//			m_Animator->Play(L"WALK_DOWN", true);
	//			lastState = 2;
	//		}
	//		if (lastInputDirection == 4)
	//		{
	//			m_Animator->Play(L"WALK_RIGHT", true);
	//			lastState = 4;
	//		}
	//	}
	//
	//	// ���� ���� �̵� �� �ִϸ��̼� ó��
	//	if (!upPressed && !downPressed && !rightPressed && leftPressed) {
	//		vPos.x -= m_fSpeed * DT;
	//		m_Animator->Play(L"WALK_LEFT", true);
	//		lastState = 3;
	//	}
	//	else if (!upPressed && !downPressed && !leftPressed && rightPressed) {
	//		vPos.x += m_fSpeed * DT;
	//		m_Animator->Play(L"WALK_RIGHT", true);
	//		lastState = 4;
	//	}
	//	else if (!leftPressed && !rightPressed && !downPressed && upPressed) {
	//		vPos.y -= m_fSpeed * DT;
	//		m_Animator->Play(L"WALK_UP", true);
	//		lastState = 1;
	//	}
	//	else if (!leftPressed && !rightPressed && !upPressed && downPressed) {
	//		vPos.y += m_fSpeed * DT;
	//		m_Animator->Play(L"WALK_DOWN", true);
	//		lastState = 2;
	//	}
	//
	//	// ��� �̵� Ű�� ������ �ʾ��� �� IDLE �ִϸ��̼� ó��
	//	if (prevPos == vPos)
	//	{
	//		switch (lastState) {
	//			case 1: // ������ ������ ����
	//				m_Animator->Play(L"IDLE_UP", true);
	//				break;
	//			case 2: // ������ ������ �Ʒ���
	//				m_Animator->Play(L"IDLE_DOWN", true);
	//				break;
	//			case 3: // ������ ������ ����
	//				m_Animator->Play(L"IDLE_LEFT", true);
	//				break;
	//			case 4: // ������ ������ ������
	//				m_Animator->Play(L"IDLE_RIGHT", true);
	//				break;
	//			default:
	//				// �⺻ IDLE �ִϸ��̼� ó��
	//				//m_Animator->Play(L"WALK_DOWN", true);
	//				break;
	//		}
	//
	//		lastState = 0;
	//	}
	//
	//	SetPos(vPos);
	//
	//	if (KEY_JUST_PRESSED(KEY::SPACE))
	//	{
	//		CMissile* pMissile = new CGuidedMissile;
	//
	//		pMissile->SetPos(Vec2(GetPos() + Vec2(0, -GetScale().y * 0.5f)));
	//		pMissile->SetScale(20, 20);
	//		//pMissile->SetAngle(-3.141592f * 0.5);
	//		pMissile->SetName(L"Player Guided Missile");
	//
	//		SpawnObject(CLevelMgr::GetInstance().GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);
	//
	//		/*tDbgLog log{};
	//		log.Type = LOG_TYPE::DBG_LOG;
	//		log.strLog = L"!! �̻��� �߻� !!";
	//		CDbgRenderer::GetInstance().AddDbgLog(log);*/
	//
	//		LOG(LOG_TYPE::DBG_WARNING, L"@@ �̻��� �߻� @@");
	//	}
	//}





