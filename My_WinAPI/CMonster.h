#pragma once
#include "CObj.h"
class CMonster :
    public CObj
{
private:
    CCollider* m_pCollider;
public:
    virtual void tick() override;
    virtual void render() override;

    virtual CMonster* Clone() override { return new CMonster(*this); }

public:
    CMonster();
    ~CMonster();
};

