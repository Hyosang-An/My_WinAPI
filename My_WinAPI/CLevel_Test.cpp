#include "pch.h"
#include "CLevel_Test.h"
#include "CKeyMgr.h"
#include "CForce.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "CMonster.h"
#include "CGround.h"
#include "CCollisionMgr.h"


CLevel_Test::CLevel_Test()
{
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
	pObj = new CGround;
	pObj->SetName(L"Ground_test");
	pObj->SetPos(Vec2(640.f, 600));
	AddObject(LAYER_TYPE::GROUND, pObj);

	pObj = pObj->Clone();
	pObj->SetPos(Vec2(640.f + 1910, 600));
	pObj->SetName(L"Ground_test2");
	AddObject(LAYER_TYPE::GROUND, pObj);

	// 충돌 지정
	// Player와 Monster 레이어 간 충돌 체크
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

