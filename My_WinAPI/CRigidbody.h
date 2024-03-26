#pragma once
#include "CComponent.h"
class CRigidbody :
    public CComponent
{
public:
    float   m_fMass;
    Vec2    m_Velocity;
    Vec2    m_Force;

public:
    virtual void finaltick() override;

public:
    CLONE(CRigidbody)
    CRigidbody();
    ~CRigidbody();
};

