#pragma once
#include "CLevel.h"
class CLevel_Test :
    public CLevel
{
private:
    void CreateAndSaveAnimationByJson();

private:
    virtual void LoadBackground() override;
    virtual void LoadObject() override;
    virtual void SetCollision() override;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    CLevel_Test();
    ~CLevel_Test();
};

