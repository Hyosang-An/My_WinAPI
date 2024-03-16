#pragma once
#include "Singleton.h"

enum class TASK_TYPE
{
    SPAWN_OBJECT,   // 1 : Level, 2 : LAYER_TYPE, 3 : Object Adress
    DELETE_OBJECT,  // 1 : Object Adress
    CHANGE_LEVEL,

    END
};

struct tTask
{
    TASK_TYPE       eType;
    DWORD_PTR       param1;
    DWORD_PTR       param2;
    DWORD_PTR       param3;
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

