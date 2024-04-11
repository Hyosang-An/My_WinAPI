#include "pch.h"
#include "CLevel_Test.h"

#include "CKeyMgr.h"

#include "CForce.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "CMonster.h"
#include "CGround.h"
#include "CBackground.h"
#include "Question_Mark.h"


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

	CreateAndSaveAnimationByJson();
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
		SpawnObject(LAYER_TYPE::FORCE, pForce);
	}
	
	if (KEY_JUST_PRESSED(KEY::N))
		ChangeLevel(LEVEL_TYPE::BOSS_STAGE_1);
}

void CLevel_Test::Enter()
{
	// 카메라 트래킹 설정
	CCamera::GetInstance().SetCameraInitialLookAt(Vec2(640, 384));
	CCamera::GetInstance().SetTrackingState(CAM_TRACKING_STATE::RUN_AND_GUN_STAGE);

	LoadBackground();
	LoadObject();
	SetCollision();


	

}


void CLevel_Test::CreateAndSaveAnimationByJson()
{
	CAnimator* tmp_animator = new CAnimator;


	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead\\Cuphead_R\\Ghost\\cuphead_ghost.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead\\Cuphead_R\\Intros\\Regular\\cuphead_intro_a.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead\\Cuphead_R\\Jump\\Dust\\cuphead_jump_dust_a.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead\\Cuphead_R\\Hit\\Air\\cuphead_hit_air_R.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead\\Cuphead_R\\Special Attack\\Straight\\Ground\\cuphead_ex_straight_R.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead\\Cuphead_R\\Special Attack\\SFX\\cuphead_explode_fx.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead\\Cuphead_L\\Hit\\Air\\cuphead_hit_air_L.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Cuphead\\Cuphead_L\\Special Attack\\Straight\\Ground\\cuphead_ex_straight_L.json", 24);



	// Phase 1 ======================================================================
	// L
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Intro\\slime_intro_L.json", 18);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Down\\slime_air_down_L.json", 18);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Air Up\\slime_air_up_L.json", 18);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Jump\\slime_jump_L.json", 18);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Punch\\slime_punch_L.json", 12);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_1_L.json", 12);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\slime_morph_2_L.json", 12);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\Question Marks\\c_slime_question_mark_L.json", 12);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Up Down Transition\\slime_up_down_trans_L.json", 18);

	// R
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Air Down\\slime_air_down_R.json", 18);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Air Up\\slime_air_up_R.json", 18);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Jump\\slime_jump_R.json", 18);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Punch\\slime_punch_R.json", 12);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Transition To Ph2\\slime_morph_1_R.json", 12);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Transition To Ph2\\slime_morph_2_R.json", 12);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 1\\Up Down Transition\\slime_up_down_trans_R.json", 18);

	// VFX
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Dust\\A\\lg_slime_dust_a.json", 18);


	// Phase 2 ======================================================================
	// L
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Idle\\lg_slime_idle_L.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Jump\\lg_slime_jump_L.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Air Up\\lg_slime_air_up_L.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Air Down\\lg_slime_air_down_L.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Punch\\lg_slime_punch_1_L.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Punch\\lg_slime_punch_2_L.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Up Down Transition\\lg_slime_up_down_trans_L.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Death\\lg_slime_death_L.json", 24);

	// R
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Idle\\lg_slime_idle_R.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Jump\\lg_slime_jump_R.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Air Up\\lg_slime_air_up_R.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Air Down\\lg_slime_air_down_R.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Punch\\lg_slime_punch_1_R.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Punch\\lg_slime_punch_2_R.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Up Down Transition\\lg_slime_up_down_trans_R.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 2\\Death\\lg_slime_death_R.json", 24);

	// VFX
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 2\\Dust\\B\\lg_slime_dust_b.json", 18);


	// Phase 3 ======================================================================
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Intro\\slime_tomb_fall.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Intro\\slime_tomb_slam.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Intro\\Transition\\slime_tomb_trans.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Death\\slime_tomb_death.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Smash\\slime_tomb_smash_1.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Smash\\slime_tomb_smash_2.json", 24);

	// L
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Move\\Left\\slime_tomb_lt_move_L.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Move\\Left\\Trans\\slime_tomb_trans_left_to_mid.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Move\\Left\\Trans\\slime_tomb_trans_mid_to_left.json", 24);

	// R
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 3\\Move\\Right\\slime_tomb_rt_move_R.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 3\\Move\\Right\\Trans\\slime_tomb_trans_right_to_mid.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 3\\Move\\Right\\Trans\\slime_tomb_trans_mid_to_right.json", 24);
	
	// VFX
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Dust(Intro)\\slime_tomb_dust.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Smash\\Dust\\slime_tomb_smash_dust.json", 24);

	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 3\\Move\\GroundFX\\Dust\\slime_tomb_groundfx_L.json", 24);
	tmp_animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande R\\Phase 3\\Move\\GroundFX\\Dust\\slime_tomb_groundfx_R.json", 24);


	delete tmp_animator;
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





	// 물음표 테스트
	CObj* question_mark = new Question_Mark;
	question_mark->SetPos(Vec2(640.f + 200, 384.f - 80));
	AddObject(LAYER_TYPE::NEUTRAL_OBJ, question_mark);

	question_mark = new Question_Mark;
	question_mark->SetPos(Vec2(640.f + 200 * 2, 384.f - 80));
	AddObject(LAYER_TYPE::NEUTRAL_OBJ, question_mark);

	question_mark = new Question_Mark;
	question_mark->SetPos(Vec2(640.f + 200 * 3, 384.f - 80));
	AddObject(LAYER_TYPE::NEUTRAL_OBJ, question_mark);

	question_mark = new Question_Mark;
	question_mark->SetPos(Vec2(640.f + 200 * 4, 384.f - 80));
	AddObject(LAYER_TYPE::NEUTRAL_OBJ, question_mark);

	question_mark = new Question_Mark;
	question_mark->SetPos(Vec2(640.f + 200 * 5, 384.f - 80));
	AddObject(LAYER_TYPE::NEUTRAL_OBJ, question_mark);

	question_mark = new Question_Mark;
	question_mark->SetPos(Vec2(640.f + 200 * 6, 384.f - 80));
	AddObject(LAYER_TYPE::NEUTRAL_OBJ, question_mark);

}

void CLevel_Test::SetCollision()
{
	// 충돌 지정
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::GROUND);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::NEUTRAL_OBJ);


}

void CLevel_Test::Exit()
{
	// 레벨에 있는 모든 오브젝트 삭제한다.
	DeleteAllObjects();
}

