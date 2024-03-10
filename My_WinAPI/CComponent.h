#pragma once
#include "CEntity.h"

class CObj;

class CComponent :
    public CEntity
{
    friend class CObj;

protected:
    CObj* m_pOwner;

public:
    CObj* GetOwner() { return m_pOwner; }

public:
    virtual void finaltick() = 0;
    virtual CComponent* Clone() = 0;

public:
    CComponent();
    ~CComponent();
};

