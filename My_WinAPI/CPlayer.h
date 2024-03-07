#pragma once
#include "CObj.h"
class CPlayer :
    public CObj
{
private:
    float m_fSpeed;

public:
    virtual void begin();
    virtual void tick();
    virtual void finaltick();
    virtual void render();

    virtual CPlayer* Clone() override { return new CPlayer(*this); }

public:
    CPlayer();
    ~CPlayer();
};

