#pragma once
#include "CLevel.h"
class World_Map :
    public CLevel
{
public:
    virtual void Enter();   // ������ ��ȯ�ǰ� ó�� �ʱ�ȭ �۾�

    virtual void tick();
    virtual void finaltick();
    virtual void render();

    virtual void LoadBackground();
    virtual void LoadObject();
    virtual void SetCollision();

    virtual void Exit();    // ������ ������ �� ��

public:
    World_Map();
    ~World_Map();
};

