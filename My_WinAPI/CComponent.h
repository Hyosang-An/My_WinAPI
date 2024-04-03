#pragma once
#include "CEntity.h"

class CObj;

class CComponent :
    public CEntity
{
    friend class CObj;

protected:
    CObj* m_Owner;

public:
    CObj* GetOwner() { return m_Owner; }

public:
    virtual void finaltick() = 0;

    // 컴포넌트는 Clone 불가
public:
    CComponent();
    CComponent(const CComponent& _other);
    ~CComponent();
};

