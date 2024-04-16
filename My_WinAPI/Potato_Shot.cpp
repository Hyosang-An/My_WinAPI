#include "pch.h"
#include "Potato_Shot.h"

Potato_Shot::Potato_Shot()
{
	m_fSpeed = 320;
	m_fAngle = PI;

	m_Collider->SetScale(Vec2(80, 80));

	m_Animator = AddComponent(new CAnimator);
	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\potato\\shot\\veggie_potato_shot.anim");
}

Potato_Shot::Potato_Shot(const Potato_Shot& _other) :
	CMissile(_other)
{
}

Potato_Shot::~Potato_Shot()
{
}

void Potato_Shot::begin()
{
	m_Animator->Play(L"veggie_potato_shot", true);
}

void Potato_Shot::render()
{
	CObj::render();
}


