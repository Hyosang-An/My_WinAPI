#include "pch.h"
#include "Peashooter.h"

Peashooter::Peashooter()
{
	m_fSpeed = 2000;

	m_Animator = AddComponent(new CAnimator);


	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Weapon\\Peashooter\\Down\\Peashooter_down.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Weapon\\Peashooter\\Down_Left\\Peashooter_down_left.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Weapon\\Peashooter\\Down_Right\\Peashooter_down_right.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Weapon\\Peashooter\\Left\\Peashooter_left.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Weapon\\Peashooter\\Right\\Peashooter_right.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Weapon\\Peashooter\\Up\\Peashooter_up.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Weapon\\Peashooter\\Up_Left\\Peashooter_up_left.json", 12);
	//m_Animator->CreateAndSaveAnimationFileByJSON(L"animation\\Weapon\\Peashooter\\Up_Right\\Peashooter_up_right.json", 12);

	m_Animator->LoadAnimation(L"animation\\Weapon\\Peashooter\\Down\\Peashooter_down.anim");
	m_Animator->LoadAnimation(L"animation\\Weapon\\Peashooter\\Down_Left\\Peashooter_down_left.anim");
	m_Animator->LoadAnimation(L"animation\\Weapon\\Peashooter\\Down_Right\\Peashooter_down_right.anim");
	m_Animator->LoadAnimation(L"animation\\Weapon\\Peashooter\\Left\\Peashooter_left.anim");
	m_Animator->LoadAnimation(L"animation\\Weapon\\Peashooter\\Right\\Peashooter_right.anim");
	m_Animator->LoadAnimation(L"animation\\Weapon\\Peashooter\\Up\\Peashooter_up.anim");
	m_Animator->LoadAnimation(L"animation\\Weapon\\Peashooter\\Up_Left\\Peashooter_up_left.anim");
	m_Animator->LoadAnimation(L"animation\\Weapon\\Peashooter\\Up_Right\\Peashooter_up_right.anim");
}

Peashooter::Peashooter(const Peashooter& _other)
{
}

Peashooter::~Peashooter()
{
}

void Peashooter::begin()
{
	// 애니메이션
	if (m_fAngle == 0)
	{
		m_Animator->Play(L"Peashooter_right", false);
	}
	else if (m_fAngle == PI / 4)
	{
		m_Animator->Play(L"Peashooter_down_right", false);
	}
	else if (m_fAngle == PI / 4 * 2)
	{
		m_Animator->Play(L"Peashooter_down", false);
	}
	else if (m_fAngle == PI / 4 * 3)
	{
		m_Animator->Play(L"Peashooter_down_left", false);
	}
	else if (m_fAngle == PI / 4 * 4)
	{
		m_Animator->Play(L"Peashooter_left", false);
	}
	else if (m_fAngle == PI / 4 * 5)
	{
		m_Animator->Play(L"Peashooter_up_left", false);
	}
	else if (m_fAngle == PI / 4 * 6)
	{
		m_Animator->Play(L"Peashooter_up", false);
	}
	else if (m_fAngle == PI / 4 * 7)
	{
		m_Animator->Play(L"Peashooter_up_right", false);
	}
}

void Peashooter::tick()
{
	// 위치 업데이트
	Vec2 vPos = GetPos();
	Vec2 vDir = Vec2(cosf(m_fAngle), sinf(m_fAngle));
	vDir.Normalize();
	vPos += DT * m_fSpeed * vDir;
	SetPos(vPos);

	

}

void Peashooter::render()
{
	CObj::render();
}

void Peashooter::OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider)
{
	CObj* pOtherObj = _pOtherCollider->GetOwner();

	if (pOtherObj->GetLayerType() == LAYER_TYPE::MONSTER || pOtherObj->GetLayerType() == LAYER_TYPE::BOSS)
	{
		// TODO
		//  터지는 이펙트 
	}
}


