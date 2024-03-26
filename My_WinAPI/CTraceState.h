#pragma once
#include "CState.h"
class CTraceState :
    public CState
{
public:
    float m_fRange;
    CObj* m_pSelf;
    CObj* m_pTarget;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;



public:
    CLONE(CTraceState)
    CTraceState();
    ~CTraceState();
};

