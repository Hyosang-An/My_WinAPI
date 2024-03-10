#pragma once
#include "CObj.h"
class CPlayer :
    public CObj
{
private:
    float m_fSpeed;

    CCollider* m_pCollider;

public:
    virtual void begin();
    virtual void tick();
    virtual void render();

    virtual CPlayer* Clone() override { return new CPlayer(*this); }

public:
    CPlayer();
    ~CPlayer();
};

