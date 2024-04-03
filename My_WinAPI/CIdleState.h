#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
private:
    float m_fRange;
    CObj* m_pTarget;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

    virtual CIdleState* Clone() override { return new CIdleState(*this); }

public:
    CIdleState();
    ~CIdleState();
};

