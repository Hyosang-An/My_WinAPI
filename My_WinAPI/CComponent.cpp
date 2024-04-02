#include "pch.h"
#include "CComponent.h"

CComponent::CComponent()
	: m_Owner(nullptr)
{
}

CComponent::CComponent(const CComponent& _other) :
	m_Owner(nullptr)
{
	// m_Owner 는 AddComponent하면서 _Component->m_Owner = this;로 설정
}

CComponent::~CComponent()
{
}
