#include "pch.h"
#include "World_Map.h"

#include "Worldmap_Player.h"
#include "CBackground.h"
#include "CWorldmap_Point.h"



World_Map::World_Map() :
	m_WorldmapPlayer{}
{
	SetName(L"World_Map");

	// BGM 
	BGM = CAssetMgr::GetInstance().LoadSound(L"BGM_Worldmap", L"sound\\BGM\\BGM_Inkwell_Isle_One.wav");
	BGM->SetVolume(50);
}

World_Map::~World_Map()
{
}

void World_Map::Enter()
{
	CCamera::GetInstance().SetTrackingState(CAM_TRACKING_STATE::WORLD_MAP);

	LoadBackground();
	LoadObject();
	SetCollision();

	if (m_bFirstEnter)
	{
		CCamera::GetInstance().SetCameraLookAt(Vec2(-963, 68));
		m_bFirstEnter = false;
	}
	else
	{
		m_WorldmapPlayer->SetPos(m_LastWorldmapPlayerPos);
		CCamera::GetInstance().SetCameraLookAt(m_WorldmapPlayer->GetPos());
	}

	if (m_bWinState)
	{
		m_WorldmapPlayer->SetWinState();
	}

	BGM->Play();
}

void World_Map::tick()
{
	CLevel::tick();

	if (KEY_JUST_PRESSED(KEY::_1))
		ChangeLevel(LEVEL_TYPE::BOSS_STAGE_1);

	else if (KEY_JUST_PRESSED(KEY::_2))
		ChangeLevel(LEVEL_TYPE::BOSS_STAGE_2);

	else if (KEY_JUST_PRESSED(KEY::T))
		ChangeLevel(LEVEL_TYPE::Test);
}

void World_Map::render()
{
	CLevel::render();
}

void World_Map::LoadBackground()
{
	// 먼저 그려야 하는것부터 추가
	CBackground* Worldmap_BG;

	Worldmap_BG = new CBackground;
	Worldmap_BG->SetName(L"World_Map_BG");
	Worldmap_BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"World_Map_BG", L"texture\\World_Map\\World_Map.png"));
	Worldmap_BG->SetPos(Vec2(0, 0));
	Worldmap_BG->SetDepth(BACKGROUND_DEPTH::Fore);
	AddObject(LAYER_TYPE::BACKGROUND, Worldmap_BG);

	CWorldmap_Point* worldmap_point = new CWorldmap_Point;
	worldmap_point->SetPos(Vec2(150, -437));
	worldmap_point->SetColliderOffset(Vec2(0, 100));
	worldmap_point->SetAnimation(L"animation\\Worldmap_Point\\Goopy_Le_Grande_point\\Goopy_Le_Grande_point.anim");
	worldmap_point->SetStage(LEVEL_TYPE::BOSS_STAGE_1);
	AddObject(LAYER_TYPE::WORLDMAP_POINT, worldmap_point);

	worldmap_point = new CWorldmap_Point;
	worldmap_point->SetPos(Vec2(-150, 355));
	worldmap_point->SetColliderOffset(Vec2(20, -20));
	worldmap_point->SetAnimation(L"animation\\Worldmap_Point\\Veggie_point\\veggie_point.anim");
	worldmap_point->SetStage(LEVEL_TYPE::BOSS_STAGE_2);
	AddObject(LAYER_TYPE::WORLDMAP_POINT, worldmap_point);

}

void World_Map::LoadObject()
{
	m_WorldmapPlayer = new Worldmap_Player;
	m_WorldmapPlayer->SetName(L"Worldmap_Player");
	m_WorldmapPlayer->SetPos(Vec2(-963, 68));
	AddObject(LAYER_TYPE::WORLDMAP_PLAYER, m_WorldmapPlayer);
}

void World_Map::SetCollision()
{
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::WORLDMAP_PLAYER, LAYER_TYPE::WORLDMAP_POINT);
}


void World_Map::Exit()
{
	BGM->Stop();
	m_LastWorldmapPlayerPos = m_WorldmapPlayer->GetPos();
	DeleteAllObjects();
}

