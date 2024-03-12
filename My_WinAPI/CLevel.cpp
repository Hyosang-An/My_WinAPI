#include "pch.h"
#include "CLevel.h"

#include "CObj.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	for (size_t i = 0; i < (size_t)LAYER_TYPE::END; i++)
	{
		Safe_Del_Vec(m_arrObjvec[i]);
	}
	
}

void CLevel::begin()
{
	for (size_t i = 0; i < (size_t)LAYER_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObjvec[i].size(); j++)
		{
			m_arrObjvec[i][j]->begin();
		}
	}
}

void CLevel::tick()
{
	// m_arrObjvec[i]->tick() ���ο��� m_vecObj�� ���ο� ��Ҹ� �߰��ϴµ�, 
	// for�� �� ������ m_arrObjvec.size()�� ���� ����ϱ� ������ �������� �۵��Ѵ�. 
	// �׷��� ������� for�� ���� ������ �����ϴ� �������� ������ ũ�⸦ ����ϰ� �ݺ��� ������ �����ϱ� ������
	// �߰��� ���ο� ��Ұ� �߰��Ǹ� ������ �߻��Ѵ�.
	for (size_t i = 0; i < (size_t)LAYER_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObjvec[i].size(); j++)
		{
			m_arrObjvec[i][j]->tick();
		}
	}
}

void CLevel::finaltick()
{
	for (size_t i = 0; i < (size_t)LAYER_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObjvec[i].size(); j++)
		{
			m_arrObjvec[i][j]->finaltick();
		}
	}
}

void CLevel::render()
{
	for (size_t i = 0; i < (size_t)LAYER_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObjvec[i].size(); j++)
		{
			m_arrObjvec[i][j]->render();
		}
	}
}

void CLevel::progress()
{
	tick();
	finaltick();
}


void CLevel::AddObject(LAYER_TYPE _type, CObj* _pObj)
{
	m_arrObjvec[(UINT)_type].push_back(_pObj);
	_pObj->m_eType = _type;
}

const vector<CObj*>& CLevel::GetObjvec(LAYER_TYPE _type)
{
	return m_arrObjvec[(UINT)_type];
}



