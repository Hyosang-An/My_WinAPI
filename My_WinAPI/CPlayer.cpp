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
	m_PrevBaseState(m_CurBaseState)
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
	m_Rigidbody->SetMinWalkSpeed(0);
	m_Rigidbody->SetMaxWalkSpeed(400);
	m_Rigidbody->SetFriction(2000);

	m_Animator = AddComponent(new CAnimator);

	{
		CTexture* pAtlas = CAssetMgr::GetInstance().LoadTexture(L"PlayerAtlasTexture", L"texture\\link.png");

		//m_Animator->CreateAnimation(L"IDLE_DOWN", pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 130.f), 3, 10)->Save(L"animation\\player\\");
		//m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlas, Vec2(0.f, 130.f), Vec2(120.f, 130.f), 3, 10)->Save(L"animation\\player\\");
		//m_Animator->CreateAnimation(L"IDLE_UP", pAtlas, Vec2(0.f, 260.f), Vec2(120.f, 130.f), 1, 1)->Save(L"animation\\player\\");
		//m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.f), 3, 1)->Save(L"animation\\player\\");
		//
		//m_Animator->CreateAnimation(L"WALK_DOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.f), 10, 18)->Save(L"animation\\player\\");
		//m_Animator->CreateAnimation(L"WALK_LEFT", pAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.f), 10, 18)->Save(L"animation\\player\\");
		//m_Animator->CreateAnimation(L"WALK_UP", pAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.f), 10, 18)->Save(L"animation\\player\\");
		//m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.f), 10, 18)->Save(L"animation\\player\\");

		//m_Animator->LoadAnimation(L"animation\\player\\WALK_DOWN.anim");
		//m_Animator->LoadAnimation(L"animation\\player\\WALK_RIGHT.anim");
		//m_Animator->LoadAnimation(L"animation\\player\\WALK_LEFT.anim");
		//m_Animator->LoadAnimation(L"animation\\player\\WALK_UP.anim");
		//m_Animator->LoadAnimation(L"animation\\player\\IDLE_DOWN.anim");
		//m_Animator->LoadAnimation(L"animation\\player\\IDLE_LEFT.anim");
		//m_Animator->LoadAnimation(L"animation\\player\\IDLE_UP.anim");
		//m_Animator->LoadAnimation(L"animation\\player\\IDLE_RIGHT.anim");

		//m_Animator->Play(L"IDLE_DOWN", true);
	}

	{
		//m_Animator->CreateAnimationByJSON(L"animation\\Cuphead\\Cuphead_R\\Run\\Normal\\cuphead_run_R.json", 30);
		//m_Animator->FindAnimation(L"cuphead_run_R")->Save(L"animation\\Cuphead\\Cuphead_R\\Run\\Normal");		
		
		m_Animator->LoadAnimation(L"animation\\Cuphead\\Cuphead_R\\Run\\Normal\\cuphead_run_R.anim");
		m_Animator->Play(L"cuphead_run_R", true);
	}


	//m_Texture = CAssetMgr::GetInstance().LoadTexture(L"PlayerTexture", L"texture\\Character.png");


}

CPlayer::~CPlayer()
{
}

void CPlayer::UpdateState()
{
	m_PrevBaseState = m_CurBaseState;

	bool leftPressed = KEY_PRESSED(KEY::LEFT);
	bool rightPressed = KEY_PRESSED(KEY::RIGHT);
	bool upPressed = KEY_PRESSED(KEY::UP);
	bool downPressed = KEY_PRESSED(KEY::DOWN);


	// 바라보는 방향 전환 (두 케이스 모두 아니라면 기존 방향 유지)
	if (m_bFacingRight && leftPressed && !rightPressed)
		m_bFacingRight = false;
	else if (!m_bFacingRight && !leftPressed && rightPressed)
		m_bFacingRight = true;


	// BASE_STATE 설정
	{
		// 땅 위에 있는 경우
		if (m_Rigidbody->IsOnGround())
		{
			// 방향키 안누르면 Idle
			if (!leftPressed && !rightPressed && !upPressed && !downPressed)
				m_CurBaseState = BASE_STATE::IDLE;

			// 아래 키 누르면 무조건 crouch 모드
			else if (downPressed)
				m_CurBaseState = BASE_STATE::CROUCH;

			// 좌우 방향키 누르면 run
			else if (leftPressed || rightPressed)
				m_CurBaseState = BASE_STATE::RUN;

			// Z키 누르면 점프
			if (KEY_PRESSED(KEY::_Z) && !(m_CurBaseState == BASE_STATE::DASH))
				m_CurBaseState = BASE_STATE::JUMP;

			if (KEY_PRESSED(KEY::_C))
				m_CurBaseState = BASE_STATE::FIXED;
		}

		// Shift 키 누르면 대쉬
		if (KEY_PRESSED(KEY::SHIFT) && (m_CurBaseState != BASE_STATE::DASH))
			m_CurBaseState = BASE_STATE::DASH;
	}


	// ACTION_STATE 설정
	// 총쏘기
	if (KEY_PRESSED(KEY::_C))
	{
		AddActionState(ACTION_STATE::SHOOTING);
	}
	else
	{
		RemoveActionState(ACTION_STATE::SHOOTING);
	}

	// ShootingDir 설정
	{
		// 오른쪽을 보고 있는 경우
		if (m_bFacingRight)
		{
			if (!leftPressed && !rightPressed && !upPressed && !downPressed)
				m_ShootingDir = SHOOTING_DIR::RIGHT;
			else if (upPressed && !rightPressed)
				m_ShootingDir = SHOOTING_DIR::UP;
			else if (downPressed && !rightPressed)
				m_ShootingDir = SHOOTING_DIR::DOWN;
			else if (upPressed && rightPressed)
				m_ShootingDir = SHOOTING_DIR::UP_RIGHT;
			else if (downPressed && rightPressed)
				m_ShootingDir = SHOOTING_DIR::DOWN_RIGHT;
		}

		// 왼쪽을 보고 있는 경우
		if (!m_bFacingRight)
		{
			if (!leftPressed && !rightPressed && !upPressed && !downPressed)
				m_ShootingDir = SHOOTING_DIR::LEFT;
			else if (upPressed && !leftPressed)
				m_ShootingDir = SHOOTING_DIR::UP;
			else if (downPressed && !leftPressed)
				m_ShootingDir = SHOOTING_DIR::DOWN;
			else if (upPressed && leftPressed)
				m_ShootingDir = SHOOTING_DIR::UP_LEFT;
			else if (downPressed && leftPressed)
				m_ShootingDir = SHOOTING_DIR::DOWN_LEFT;
		}
	}
}

void CPlayer::Move()
{


	bool leftPressed = KEY_PRESSED(KEY::LEFT);
	bool rightPressed = KEY_PRESSED(KEY::RIGHT);
	bool upPressed = KEY_PRESSED(KEY::UP);
	bool downPressed = KEY_PRESSED(KEY::DOWN);

	float forceMagnitude = 10000;

	if (upPressed)
	{
		//m_Rigidbody->AddForce(Vec2(0, -forceMagnitude));
		m_Rigidbody->AddForce(Vec2(0, -200));
	}

	if (downPressed)
	{
		//m_Rigidbody->AddForce(Vec2(0, forceMagnitude));
		m_Rigidbody->AddForce(Vec2(0, 200));
	}

	if (leftPressed)
	{
		//m_Rigidbody->AddForce(Vec2(-forceMagnitude, 0));
		m_Rigidbody->AddForce(Vec2(-200, 0));
	}

	if (rightPressed)
	{
		//m_Rigidbody->AddForce(Vec2(forceMagnitude, 0));
		m_Rigidbody->AddForce(Vec2(200, 0));

	}

	if (KEY_JUST_PRESSED(KEY::UP))
	{
		m_Rigidbody->AddVelocity(Vec2(0, -200));
	}
	if (KEY_JUST_PRESSED(KEY::DOWN))
	{
		m_Rigidbody->AddVelocity(Vec2(0, 200));

	}
	if (KEY_JUST_PRESSED(KEY::LEFT))
	{
		m_Rigidbody->AddVelocity(Vec2(-200, 0));

	}
	if (KEY_JUST_PRESSED(KEY::RIGHT))
	{
		m_Rigidbody->AddVelocity(Vec2(200, 0));
	}
}

void CPlayer::UpdateAnimation()
{
	// 상태 변경이 일어나지 않으면 기존 애니메이션 계속 출력
	if (m_PrevShootingDir == m_ShootingDir && m_PrevBaseState == m_CurBaseState && m_PrevActionState == m_CurActionState)
		return;

	// 총쏘지 않는 상태
	if (!IsInActionState(ACTION_STATE::SHOOTING))
	{
		switch (m_CurBaseState)
		{
			case BASE_STATE::IDLE:
			{
				//if (m_bFacingRight)
				//	m_Animator->Play();
				//else
				//	m_Animator->Play();
			}
				break;
			case BASE_STATE::CROUCH:
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

	// 총쏘는 상태
	else
	{
		switch (m_CurBaseState)
		{
			case BASE_STATE::IDLE:
				break;
			case BASE_STATE::CROUCH:
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




	//=====================================================================================
	// 레거시 코드


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
	//	// 방향 입력에 대한 처리
	//	static int lastInputDirection = 0;  // 마지막 입력 방향을 기억하기 위한 변수
	//	static int lastState = 0;			// 마지막 상태를 기억하기 위한 변수
	//
	//	if (KEY_JUST_PRESSED(KEY::UP)) {
	//		lastInputDirection = 1; // 위쪽
	//	}
	//	if (KEY_JUST_PRESSED(KEY::DOWN)) {
	//		lastInputDirection = 2; // 아래쪽
	//	}
	//	if (KEY_JUST_PRESSED(KEY::LEFT)) {
	//		lastInputDirection = 3; // 왼쪽
	//	}
	//	if (KEY_JUST_PRESSED(KEY::RIGHT)) {
	//		lastInputDirection = 4; // 오른쪽
	//	}
	//
	//	// 왼쪽-위 대각선 이동 및 애니메이션 처리
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
	//	// 왼쪽-아래 대각선 이동 및 애니메이션 처리
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
	//	// 오른쪽-위 대각선 이동 및 애니메이션 처리
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
	//	// 오른쪽-아래 대각선 이동 및 애니메이션 처리
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
	//	// 단일 방향 이동 및 애니메이션 처리
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
	//	// 모든 이동 키가 눌리지 않았을 때 IDLE 애니메이션 처리
	//	if (prevPos == vPos)
	//	{
	//		switch (lastState) {
	//			case 1: // 마지막 방향이 위쪽
	//				m_Animator->Play(L"IDLE_UP", true);
	//				break;
	//			case 2: // 마지막 방향이 아래쪽
	//				m_Animator->Play(L"IDLE_DOWN", true);
	//				break;
	//			case 3: // 마지막 방향이 왼쪽
	//				m_Animator->Play(L"IDLE_LEFT", true);
	//				break;
	//			case 4: // 마지막 방향이 오른쪽
	//				m_Animator->Play(L"IDLE_RIGHT", true);
	//				break;
	//			default:
	//				// 기본 IDLE 애니메이션 처리
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
	//		log.strLog = L"!! 미사일 발사 !!";
	//		CDbgRenderer::GetInstance().AddDbgLog(log);*/
	//
	//		LOG(LOG_TYPE::DBG_WARNING, L"@@ 미사일 발사 @@");
	//	}
	//}

	//void CPlayer::render()
	//{
	//	auto vPos = GetPos();
	//
	//	// AlphaBlending
	//	BLENDFUNCTION bf = {};
	//
	//	bf.BlendOp = AC_SRC_OVER;
	//	bf.BlendFlags = 0;
	//	bf.SourceConstantAlpha = 255;
	//	bf.AlphaFormat = AC_SRC_ALPHA;
	//
	//	auto m_Img = m_Texture;
	//
	//	AlphaBlend(SUBDC, (int)(vPos.x - m_Img->GetWidth() / 2.f)
	//		, (int)(vPos.y - m_Img->GetHeight() / 2.f)
	//		, m_Img->GetWidth(), m_Img->GetHeight()
	//		, m_Img->GetDC(), 0, 0, m_Img->GetWidth(), m_Img->GetHeight(), bf);
	//}



