#include "pch.h"
#include "CTaskMgr.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "CObj.h"
#include "CCollider.h"

CTaskMgr::CTaskMgr()
{
}

CTaskMgr::~CTaskMgr()
{
}

void CTaskMgr::tick()
{
	ClearGarbageCollector();
	ExcuteTask();
}

void CTaskMgr::ExcuteTask()
{
	// �� ������ ������ ������ �ٲٴ� Task�� �� ���� �����ϵ��� flag ����
	static bool bLevelChanged = false;
	bLevelChanged = false;

	for (size_t i = 0; i < m_vecTask.size(); i++)
	{
		switch (m_vecTask[i].eType)
		{
		case TASK_TYPE::SPAWN_OBJECT:
		{
			// 1 : Level adress, 2 : LAYER_TYPE, 3 : Object Adress

			CLevel* pSpawnLevel = reinterpret_cast<CLevel*>(m_vecTask[i].param1);
			LAYER_TYPE	layer_type = static_cast<LAYER_TYPE>(m_vecTask[i].param2);
			CObj* pObj = reinterpret_cast<CObj*>(m_vecTask[i].param3);

			if (CLevelMgr::GetInstance().GetCurrentLevel() != pSpawnLevel)
			{
				delete pObj;
			}
			else
			{
				pSpawnLevel->AddObject(layer_type, pObj);
				pObj->begin();
			}

			break;
		}
		case TASK_TYPE::DELETE_OBJECT:
		{
			// 1 : Object Adress
			// ���� ���� Obj���� Dead���·� �����ϰ� GarbageCollector�� ��Ƶд�.
			CObj* pDeadObj = reinterpret_cast<CObj*>(m_vecTask[i].param1);

			// ������ ������Ʈ�� ���� ���� ��û�� ���ÿ� ������ ���� ��� �� ���� ó���ϵ��� ��.
 			if (pDeadObj->IsDead())
				break;

			pDeadObj->SetDead();
			m_vecGarbageCollector.push_back(pDeadObj);

			// �浹ü ���ֱ�
			for (auto& collider : pDeadObj->GetVecCollider())
			{
				collider->SetActive(false);
			}

			break;
		}
		case TASK_TYPE::CHANGE_LEVEL:
		{

			break;
		}
		}
	}

	m_vecTask.clear();
}

void CTaskMgr::ClearGarbageCollector()
{
	Safe_Del_Vec(m_vecGarbageCollector);
	m_vecGarbageCollector.clear();
}
