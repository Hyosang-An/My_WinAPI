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
	m_Texture{}
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

	m_Animator = AddComponent(new CAnimator);

	/*{
		CTexture* pAtlas = CAssetMgr::GetInstance().LoadTexture(L"PlayerAtlasTexture", L"texture\\link.png");

		m_Animator->CreateAnimation(L"IDLE_DOWN", pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 130.f), 3, 10)->Save2(L"animation\\player\\");
		m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlas, Vec2(0.f, 130.f), Vec2(120.f, 130.f), 3, 10)->Save2(L"animation\\player\\");
		m_Animator->CreateAnimation(L"IDLE_UP", pAtlas, Vec2(0.f, 260.f), Vec2(120.f, 130.f), 1, 1)->Save2(L"animation\\player\\");
		m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.f), 3, 1)->Save2(L"animation\\player\\");
		
		m_Animator->CreateAnimation(L"WALK_DOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.f), 10, 18)->Save2(L"animation\\player\\");
		m_Animator->CreateAnimation(L"WALK_LEFT", pAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.f), 10, 18)->Save2(L"animation\\player\\");
		m_Animator->CreateAnimation(L"WALK_UP", pAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.f), 10, 18)->Save2(L"animation\\player\\");
		m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.f), 10, 18)->Save2(L"animation\\player\\");

		m_Animator->LoadAnimation2(L"animation\\player\\WALK_DOWN.anim");
		m_Animator->LoadAnimation2(L"animation\\player\\WALK_RIGHT.anim");
		m_Animator->LoadAnimation2(L"animation\\player\\WALK_LEFT.anim");
		m_Animator->LoadAnimation2(L"animation\\player\\WALK_UP.anim");
		m_Animator->LoadAnimation2(L"animation\\player\\IDLE_DOWN.anim");
		m_Animator->LoadAnimation2(L"animation\\player\\IDLE_LEFT.anim");
		m_Animator->LoadAnimation2(L"animation\\player\\IDLE_UP.anim");
		m_Animator->LoadAnimation2(L"animation\\player\\IDLE_RIGHT.anim");

		m_Animator->Play(L"IDLE_DOWN", true);
	}*/

	{
		m_Animator->CreateAnimationFromJSON(L"animation\\run", 30);
		m_Animator->Play(L"run", true);
	}


	//m_Texture = CAssetMgr::GetInstance().LoadTexture(L"PlayerTexture", L"texture\\Character.png");


}

CPlayer::~CPlayer()
{
}

void CPlayer::begin()
{
}

void CPlayer::tick()
{
	auto vPos = GetPos();

	auto prevPos = vPos;

	bool leftPressed = KEY_PRESSED(KEY::LEFT);
	bool rightPressed = KEY_PRESSED(KEY::RIGHT);
	bool upPressed = KEY_PRESSED(KEY::UP);
	bool downPressed = KEY_PRESSED(KEY::DOWN);

	// ���� �Է¿� ���� ó��
	static int lastInputDirection = 0;  // ������ �Է� ������ ����ϱ� ���� ����
	static int lastState = 0;			// ������ ���¸� ����ϱ� ���� ����

	if (KEY_JUST_PRESSED(KEY::UP)) {
		lastInputDirection = 1; // ����
	}
	if (KEY_JUST_PRESSED(KEY::DOWN)) {
		lastInputDirection = 2; // �Ʒ���
	}
	if (KEY_JUST_PRESSED(KEY::LEFT)) {
		lastInputDirection = 3; // ����
	}
	if (KEY_JUST_PRESSED(KEY::RIGHT)) {
		lastInputDirection = 4; // ������
	}

	// ����-�� �밢�� �̵� �� �ִϸ��̼� ó��
	if (leftPressed && upPressed) {
		vPos.x -= m_fSpeed * DT / sqrtf(2);
		vPos.y -= m_fSpeed * DT / sqrtf(2);
		if (lastInputDirection == 1)
		{
			m_Animator->Play(L"WALK_UP", true);
			lastState = 1;
		}
		if (lastInputDirection == 3)
		{
			m_Animator->Play(L"WALK_LEFT", true);
			lastState = 3;
		}
	}
	// ����-�Ʒ� �밢�� �̵� �� �ִϸ��̼� ó��
	else if (leftPressed && downPressed) {
		vPos.x -= m_fSpeed * DT / sqrtf(2);
		vPos.y += m_fSpeed * DT / sqrtf(2);
		if (lastInputDirection == 2)
		{
			m_Animator->Play(L"WALK_DOWN", true);
			lastState = 2;
		}
		if (lastInputDirection == 3)
		{
			m_Animator->Play(L"WALK_LEFT", true);
			lastState = 3;
		}
	}
	// ������-�� �밢�� �̵� �� �ִϸ��̼� ó��
	else if (rightPressed && upPressed) {
		vPos.x += m_fSpeed * DT / sqrtf(2);
		vPos.y -= m_fSpeed * DT / sqrtf(2);
		if (lastInputDirection == 1)
		{
			m_Animator->Play(L"WALK_UP", true);
			lastState = 1;
		}
		if (lastInputDirection == 4)
		{
			m_Animator->Play(L"WALK_RIGHT", true);
			lastState = 4;
		}
	}
	// ������-�Ʒ� �밢�� �̵� �� �ִϸ��̼� ó��
	else if (rightPressed && downPressed) {
		vPos.x += m_fSpeed * DT / sqrtf(2);
		vPos.y += m_fSpeed * DT / sqrtf(2);
		if (lastInputDirection == 2)
		{
			m_Animator->Play(L"WALK_DOWN", true);
			lastState = 2;
		}
		if (lastInputDirection == 4)
		{
			m_Animator->Play(L"WALK_RIGHT", true);
			lastState = 4;
		}
	}

	// ���� ���� �̵� �� �ִϸ��̼� ó��
	if (!upPressed && !downPressed && !rightPressed && leftPressed) {
		vPos.x -= m_fSpeed * DT;
		m_Animator->Play(L"WALK_LEFT", true);
		lastState = 3;
	}
	else if (!upPressed && !downPressed && !leftPressed && rightPressed) {
		vPos.x += m_fSpeed * DT;
		m_Animator->Play(L"WALK_RIGHT", true);
		lastState = 4;
	}
	else if (!leftPressed && !rightPressed && !downPressed && upPressed) {
		vPos.y -= m_fSpeed * DT;
		m_Animator->Play(L"WALK_UP", true);
		lastState = 1;
	}
	else if (!leftPressed && !rightPressed && !upPressed && downPressed) {
		vPos.y += m_fSpeed * DT;
		m_Animator->Play(L"WALK_DOWN", true);
		lastState = 2;
	}

	// ��� �̵� Ű�� ������ �ʾ��� �� IDLE �ִϸ��̼� ó��
	if (prevPos == vPos)
	{
		switch (lastState) {
			case 1: // ������ ������ ����
				m_Animator->Play(L"IDLE_UP", true);
				break;
			case 2: // ������ ������ �Ʒ���
				m_Animator->Play(L"IDLE_DOWN", true);
				break;
			case 3: // ������ ������ ����
				m_Animator->Play(L"IDLE_LEFT", true);
				break;
			case 4: // ������ ������ ������
				m_Animator->Play(L"IDLE_RIGHT", true);
				break;
			default:
				// �⺻ IDLE �ִϸ��̼� ó��
				//m_Animator->Play(L"WALK_DOWN", true);
				break;
		}

		lastState = 0;
	}

	SetPos(vPos);

	if (KEY_JUST_PRESSED(KEY::SPACE))
	{
		CMissile* pMissile = new CGuidedMissile;

		pMissile->SetPos(Vec2(GetPos() + Vec2(0, -GetScale().y * 0.5f)));
		pMissile->SetScale(20, 20);
		//pMissile->SetAngle(-3.141592f * 0.5);
		pMissile->SetName(L"Player Guided Missile");

		SpawnObject(CLevelMgr::GetInstance().GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);

		/*tDbgLog log{};
		log.Type = LOG_TYPE::DBG_LOG;
		log.strLog = L"!! �̻��� �߻� !!";
		CDbgRenderer::GetInstance().AddDbgLog(log);*/

		LOG(LOG_TYPE::DBG_WARNING, L"@@ �̻��� �߻� @@");
	}
}

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



