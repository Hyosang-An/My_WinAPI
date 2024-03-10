#pragma once
#include "CObj.h"
class CMissile :
    public CObj
{
private:
    float   m_fSpeed;

    CCollider* m_pCollider;

private:
    virtual void tick() override;

public:
    virtual CMissile* Clone() { return new CMissile(*this); }

public:
    CMissile();
    ~CMissile();
};

