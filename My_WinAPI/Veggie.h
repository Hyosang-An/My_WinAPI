#pragma once
#include "CObj.h"
class Veggie :
    public CObj
{
protected:
    int m_iHP = 1;

    virtual void LoadAnimation() = 0;

    virtual void UpdateState() = 0;
    virtual void UpdateAnimation() = 0;
    virtual void MoveAndAction() = 0;

public:
    int GetHP() { return m_iHP; }

public:
    Veggie();
    ~Veggie();
};

