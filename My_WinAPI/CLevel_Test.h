#pragma once
#include "CLevel.h"
class CLevel_Test :
    public CLevel
{
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    CLevel_Test();
    ~CLevel_Test();
};

