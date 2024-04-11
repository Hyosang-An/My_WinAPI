#include "pch.h"
#include "Question_Mark.h"

#include "CPlayer.h"

Question_Mark::Question_Mark()
{
	m_Question_Mark_Collider = AddComponent(new CCollider);
	m_Question_Mark_Collider->SetName(L"Question Mark Collider");
	m_Question_Mark_Collider->SetScale(Vec2(80, 110));

	m_Animator = AddComponent(new CAnimator);

	m_bAbleParry = true;

	// 애니메이션 로드

	// m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\Question Marks\\c_slime_question_mark_L.json", 12);

	m_Animator->LoadAnimation(L"animation\\Boss\\Goopy Le Grande\\Goopy Le Grande L\\Phase 1\\Transition To Ph2\\Question Marks\\c_slime_question_mark_L.anim");
	m_Animator->Play(L"c_slime_question_mark_L", false);
}

Question_Mark::Question_Mark(const Question_Mark& _other) :
	CObj(_other)
{
	m_Question_Mark_Collider = AddComponent(new CCollider(*_other.m_Question_Mark_Collider));
}

Question_Mark::~Question_Mark()
{
}

void Question_Mark::begin()
{
}

void Question_Mark::tick()
{
	m_accLifeTime += DT;
	if (m_LifeDuration < m_accLifeTime)
		SelfDestruct();
}



