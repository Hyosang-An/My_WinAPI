#include "pch.h"
#include "CFSM.h"

#include "CState.h"

CFSM::CFSM() :
	m_CurState(nullptr)
{
}

CFSM::~CFSM()
{
	Safe_Del_Map(m_mapState); // 동적할당한 데이터만 삭제하면 됨.
}

void CFSM::finaltick()
{
	if (nullptr == m_CurState)
		return;

	m_CurState->finaltick();
}

void CFSM::AddState(const wstring& _strStateName, CState* _state)
{
	assert(!FindState(_strStateName));

	// 상태의 소유자(FSM) 세팅하기
	_state->m_pOwnerFSM = this;

	// 상태 추가
	m_mapState.insert(make_pair(_strStateName, _state));
}

CState* CFSM::FindState(const wstring& _strStateName)
{
	auto iter = m_mapState.find(_strStateName);

	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}

void CFSM::ChangeState(const wstring& _strNextStateName)
{
	if (m_CurState && (m_CurState->GetName() == _strNextStateName))
		return;

	if (m_CurState != nullptr)
		m_CurState->Exit();

	m_CurState = FindState(_strNextStateName);

	assert(m_CurState);

	m_CurState->Enter();
}

void CFSM::SetBlackboardData(const wstring& _strDataKey, DATA_TYPE _Type, void* _pData)
{
	tBlackboardData data{ _Type, _pData };
	m_mapData.insert(make_pair(_strDataKey, data));
}


