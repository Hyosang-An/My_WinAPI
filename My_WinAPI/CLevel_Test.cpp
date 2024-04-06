#include "pch.h"
#include "CLevel_Test.h"
#include "CKeyMgr.h"
#include "CForce.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "CMonster.h"
#include "CGround.h"
#include "CBackground.h"


CLevel_Test::CLevel_Test() 
{
	SetName(L"Test Level");
}

CLevel_Test::~CLevel_Test()
{
}


void CLevel_Test::begin()
{
	CLevel::begin();

	//CCamera::GetInstance().SetCameraEffect(CAM_EFFECT::FADE_OUT, 2);
	CCamera::GetInstance().SetCameraEffect(CAM_EFFECT::FADE_IN, 2);

}

void CLevel_Test::tick()
{
	CLevel::tick();

	if (KEY_JUST_PRESSED(KEY::RBTN))
	{
		Vec2 vMousePos = CKeyMgr::GetInstance().GetMousePos();

		CForce* pForce = new CForce;
		pForce->SetPos(vMousePos);
		pForce->SetForce(1000, 300, 0.5);
		SpawnObject(this, LAYER_TYPE::FORCE, pForce);
	}
	
	if (KEY_JUST_PRESSED(KEY::N))
		ChangeLevel(LEVEL_TYPE::BOSS_STAGE_1);
}

void CLevel_Test::Enter()
{
	// 카메라 트래킹 설정
	CCamera::GetInstance().SetTrackingState(CAM_TRACKING_STATE::RUN_AND_GUN_STAGE);

	LoadBackground();
	LoadObject();
	SetCollision();


	

}


void CLevel_Test::LoadBackground()
{

	// Background 생성
	auto bg = new CBackground;
	bg->SetTexture(CAssetMgr::GetInstance().LoadTexture(L"Test Background", L"texture\\Funfair Fever\\main playable\\lv2-1_main_playable_ground_loop.png"));
	bg->SetName(L"BG_Test");
	bg->SetPos(Vec2(640.f, 600));
	AddObject(LAYER_TYPE::GROUND, bg);

	bg = bg->Clone();
	bg->SetName(L"BG_Test2");
	bg->SetPos(Vec2(640.f + 1910, 600));
	AddObject(LAYER_TYPE::GROUND, bg);
}

void CLevel_Test::LoadObject()
{
	// 레벨에 물체 추가하기
	CObj* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(640.f, 384.f);
	pObj->SetScale(100, 100);
	AddObject(LAYER_TYPE::PLAYER, pObj);

	pObj = new CMonster;
	pObj->SetName(L"Monster");
	pObj->SetPos(200.f, 200.f);
	pObj->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::MONSTER, pObj);


	// 플랫폼 생성
	pObj = new CPlatform;
	pObj->SetName(L"Platform");
	pObj->SetPos(Vec2(640.f, 600));
	AddObject(LAYER_TYPE::PLATFORM, pObj);

	// Ground 생성 (test)
	auto ground = new CGround;
	ground->SetName(L"Ground_test");
	ground->SetPos(Vec2(640.f, 600));
	ground->SetColliderScale(Vec2(1910, 10));
	AddObject(LAYER_TYPE::GROUND, ground);

	ground = ground->Clone();
	ground->SetPos(Vec2(640.f + 1910, 600));
	ground->SetName(L"Ground_test2");
	AddObject(LAYER_TYPE::GROUND, ground);
}

void CLevel_Test::SetCollision()
{
	// 충돌 지정
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::GROUND);
}

void CLevel_Test::Exit()
{
	// 레벨에 있는 모든 오브젝트 삭제한다.
	DeleteAllObjects();
}

