#pragma once
#include "Singleton.h"

#include "CLevel.h"

class CLevelMgr :
    public Singleton<CLevelMgr>
{
    friend Singleton<CLevelMgr>; friend CTaskMgr;

private:
    CLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];
    CLevel* m_pCurrentLevel;

private:
    void ChangeLevel(LEVEL_TYPE _nextLevelType);

public:
    void init();
    void progress();
    void render();

    CLevel* GetCurrentLevel() { return m_pCurrentLevel; }
    CObj* FindObjectByName(const wstring& _strName);

private:
    CLevelMgr();
    ~CLevelMgr();
};

