#pragma once
#include "CLevel.h"
class World_Map :
    public CLevel
{
public:
    virtual void Enter();   // 레벨이 전환되고 처음 초기화 작업

    virtual void tick();
    virtual void finaltick();
    virtual void render();

    virtual void LoadBackground();
    virtual void LoadObject();
    virtual void SetCollision();

    virtual void Exit();    // 레벨이 끝날때 할 일

public:
    World_Map();
    ~World_Map();
};

