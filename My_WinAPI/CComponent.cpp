#include "pch.h"
#include "CComponent.h"

CComponent::CComponent()
	: m_Owner(nullptr)
{
}

CComponent::CComponent(const CComponent& _other) :
	m_Owner(nullptr)
{
	// m_Owner �� AddComponent�ϸ鼭 _Component->m_Owner = this;�� ����
}

CComponent::~CComponent()
{
}
