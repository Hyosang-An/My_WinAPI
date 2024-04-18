#pragma once
#include "CLevel.h"

class Worldmap_Player;

class World_Map :
    public CLevel
{
private:
    bool    m_bFirstEnter = true;
    bool    m_bWinState = false;

    Worldmap_Player*    m_WorldmapPlayer;
    Vec2 m_LastWorldmapPlayerPos;

public:
    void SetWinState() { m_bWinState = true; }

public:
    virtual void Enter();   // 레벨이 전환되고 처음 초기화 작업

    virtual void tick();
    virtual void render();

    virtual void LoadBackground();
    virtual void LoadObject();
    virtual void SetCollision();

    virtual void Exit();    // 레벨이 끝날때 할 일

public:
    World_Map();
    ~World_Map();
};

