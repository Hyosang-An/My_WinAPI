#pragma once
#include "CMissile.h"
class CGuidedMissile :
    public CMissile
{
private:
    CObj*   m_Target;
    float   m_fRange;

private:
    void    FindTarget();

public:
    virtual void tick() override; 

public:
    CGuidedMissile();
    ~CGuidedMissile();
};

