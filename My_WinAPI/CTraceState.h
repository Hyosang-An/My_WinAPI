#pragma once
#include "CState.h"
class CTraceState :
    public CState
{
public:
    float m_fRange;
    CObj* m_pTarget;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

    virtual CTraceState* Clone() override { return new CTraceState(*this); } 

public:
    CTraceState();
    ~CTraceState();
};

