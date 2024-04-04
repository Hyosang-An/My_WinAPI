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

void CLevel::DeleteAllObjects()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		DeleteObjectsOfLayer((LAYER_TYPE)i);
	}
}

void CLevel::DeleteObjectsOfLayer(LAYER_TYPE _LayerType)
{
	vector<CObj*>& vecObjects = m_arrObjvec[(UINT)_LayerType];

	for (size_t i = 0; i < vecObjects.size(); ++i)
	{
		delete vecObjects[i];
	}

	vecObjects.clear();
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
			if (!m_arrObjvec[i][j]->IsDead())
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
		auto iter = m_arrObjvec[i].begin();
		for (; iter != m_arrObjvec[i].end();)
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrObjvec[i].erase(iter);
			}
			else
			{
				(*iter)->render();
				++iter;
			}
		}
	}
}

void CLevel::AddObject(LAYER_TYPE _type, CObj* _pObj)
{
	m_arrObjvec[(UINT)_type].push_back(_pObj);
	_pObj->m_eType = _type;
}

const vector<CObj*>& CLevel::GetObjvecOfLayer(LAYER_TYPE _type)
{
	return m_arrObjvec[(UINT)_type];
}

CObj* CLevel::FindObjectByName(const wstring& _strName)
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; i++)
	{
		for (auto const obj : m_arrObjvec[i])
		{
			if (obj->GetName() == _strName)
				return obj;
		}
	}

	return nullptr;
}



