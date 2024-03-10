#pragma once
#include "CComponent.h"
class CCollider :
    public CComponent
{
private:
    Vec2    m_vOffsetPos;
    Vec2    m_vFinalPos;    // finaltick���� ���

    Vec2    m_vScale;       // �浹ü�� ũ��

public:
    void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
    
    Vec2 GetOffsetPos() { return m_vOffsetPos; }
    Vec2 GetScale() { return m_vOffsetPos; }

    void render();

public:
    virtual void finaltick() override;

    virtual CCollider* Clone() { return new CCollider(*this); }

public:
    CCollider();
    ~CCollider();
};

