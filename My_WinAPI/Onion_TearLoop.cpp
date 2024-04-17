#include "pch.h"
#include "Onion_TearLoop.h"

Onion_TearLoop::Onion_TearLoop()
{
	m_bActive = false;
	m_Animator = AddComponent(new CAnimator);

	m_Animator->LoadAnimation(L"animation\\Boss\\Veggie\\onion\\tears\\tear_loop.anim");
}

Onion_TearLoop::~Onion_TearLoop()
{
}

void Onion_TearLoop::Start()
{
	m_bActive = true;

	m_Animator->Play(L"tear_loop", true);
}

void Onion_TearLoop::Stop()
{
	m_bActive = false;
}

void Onion_TearLoop::begin()
{
}

void Onion_TearLoop::tick()
{

}


