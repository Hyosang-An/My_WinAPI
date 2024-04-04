#pragma once
#include "CLevel.h"
class CRunAndGunStage1 :
    public CLevel
{
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    CRunAndGunStage1();
    ~CRunAndGunStage1();
};

