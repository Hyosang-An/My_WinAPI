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

    bool m_bFreeze = false;
    float m_FreezeDuration = 0.5;

    vector<CTexture*> m_vecKnockOutMsg;

    // �÷��̾� ü�� HUD
    vector<CTexture*> m_vecPlayerHP_HUD;

    // !�����
    bool m_bPauseProgress = false;

private:
    void ChangeLevel(LEVEL_TYPE _nextLevelType);

public:
    void SetWorldmapLevelWin();
    const vector<CTexture*>& GetvecKnockOutMsg() { return m_vecKnockOutMsg; }
    const vector<CTexture*>& GetvecPlayerHP_HUD() { return m_vecPlayerHP_HUD; }

public:
    void init();
    void progress();
    void render();

    CLevel* GetCurrentLevel() { return m_pCurrentLevel; }
    CObj* FindObjectByName(const wstring& _strName);

    void SetFreeze() { m_bFreeze = true; }

private:
    CLevelMgr();
    ~CLevelMgr();
};

