#include "pch.h"
#include "World_Map.h"
#include "CBackground.h"


World_Map::World_Map()
{
	SetName(L"World_Map");
}

World_Map::~World_Map()
{
}

void World_Map::Enter()
{
	CCamera::GetInstance().SetCameraLookAt(Vec2(-963, 68));

	LoadBackground();
	LoadObject();
	SetCollision();
}

void World_Map::tick()
{
	CLevel::tick();

	if (KEY_JUST_PRESSED(KEY::N))
		ChangeLevel(LEVEL_TYPE::BOSS_STAGE_1);
}

void World_Map::render()
{
	CLevel::render();
}

void World_Map::LoadBackground()
{
	// 먼저 그려야 하는것부터 추가
	CBackground* Worldmap_BG;

	// 아주 먼 배경
	Worldmap_BG = new CBackground;
	Worldmap_BG->SetName(L"World_Map_BG");
	Worldmap_BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"World_Map_BG", L"texture\\World_Map\\World_Map.png"));
	Worldmap_BG->SetPos(Vec2(0, 0));
	Worldmap_BG->SetDepth(BACKGROUND_DEPTH::Fore);
	AddObject(LAYER_TYPE::BACKGROUND, Worldmap_BG);
}

void World_Map::LoadObject()
{
}

void World_Map::SetCollision()
{
}


void World_Map::Exit()
{
}

