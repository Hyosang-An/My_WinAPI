#pragma once
#include "Singleton.h"

#include "CLevel.h"

class CLevelMgr :
    public Singleton<CLevelMgr>
{
    friend Singleton<CLevelMgr>;

private:
    CLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];
    CLevel* m_pCurrentLevel;

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

