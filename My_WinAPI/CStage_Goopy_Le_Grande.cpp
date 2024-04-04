#include "pch.h"
#include "CStage_Goopy_Le_Grande.h"

#include "CBackground.h"
#include "CKeyMgr.h"

CStage_Goopy_Le_Grande::CStage_Goopy_Le_Grande()
{
}

CStage_Goopy_Le_Grande::~CStage_Goopy_Le_Grande()
{
}

void CStage_Goopy_Le_Grande::LoadBackGround()
{
	auto BG = new CBackground;
	//BG->SetPos(500, 500);
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Goopy_Le_Grande_BG_main_ground", L"texture\\Goopy Le Grande\\Background\\slime_bg_mg_main_ground.png"));
	AddObject(LAYER_TYPE::BACKGROUND, BG);
}

void CStage_Goopy_Le_Grande::tick()
{
	CLevel::tick();

	if (KEY_JUST_PRESSED(KEY::M))
	{
		ChangeLevel(LEVEL_TYPE::Test);
	}
}

void CStage_Goopy_Le_Grande::Enter()
{
	CCamera::GetInstance().SetCameraLookAt(Vec2(0, 0));
	LoadBackGround();
}

void CStage_Goopy_Le_Grande::Exit()
{
	DeleteAllObjects();
}


