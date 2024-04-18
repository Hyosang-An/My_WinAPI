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
    virtual void Enter();   // ������ ��ȯ�ǰ� ó�� �ʱ�ȭ �۾�

    virtual void tick();
    virtual void render();

    virtual void LoadBackground();
    virtual void LoadObject();
    virtual void SetCollision();

    virtual void Exit();    // ������ ������ �� ��

public:
    World_Map();
    ~World_Map();
};

