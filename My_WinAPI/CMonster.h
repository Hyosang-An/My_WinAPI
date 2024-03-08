#pragma once
#include "CObj.h"
class CMonster :
    public CObj
{
private:

public:
    virtual void tick() override;
    virtual CMonster* Clone() override { return new CMonster(*this); }

public:
    CMonster();
    ~CMonster();
};

