#include "pch.h"
#include "CLevel_Veggie.h"

#include "CLevelMgr.h"

#include "CBackground.h"
#include "Cloud.h"
#include "CGround.h"
#include "CWall.h"
#include "CEffect.h"
#include "Potato.h"
#include "Onion.h"

CLevel_Veggie::CLevel_Veggie() :
	m_player{},
	m_CurBoss{},
	m_BurstEffect{},
	m_BurstDust{}
{
	SetName(L"Veggie_Level");

	// BGM
	BGM = CAssetMgr::GetInstance().LoadSound(L"BGM_Botanic_Panic", L"sound\\BGM\\BGM_Botanic_Panic.wav");
}

CLevel_Veggie::~CLevel_Veggie()
{
}

void CLevel_Veggie::Enter()
{
	// 카메라 설정
	CCamera::GetInstance().SetCameraInitialLookAt(Vec2(0, 0));
	CCamera::GetInstance().SetTrackingState(CAM_TRACKING_STATE::BOSS_STAGE, Vec2(-670, 670));
	CCamera::GetInstance().SetCameraEffect(CAM_EFFECT::FADE_IN, 3);

	m_bLevelClear = false;

	m_PhaseState = PHASE_STATE::PHASE1;
	m_player = nullptr;
	m_CurBoss = nullptr;
	m_BossSpawnFlag = false;

	m_Potato = new Potato;
	m_Onion = new Onion;
	m_Carrot = nullptr;

	m_CurBoss = m_Potato;

	//배경 추가
	LoadBackground();

	// 오브젝트 추가
	LoadObject();

	// 충돌 설정
	SetCollision();

	BGM->Play(true);
	Announcer_intro->Play();
}

void CLevel_Veggie::tick()
{
	CLevel::tick();

	if (KEY_JUST_PRESSED(KEY::ESC))
	{
		ChangeLevel(LEVEL_TYPE::WORLD_MAP);
	}

	// 플레이어 죽음
	if (m_player->GetHP() == 0)
	{
		static float accPlayerDeathTime = 0;
		accPlayerDeathTime += DT;

		if (3 < accPlayerDeathTime)
		{
			accPlayerDeathTime = 0;
			ChangeLevel(LEVEL_TYPE::WORLD_MAP);
		}
	}

	// 스테이지 클리어
	if (m_bLevelClear)
	{
		static bool bAnnounce_KO = false;
		if (bAnnounce_KO == false)
		{
			Announcer_KO->Play();
			bAnnounce_KO = true;
		}

		static float accClearTime = 0;

		accClearTime += DT;

		if (4 < accClearTime)
		{
			accClearTime = 0;
			ChangeLevel(LEVEL_TYPE::WORLD_MAP);
			CLevelMgr::GetInstance().SetWorldmapLevelWin();
		}

		return;
	}

	switch (m_PhaseState)
	{
		case CLevel_Veggie::PHASE_STATE::PHASE1:
		{
			// BurstEffect 재설정
			if (m_BurstEffect != nullptr && m_BurstEffect->IsDead())
			{

				//!디버깅
				auto& vec = GetObjvecOfLayer(LAYER_TYPE::EFFECT);

				m_BurstEffect = nullptr;				
			}

			// 보스 생성
			if (!m_BossSpawnFlag && m_BurstEffect != nullptr && m_BurstEffect->GetComponent<CAnimator>()->GetCurAnimationFrmIdx() == 8)
			{
				m_CurBoss->SetName(L"Potato");
				m_CurBoss->SetPos(Vec2(400, 110));
				SpawnObject(LAYER_TYPE::BOSS, m_CurBoss);

				m_BossSpawnFlag = true;
			}

			// 남은 m_BurstDust 생성
			if (m_BurstDust == nullptr && m_BurstEffect && m_BurstEffect->GetComponent<CAnimator>()->GetCurAnimationFrmIdx() == 17)
			{
				m_BurstDust = new CBackground;
				m_BurstDust->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_potato_ground_burst_front_0018", L"animation\\Boss\\Veggie\\potato\\ground_burst\\veggie_potato_ground_burst_front_0018.png"));
				m_BurstDust->SetPos(Vec2(400, 270));
				m_BurstDust->SetName(L"Burst_Dust1");
				SpawnObject(LAYER_TYPE::FOREGROUND, m_BurstDust);
			}

			// 다음 페이즈로 전환
			if (m_CurBoss && m_CurBoss->IsDead())
			{
				m_CurBoss = nullptr;

				m_BurstDust->SelfDestruct();
				m_BurstDust = nullptr;

				m_PhaseState = PHASE_STATE::PHASE2;

				//!디버깅
				auto& vec = GetObjvecOfLayer(LAYER_TYPE::EFFECT);

				m_BurstEffect = new CEffect;
				m_BurstEffect->SetName(L"veggie_potato_ground_burst_front");
				m_BurstEffect->SetAnimation(L"animation\\Boss\\Veggie\\potato\\ground_burst\\veggie_potato_ground_burst_front.anim");
				m_BurstEffect->SetPos(Vec2(0, 100));
				SpawnObject(LAYER_TYPE::EFFECT, m_BurstEffect);

				m_BossSpawnFlag = false;
			}

			break;
		}

		case CLevel_Veggie::PHASE_STATE::PHASE2:
		{
			// BurstEffect 재설정
			if (m_BurstEffect != nullptr && m_BurstEffect->IsDead())
			{
				m_BurstEffect = nullptr;
			}

			// 보스 생성
			if (!m_BossSpawnFlag && m_BurstEffect != nullptr && m_BurstEffect->GetComponent<CAnimator>()->GetCurAnimationFrmIdx() == 7)
			{
				m_CurBoss = m_Onion;
				m_CurBoss->SetName(L"Onion");
				m_CurBoss->SetPos(Vec2(0, 10));
				SpawnObject(LAYER_TYPE::BOSS, m_CurBoss);

				m_BossSpawnFlag = true;
			}

			// 남은 m_BurstDust 생성
			if (m_BurstEffect && m_BurstEffect->GetComponent<CAnimator>()->IsCurAnimationFinished())
			{

				m_BurstDust = new CBackground;
				m_BurstDust->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_potato_ground_burst_front_0018", L"animation\\Boss\\Veggie\\potato\\ground_burst\\veggie_potato_ground_burst_front_0018.png"));
				m_BurstDust->SetPos(Vec2(0, 280));
				SpawnObject(LAYER_TYPE::FOREGROUND, m_BurstDust);
			}

			// 다음 페이즈로 전환
			if (m_CurBoss && m_CurBoss->IsDead())
			{
				m_bLevelClear = true;

				/*m_BurstDust->SelfDestruct();

				m_PhaseState = PHASE_STATE::PHASE3;

				m_BurstEffect = new CEffect;
				m_BurstEffect->SetName(L"veggie_carrot_ground_burst_front");
				m_BurstEffect->SetAnimation(L"animation\\Boss\\Veggie\\carrot\\ground_burst\\veggie_carrot_ground_burst_front.anim");
				SpawnObject(LAYER_TYPE::EFFECT, m_BurstEffect);

				m_BossSpawnFlag = false;*/
			}

			break;
		}
		case CLevel_Veggie::PHASE_STATE::PHASE3:
			break;
	}

	

}

void CLevel_Veggie::render()
{
	CLevel::render();

	auto res = CEngine::GetInstance().GetResolution();

	//// !디버깅
	//if (m_player)
	//{
	//	wstring playerHP = L"플레이어 HP : " + std::to_wstring(m_player->GetHP());
	//	TextOut(SUBDC, 0, (int)res.y - 20,
	//		playerHP.c_str(), (int)playerHP.length());
	//}
	//
	//if (m_CurBoss)
	//{
	//	wstring bossHP = L"보스 HP : " + std::to_wstring(m_CurBoss->GetHP());
	//	TextOut(SUBDC, (int)res.x - 80, (int)res.y - 20,
	//		bossHP.c_str(), (int)bossHP.length());
	//}
	//// 디버깅

	BLENDFUNCTION bf{};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	// 플레이어 HP HUD
	auto curHUD_Tex = CLevelMgr::GetInstance().GetvecPlayerHP_HUD()[m_player->GetHP()];
	auto w = curHUD_Tex->GetWidth();
	auto h = curHUD_Tex->GetHeight();
	AlphaBlend(SUBDC, 0, res.y - 80, w, h,
		curHUD_Tex->GetDC(), 0, 0, w, h, bf);


	// KnockOut 렌더링
	if (m_bLevelClear)
	{
		// 애니매이션 렌더링
		auto vecKnockOutMsg = CLevelMgr::GetInstance().GetvecKnockOutMsg();

		// 프레임이 마지막에 도달한 경우
		if (m_CurKnockOutFrameIdx >= vecKnockOutMsg.size() - 1)
			return;

		m_KnockOutframeElapsedTime += DT;

		if (m_KnockOutframeDuration < m_KnockOutframeElapsedTime)
		{
			m_KnockOutframeElapsedTime -= m_KnockOutframeDuration;
			m_CurKnockOutFrameIdx++;
		}


		auto curFrame = vecKnockOutMsg[m_CurKnockOutFrameIdx];
		w = curFrame->GetWidth();
		h = curFrame->GetHeight();


		AlphaBlend(SUBDC, 0, 0, res.x, res.y,
			curFrame->GetDC(), 0, 0, w, h, bf);

	}
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
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_fore2", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_fore2.png"));
	BG->SetPos(Vec2(0, 60));
	BG->SetDepth(BACKGROUND_DEPTH::Fore);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	// 가까이에 있는 배경
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_fore1", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_fore1.png"));
	BG->SetPos(Vec2(0, 200));
	BG->SetDepth(BACKGROUND_DEPTH::Fore);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	// 플레이어 앞에 위치하는 배경
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"veggie_bg_0001", L"texture\\Boss Stage\\Veggie_BG\\veggie_bg_0001.png"));
	BG->SetPos(Vec2(400, 330));
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
	AddObject(LAYER_TYPE::PLAYER, m_player);

	// BurstEffect 생성
	m_BurstEffect = new CEffect;
	m_BurstEffect->SetName(L"veggie_potato_ground_burst_front");
	m_BurstEffect->SetAnimation(L"animation\\Boss\\Veggie\\potato\\ground_burst\\veggie_potato_ground_burst_front.anim");
	m_BurstEffect->SetPos(400, 120); 
	AddObject(LAYER_TYPE::EFFECT, m_BurstEffect);



	// Ground 생성
	auto ground = new CGround;
	ground->SetName(L"Ground");
	ground->SetPos(Vec2(0, 260));
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
	BGM->Stop();
	DeleteAllObjects();
}

