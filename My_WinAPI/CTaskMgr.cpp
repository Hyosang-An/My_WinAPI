#include "pch.h"
#include "CTaskMgr.h"

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
	// 한 프레임 내에서 레벨을 바꾸는 Task는 한 번만 수행하도록 flag 설정
	static bool bLevelChanged = false;
	bLevelChanged = false;

	for (size_t i = 0; i < m_vecTask.size(); i++)
	{
		switch (m_vecTask[i].eType)
		{
		case TASK_TYPE::SPAWN_OBJECT:
		{

			break;
		}
		case TASK_TYPE::DELETE_OBJECT:
		{

			break;
		}
		case TASK_TYPE::CHANGE_LEVEL:
		{

			break;
		}
		}
	}
}

void CTaskMgr::ClearGarbageCollector()
{
}
