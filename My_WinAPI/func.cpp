#include "pch.h"
#include "func.h"

#include "CTaskMgr.h"

void SpawnObject(CLevel* _Level, LAYER_TYPE _type, CObj* _pSpawned)
{
	tTask task{};
	task.eType = TASK_TYPE::SPAWN_OBJECT;
	task.param1 = reinterpret_cast<DWORD_PTR>(_Level);
	task.param2 = static_cast<DWORD_PTR>(_type);
	task.param3 = reinterpret_cast<DWORD_PTR>(_pSpawned);

	CTaskMgr::GetInstance().AddTask(task);

}

void ChangeLevel(LEVEL_TYPE _NextLevelType)
{
}
