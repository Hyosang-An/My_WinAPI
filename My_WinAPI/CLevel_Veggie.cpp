#include "pch.h"
#include "CLevel_Veggie.h"

#include "CBackground.h"
#include "Cloud.h"
#include "CGround.h"
#include "CWall.h"

CLevel_Veggie::CLevel_Veggie() :
	m_player{},
	m_Boss{}
{
	SetName(L"Veggie_Level");
}

CLevel_Veggie::~CLevel_Veggie()
{
}

void CLevel_Veggie::Enter()
{
	// 카메라 설정
	CCamera::GetInstance().SetCameraInitialLookAt(Vec2(0, 0));
	CCamera::GetInstance().SetTrackingState(CAM_TRACKING_STATE::BOSS_STAGE, Vec2(-670, 670));

	//배경 추가
	LoadBackground();

	// 오브젝트 추가
	LoadObject();

	// 충돌 설정
	SetCollision();
}

void CLevel_Veggie::tick()
{
	CLevel::tick();

	if (KEY_JUST_PRESSED(KEY::M))
	{
		ChangeLevel(LEVEL_TYPE::Test);
	}
}

void CLevel_Veggie::render()
{
	CLevel::render();

	/*wstring playerHP = L"플레이어 HP : " + std::to_wstring(m_player->GetHP());
	TextOut(SUBDC, 0, (int)CEngine::GetInstance().GetResolution().y - 20,
		playerHP.c_str(), (int)playerHP.length());*/

	/*wstring bossHP = L"보스 HP : " + std::to_wstring(m_Boss->GetHP());
	TextOut(SUBDC, (int)CEngine::GetInstance().GetResolution().x - 80, (int)CEngine::GetInstance().GetResolution().y - 20,
		bossHP.c_str(), (int)bossHP.length());*/
}

void CLevel_Veggie::LoadBackground()
{
	// 스테이지 범위 -670 ~ 670

	// 먼저 그려야 하는것부터 추가
	CBackground* BG;

	// 아주 먼 배경
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_sky", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_sky.png"));
	BG->SetPos(Vec2(0, -300));
	BG->SetDepth(BACKGROUND_DEPTH::Far);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	// ================================================================================================================================================================
	// 구름 배경
	// ================================================================================================================================================================
	Cloud* cloud = new Cloud;
	cloud->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_clouds_0001", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_clouds_0001.png"));
	cloud->SetPos(Vec2(200, -300));
	cloud->SetSpeed(-8);
	cloud->SetStageLimit(-670, 670);
	cloud->SetDepth(BACKGROUND_DEPTH::Far);
	AddObject(LAYER_TYPE::BACKGROUND, cloud);

	cloud = new Cloud;
	cloud->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_clouds_0002", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_clouds_0002.png"));
	cloud->SetPos(Vec2(-300, -180));
	cloud->SetSpeed(-15);
	cloud->SetStageLimit(-670, 670);
	cloud->SetDepth(BACKGROUND_DEPTH::Far);
	AddObject(LAYER_TYPE::BACKGROUND, cloud);

	cloud = new Cloud;
	cloud->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_clouds_0003", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_clouds_0003.png"));
	cloud->SetPos(Vec2(700, -100));
	cloud->SetSpeed(-15);
	cloud->SetStageLimit(-670, 670);
	cloud->SetDepth(BACKGROUND_DEPTH::Far);
	AddObject(LAYER_TYPE::BACKGROUND, cloud);

	cloud = new Cloud;
	cloud->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_clouds_0004", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_clouds_0004.png"));
	cloud->SetPos(Vec2(-800, -120));
	cloud->SetSpeed(-20);
	cloud->SetStageLimit(-670, 670);
	cloud->SetDepth(BACKGROUND_DEPTH::Far);
	AddObject(LAYER_TYPE::BACKGROUND, cloud);

	cloud = new Cloud;
	cloud->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_clouds_0005", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_clouds_0005.png"));
	cloud->SetPos(Vec2(-700, -400));
	cloud->SetSpeed(-25);
	cloud->SetStageLimit(-670, 670);
	cloud->SetDepth(BACKGROUND_DEPTH::Far);
	AddObject(LAYER_TYPE::BACKGROUND, cloud);

	cloud = new Cloud;
	cloud->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_clouds_0006", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_clouds_0006.png"));
	cloud->SetPos(Vec2(-900, -350));
	cloud->SetSpeed(-20);
	cloud->SetStageLimit(-670, 670);
	cloud->SetDepth(BACKGROUND_DEPTH::Far);
	AddObject(LAYER_TYPE::BACKGROUND, cloud);

	cloud = new Cloud;
	cloud->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_clouds_0007", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_clouds_0007.png"));
	cloud->SetPos(Vec2(900, -410));
	cloud->SetSpeed(-15);
	cloud->SetStageLimit(-670, 670);
	cloud->SetDepth(BACKGROUND_DEPTH::Far);
	AddObject(LAYER_TYPE::BACKGROUND, cloud);

	// ================================================================================================================================================================
	// ================================================================================================================================================================


	// 약간 먼 배경의 애니메이션
	BG = new CBackground;
	BG->SetAnimation(L"animation\\Boss\\Veggie\\BG\\veggie_tireswing.anim", true);
	BG->SetPos(Vec2(-292, -175));
	BG->SetDepth(BACKGROUND_DEPTH::Middle);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	// 약간 먼 배경
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_middle", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_middle.png"));
	BG->SetPos(Vec2(0, -230 + 40));
	BG->SetDepth(BACKGROUND_DEPTH::Middle);
	AddObject(LAYER_TYPE::BACKGROUND, BG);


	// 가까이에 있는 배경
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_fore", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_fore.png"));
	BG->SetPos(Vec2(0, 110 + 40));
	BG->SetDepth(BACKGROUND_DEPTH::Fore);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	// 플레이어 앞에 위치하는 배경
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_0001", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_0001.png"));
	BG->SetPos(Vec2(400, 300));
	AddObject(LAYER_TYPE::FOREGROUND, BG);

	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_0002", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_0002.png"));
	BG->SetPos(Vec2(-500, 300));
	AddObject(LAYER_TYPE::FOREGROUND, BG);
}

void CLevel_Veggie::LoadObject()
{
	// 플레이어 추가
	m_player = new CPlayer;
	m_player->SetName(L"Player");
	m_player->SetPos(0, 0);
	m_player->SetScale(100, 100);
	AddObject(LAYER_TYPE::PLAYER, m_player);


	// 보스 추가
	// TODO

	// Ground 생성
	auto ground = new CGround;
	ground->SetName(L"Ground");
	ground->SetPos(Vec2(0, 270));
	ground->SetColliderScale(Vec2(1910, 10));
	AddObject(LAYER_TYPE::GROUND, ground);

	// 좌우 Wall 생성
	auto wall = new CWall;
	wall->SetName(L"Left_Wall");
	wall->SetPos(Vec2(-675, 0));
	wall->SetColliderScale(Vec2(10, 1000));
	AddObject(LAYER_TYPE::WALL, wall);

	wall = wall->Clone();
	wall->SetName(L"Right_Wall");
	wall->SetPos(Vec2(675, 0));
	AddObject(LAYER_TYPE::WALL, wall);
}

void CLevel_Veggie::SetCollision()
{
}


void CLevel_Veggie::Exit()
{
}

