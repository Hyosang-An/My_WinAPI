#include "pch.h"
#include "CFSM.h"

#include "CState.h"

CFSM::CFSM() :
	m_CurState(nullptr)
{
}

CFSM::CFSM(const CFSM& _other) :
	CComponent(_other), // �θ� Ŭ������ ���� ������ ȣ��
	m_mapData(_other.m_mapData), // �ϴ� ���� ���� (������ ������ ����)
	m_mapState(), // �ʱ�ȭ�� �ص�, ���� ���� �ʿ�
	m_CurState(nullptr) // ���� �� ���� �ʿ�
{
	// m_mapState ���� ���� ó��
	for (const auto& pair : _other.m_mapState) 
	{
		 m_mapState[pair.first] = pair.second ->Clone();
	}
}

CFSM::~CFSM()
{
	Safe_Del_Map(m_mapState); // �����Ҵ��� �����͸� �����ϸ� ��.
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

	// ������ ������(FSM) �����ϱ�
	_state->m_pOwnerFSM = this;

	// ���� �߰�
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


