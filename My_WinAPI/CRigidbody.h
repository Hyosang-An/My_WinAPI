#pragma once
#include "CComponent.h"
class CRigidbody :
    public CComponent
{
public:
    float   m_fMass;
    Vec2    m_Velocity;
    Vec2    m_Force;                // �߷� �̿��� �ܷ�

    float   m_GravityAccel;

    float   m_Friction; 

    float   m_MinWalkSpeed;         // �ּ� ���� �ȴ� �ӷ�
    float   m_MaxWalkSpeed;         // �ִ� ���� �Ǵ� �ӷ�
    float   m_MaxGravitySpeed;      // �߷����� ���� �ִ� ���ϼӵ� ����

    bool m_UseGravity;
    bool m_OnGround;

    float m_JumpSpeed;

public:
    void AddForce(Vec2 _force) { m_Force += _force; }
    void SetMass(float _m) { m_fMass = _m; }

    void SetFriction(float _friction) { m_Friction = _friction; }
    void SetMinWalkSpeed(float _min) { m_MinWalkSpeed = _min; }
    void SetMaxWalkSpeed(float _max) { m_MaxGravitySpeed = _max; }
    void SetVelocity(Vec2 _vel) { m_Velocity = _vel; }
    void AddVelocity(Vec2 _vel) { m_Velocity += _vel; }


    float GetMass() { return m_fMass; }

public:
    virtual void finaltick() override;



public:
    CLONE(CRigidbody)
    CRigidbody();
    ~CRigidbody();
};

