#pragma once
#include "CComponent.h"
class CCollider :
    public CComponent
{
private:
    Vec2    m_vOffsetPos;
    Vec2    m_vFinalPos;    // finaltick에서 계산
    Vec2    m_vScale;       // 충돌체의 크기

    UINT    m_CollisionCount;
    bool    m_bActive;

public:
    void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
    void SetActive(bool _b) { m_bActive = _b; }
    
    Vec2 GetOffsetPos() { return m_vOffsetPos; }
    Vec2 GetScale() { return m_vScale; }
    Vec2 GetFinalPos() { return m_vFinalPos; }

    void OnCollisionEnter(CCollider* _pOtherCollider);
    void OnCollisionStay(CCollider* _pOtherCollider);
    void OnCollisionExit(CCollider* _pOtherCollider);


public:
    virtual void finaltick() override;

    virtual CCollider* Clone() { return new CCollider(*this); }

public:
    CCollider();
    ~CCollider();
};

