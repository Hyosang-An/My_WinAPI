#include "pch.h"
#include "CLevel_Goopy_Le_Grande.h"

#include "CBackground.h"
#include "CKeyMgr.h"
#include "CPlayer.h"
#include "CGround.h"
#include "CWall.h"
#include "Goopy_Le_Grande.h"
#include "CLevelMgr.h"

CLevel_Goopy_Le_Grande::CLevel_Goopy_Le_Grande() :
	m_player{},
	m_Boss{}
{
	SetName(L"Goopy Le Grande Level");
}

CLevel_Goopy_Le_Grande::~CLevel_Goopy_Le_Grande()
{
}



void CLevel_Goopy_Le_Grande::Enter()
{
	// �������� �¿� ���� -710 ~ 720 -> �÷��̾� �̵� ���� : -680 ~ 690

	// ī�޶� ����
	CCamera::GetInstance().SetCameraInitialLookAt(Vec2(0, 0));
	CCamera::GetInstance().SetTrackingState(CAM_TRACKING_STATE::BOSS_STAGE, Vec2(-710, 720));
	CCamera::GetInstance().SetCameraEffect(CAM_EFFECT::FADE_IN, 2);

	//��� �߰�
	LoadBackground();

	// ������Ʈ �߰�
	LoadObject();

	// �浹 ����
	SetCollision();

	m_bLevelClear = false;
}

void CLevel_Goopy_Le_Grande::tick()
{
	CLevel::tick();

	if (KEY_JUST_PRESSED(KEY::ESC))
	{
		ChangeLevel(LEVEL_TYPE::WORLD_MAP);
	}

	if (m_bLevelClear)
	{
		static float accClearTime = 0;

		accClearTime += DT;

		if (3 < accClearTime)
		{
			accClearTime = 0;
			ChangeLevel(LEVEL_TYPE::WORLD_MAP);
			CLevelMgr::GetInstance().SetWorldmapLevelWin();
		}
	}
}

void CLevel_Goopy_Le_Grande::finaltick()
{
	CLevel::finaltick();
}

void CLevel_Goopy_Le_Grande::render()
{
	CLevel::render();

	wstring playerHP = L"�÷��̾� HP : " + std::to_wstring(m_player->GetHP());
	TextOut(SUBDC, 0, (int)CEngine::GetInstance().GetResolution().y - 20,
		playerHP.c_str(), (int)playerHP.length());

	wstring bossHP = L"���� HP : " + std::to_wstring(m_Boss->GetHP());
	TextOut(SUBDC, (int)CEngine::GetInstance().GetResolution().x - 80, (int)CEngine::GetInstance().GetResolution().y - 20,
		bossHP.c_str(), (int)bossHP.length());

	if (m_bLevelClear)
	{
		BLENDFUNCTION bf{};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = 255;

		// �ִϸ��̼� ������
		auto vecKnockOutMsg = CLevelMgr::GetInstance().GetvecKnockOutMsg();

		// �������� �������� ������ ���
		if (m_CurKnockOutFrameIdx >= vecKnockOutMsg.size() - 1)
			return;

		m_KnockOutframeElapsedTime += DT;

		if (m_KnockOutframeDuration < m_KnockOutframeElapsedTime)
		{
			m_KnockOutframeElapsedTime -= m_KnockOutframeDuration;
			m_CurKnockOutFrameIdx++;
		}

		
		auto curFrame = vecKnockOutMsg[m_CurKnockOutFrameIdx];
		auto w = curFrame->GetWidth();
		auto h = curFrame->GetHeight();
		auto res = CEngine::GetInstance().GetResolution();

		AlphaBlend(SUBDC, 0, 0, res.x, res.y,
			curFrame->GetDC(), 0, 0, w, h, bf);

	}
}

void CLevel_Goopy_Le_Grande::LoadBackground()
{
	// �������� �¿� ���� -710 ~ 722

	// ���� �׷��� �ϴ°ͺ��� �߰�
	CBackground* BG;

	// ���� �� ���
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Goopy_Le_Grande_BG_bg_far_forest", L"texture\\Boss Stage\\Goopy Le Grande\\Background\\slime_bg_bg_far_forest.png"));
	BG->SetPos(Vec2(0, -120));
	BG->SetDepth(BACKGROUND_DEPTH::Far);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	// ���� �� ���
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Goopy_Le_Grande_BG_bg_evergreens", L"texture\\Boss Stage\\Goopy Le Grande\\Background\\slime_bg_bg_evergreens.png"));
	BG->SetPos(Vec2(0, -200));
	BG->SetDepth(BACKGROUND_DEPTH::Far);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	//�ణ �� ���
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Goopy_Le_Grande_BG_bg_forest", L"texture\\Boss Stage\\Goopy Le Grande\\Background\\slime_bg_bg_forest.png"));
	BG->SetPos(Vec2(0, -190));
	BG->SetDepth(BACKGROUND_DEPTH::Middle);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	// �ణ �� ����� �ִϸ��̼� ���
	BG = new CBackground;
	BG->SetAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Background\\bg_stream.anim");
	BG->SetPos(Vec2(96, 1));
	BG->SetDepth(BACKGROUND_DEPTH::Middle);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	// �����̿� �ִ� ���
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Goopy_Le_Grande_BG_mg_main_ground", L"texture\\Boss Stage\\Goopy Le Grande\\Background\\slime_bg_mg_main_ground.png"));
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Goopy_Le_Grande_BG_fg_left_branch", L"texture\\Boss Stage\\Goopy Le Grande\\Background\\slime_bg_fg_left_branch.png"));
	BG->SetPos(Vec2(-650, -300));
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Goopy_Le_Grande_BG_fg_right_branch", L"texture\\Boss Stage\\Goopy Le Grande\\Background\\slime_bg_fg_right_branches.png"));
	BG->SetPos(Vec2(650, -300));
	AddObject(LAYER_TYPE::BACKGROUND, BG);


	// �÷��̾� �տ� ��ġ�ϴ� ���
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Goopy_Le_Grande_BG_fg_mushrooms_left", L"texture\\Boss Stage\\Goopy Le Grande\\Background\\slime_bg_fg_mushrooms_left.png"));
	BG->SetPos(Vec2(-500, 270));
	AddObject(LAYER_TYPE::FOREGROUND, BG);

	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Goopy_Le_Grande_BG_fg_mushrooms_right", L"\\texture\\Boss Stage\\Goopy Le Grande\\Background\\slime_bg_fg_mushrooms_right.png"));
	BG->SetPos(Vec2(400, 220));
	AddObject(LAYER_TYPE::FOREGROUND, BG);
}

void CLevel_Goopy_Le_Grande::LoadObject()
{
	// �������� �¿� ���� -710 ~ 720
	// 
	// �÷��̾� �߰�
	m_player = new CPlayer;
	m_player->SetName(L"Player");
	m_player->SetPos(0, 0);
	m_player->SetScale(100, 100);
	AddObject(LAYER_TYPE::PLAYER, m_player);

	// ���� ���� �� �׶��� �߰�
	m_Boss = new Goopy_Le_Grande;
	m_Boss->SetPos(Vec2(200, 0));
	AddObject(LAYER_TYPE::BOSS, m_Boss);


	// Ground ����
	auto ground = new CGround;
	ground->SetName(L"Ground");
	ground->SetPos(Vec2(0, 240));
	ground->SetColliderScale(Vec2(1910, 10));
	AddObject(LAYER_TYPE::GROUND, ground);

	// �¿� Wall ����
	auto wall = new CWall;
	wall->SetName(L"Left Wall");
	wall->SetPos(Vec2(-715, 0));
	wall->SetColliderScale(Vec2(10, 1000));
	AddObject(LAYER_TYPE::WALL, wall);

	wall = wall->Clone();
	wall->SetPos(Vec2(725, 0));
	AddObject(LAYER_TYPE::WALL, wall);



}

void CLevel_Goopy_Le_Grande::SetCollision()
{
	// �÷��̾�� �ٸ� ������Ʈ �浹
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::BOSS);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENEMY_MISSILE);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::NEUTRAL_OBJ);

	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::BOSS);





	// ���� �浹
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::GROUND);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::WALL);

	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::GROUND);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::WALL);


	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::BOSS, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::BOSS, LAYER_TYPE::GROUND);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::BOSS, LAYER_TYPE::WALL);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::BOSS, LAYER_TYPE::BOSS);



}

void CLevel_Goopy_Le_Grande::Exit()
{
	DeleteAllObjects();
}

void CLevel_Goopy_Le_Grande::LevelClear()
{
	m_bLevelClear = true;
}


