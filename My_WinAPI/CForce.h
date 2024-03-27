#pragma once
#include "CObj.h"
class CForce :
    public CObj
{
private:
    float   m_fForceMagnitude;
    float   m_fRange;
    float   m_fDuration;
    float   m_fElapsedTime;

private:
    void AddForce(LAYER_TYPE _type);

public:
    void SetForce(float _force, float _range, float _duration);

public:
    virtual void tick() override;

public:
    CLONE(CForce)
    CForce();
    ~CForce();
};

