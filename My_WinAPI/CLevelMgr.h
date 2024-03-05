#pragma once
#include "Singleton.h"

class CLevel;

class CLevelMgr :
    public Singleton<CLevelMgr>
{
private:
    CLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];
    CLevel* m_pCurrentLevel;

public:
    void init();
    void progress();

private:
    CLevelMgr();
    ~CLevelMgr();
};

