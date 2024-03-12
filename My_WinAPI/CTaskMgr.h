#pragma once
#include "Singleton.h"

class CObj;

enum class TASK_TYPE
{
    SPAWN_OBJECT,
    DELETE_OBJECT,
    CHANGE_LEVEL,

    END
};

struct tTask
{
    TASK_TYPE   eType;
    DWORD       param1;
    DWORD       param2;
    DWORD       param3;
};

class CTaskMgr :
    public Singleton<CTaskMgr>
{
    friend Singleton<CTaskMgr>;

private:
    vector<tTask>   m_vecTask;
    vector<CObj*>   m_vecGarbageCollector;

public:
    void tick();
    void AddTask(const tTask& _task) { m_vecTask.push_back(_task); }

private:
    void ExcuteTask();
    void ClearGarbageCollector();

private:
    CTaskMgr();
    ~CTaskMgr();
};

