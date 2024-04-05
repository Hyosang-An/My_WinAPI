#pragma once
#include "CObj.h"
class CWall :
    public CObj
{
private:
    CCollider* m_WallCollider;

public:
    void SetColliderScale(Vec2 _scale);
    virtual CWall* Clone() override { return new CWall(*this); }

    virtual void OnCollisionEnter(CCollider* _pOtherCollider) override;
    virtual void OnCollisionStay(CCollider* _pOtherCollider) override;
    virtual void OnCollisionExit(CCollider* _pOtherCollider) override;

public:
    CWall();
    CWall(const CWall& _other);
    ~CWall();
};

