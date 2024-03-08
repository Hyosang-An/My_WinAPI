#pragma once
#include "CComponent.h"
class CCollider :
    public CComponent
{
public:
    void finaltick() override;

    CCollider* Clone() { return this; }

public:
    CCollider();
    ~CCollider();
};

