#pragma once
#include "CObj.h"
class CPlatform :
    public CObj
{
    CCollider* m_PlatformCollider;

public:
    virtual void tick() override;
    virtual void OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider) override;
    virtual void OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider) override;
    virtual void OnCollisionExit(CCollider* _myCollider, CCollider* _pOtherCollider) override;

public:
    CLONE(CPlatform)
    CPlatform();
    ~CPlatform();
};

