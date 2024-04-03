#include "pch.h"
#include "CComponent.h"

CComponent::CComponent()
	: m_Owner(nullptr)
{
}

CComponent::CComponent(const CComponent& _other) :
	CEntity(_other),
	m_Owner{}
{
}

CComponent::~CComponent()
{
}
