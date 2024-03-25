#pragma once
#include "CState.h"
class CTraceState :
    public CState
{
public:
    float Range;
    float Speed;
    CObj* pSelf;
    CObj* pTarget;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;



public:
    CTraceState();
    ~CTraceState();
};

