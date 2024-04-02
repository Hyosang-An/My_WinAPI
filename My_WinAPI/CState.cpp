#include "pch.h"
#include "CState.h"

CState::CState() :
	m_pOwnerFSM(nullptr)
{
}

CState::CState(const CState& _other) :
	m_pOwnerFSM(nullptr)
{
}

CState::~CState()
{
}
