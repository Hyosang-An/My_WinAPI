#pragma once
#include "CObj.h"
class CPlayer :
    public CObj
{
public:
    virtual void begin();
    virtual void tick();
    virtual void finaltick();
    virtual void render();

    virtual CObj* Clone() override { return new CPlayer(*this); }

public:
    CPlayer();
    ~CPlayer();
};

