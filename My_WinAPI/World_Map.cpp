#include "pch.h"
#include "World_Map.h"

#include "Worldmap_Player.h"
#include "CBackground.h"
#include "CWorldmap_Point.h"
#include "CWall.h"



World_Map::World_Map() :
	m_WorldmapPlayer{}
{
	SetName(L"World_Map");

	// BGM 
	BGM = CAssetMgr::GetInstance().LoadSound(L"BGM_Worldmap", L"sound\\BGM\\BGM_Inkwell_Isle_One.wav");
	BGM->SetVolume(25);
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

	BGM->Play(true);
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
	m_WorldmapPlayer->SetPos(Vec2(-613, -95));
	AddObject(LAYER_TYPE::WORLDMAP_PLAYER, m_WorldmapPlayer);

	// 벽 생성
	auto wall = new CWall;
	wall->SetPos(Vec2(-715, 0));
	wall->SetColliderScale(Vec2(10, 1000));
	AddObject(LAYER_TYPE::WALL, wall);

	wall = new CWall;
	wall->SetPos(Vec2(-383, -128));
	wall->SetColliderScale(Vec2(694 , 10));
	AddObject(LAYER_TYPE::WALL, wall);

	//wall = new CWall;
	//wall->SetPos(Vec2(-438, -22));
	//wall->SetColliderScale(Vec2(700, 10));
	//AddObject(LAYER_TYPE::WALL, wall);

	wall = new CWall;
	wall->SetPos(Vec2(-405, -22));
	wall->SetColliderScale(Vec2(631, 10));
	AddObject(LAYER_TYPE::WALL, wall);

	wall = new CWall;
	wall->SetPos(Vec2(-91, 164));
	wall->SetColliderScale(Vec2(10, 372));
	AddObject(LAYER_TYPE::WALL, wall);

	wall = new CWall;
	wall->SetPos(Vec2(-45, 350));
	wall->SetColliderScale(Vec2(91, 10));
	AddObject(LAYER_TYPE::WALL, wall);

	wall = new CWall;
	wall->SetPos(Vec2(5, 240));
	wall->SetColliderScale(Vec2(10, 221));
	AddObject(LAYER_TYPE::WALL, wall);

	wall = new CWall;
	wall->SetPos(Vec2(110, 129));
	wall->SetColliderScale(Vec2(219, 10));
	AddObject(LAYER_TYPE::WALL, wall);

	wall = new CWall;
	wall->SetPos(Vec2(219, -112));
	wall->SetColliderScale(Vec2(10, 482));
	AddObject(LAYER_TYPE::WALL, wall);

	//wall = new CWall;
	//wall->SetPos(Vec2(130, -353));
	//wall->SetColliderScale(Vec2(179, 10));
	//AddObject(LAYER_TYPE::WALL, wall);

	//wall = new CWall;
	//wall->SetPos(Vec2(40, -440));
	//wall->SetColliderScale(Vec2(10, 86));
	//AddObject(LAYER_TYPE::WALL, wall);

	wall = new CWall;
	wall->SetPos(Vec2(0, -526));
	wall->SetColliderScale(Vec2(81, 10));
	AddObject(LAYER_TYPE::WALL, wall);

	wall = new CWall;
	wall->SetPos(Vec2(-41, -328));
	wall->SetColliderScale(Vec2(10, 396));
	AddObject(LAYER_TYPE::WALL, wall);
}

void World_Map::SetCollision()
{
	
}


void World_Map::Exit()
{
	BGM->Stop();
	m_LastWorldmapPlayerPos = m_WorldmapPlayer->GetPos();
	DeleteAllObjects();
}

