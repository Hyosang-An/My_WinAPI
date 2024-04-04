#include "pch.h"
#include "CStage_Goopy_Le_Grande.h"

#include "CBackground.h"
#include "CKeyMgr.h"
#include "CPlayer.h"
#include "CGround.h"

CStage_Goopy_Le_Grande::CStage_Goopy_Le_Grande()
{
}

CStage_Goopy_Le_Grande::~CStage_Goopy_Le_Grande()
{
}



void CStage_Goopy_Le_Grande::Enter()
{
	// �������� �¿� ���� -710 ~ 722

	// ī�޶� ����
	CCamera::GetInstance().SetCameraInitialLookAt(Vec2(0, 0));
	CCamera::GetInstance().SetTrackingState(CAM_TRACKING_STATE::BOSS_STAGE);

	//�� ��� �߰�
	LoadBackGround();

	// ������Ʈ �߰�
	CObj* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(0, 0);
	pObj->SetScale(100, 100);
	AddObject(LAYER_TYPE::PLAYER, pObj);


	// Ground ����
	auto ground = new CGround;
	ground->SetName(L"Ground");
	ground->SetPos(Vec2(0, 240));
	ground->SetColliderScale(Vec2(1910, 10));
	AddObject(LAYER_TYPE::GROUND, ground);


	// ������Ʈ �տ� ��ġ�ϴ� ���
	CBackground* BG;


}

void CStage_Goopy_Le_Grande::tick()
{
	CLevel::tick();

	if (KEY_JUST_PRESSED(KEY::M))
	{
		ChangeLevel(LEVEL_TYPE::Test);
	}
}

void CStage_Goopy_Le_Grande::LoadBackGround()
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

	// �� ���
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Goopy_Le_Grande_BG_bg_evergreens", L"texture\\Boss Stage\\Goopy Le Grande\\Background\\slime_bg_bg_evergreens.png"));
	BG->SetPos(Vec2(0, -200));
	BG->SetDepth(BACKGROUND_DEPTH::Far);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	// �ణ �� ���
	BG = new CBackground;
	BG->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Goopy_Le_Grande_BG_bg_forest", L"texture\\Boss Stage\\Goopy Le Grande\\Background\\slime_bg_bg_forest.png"));
	BG->SetPos(Vec2(0, -190));
	BG->SetDepth(BACKGROUND_DEPTH::Middle);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

	// �ణ �� ����� �ִϸ��̼� ���
	BG = new CBackground;
	BG->SetAnimation(L"animation\\Boss\\Goopy Le Grande\\Background\\bg_stream.anim");
	BG->SetPos(Vec2(96, 1));
	BG->SetDepth(BACKGROUND_DEPTH::Middle);
	AddObject(LAYER_TYPE::BACKGROUND, BG);

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

void CStage_Goopy_Le_Grande::Exit()
{
	DeleteAllObjects();
}


