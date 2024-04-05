#pragma once
#include "CComponent.h"

#include <functional>

class CRigidbody :
    public CComponent
{
public:
    float   m_fMass;
    Vec2    m_Velocity;
    Vec2    m_Force;                // �߷� �̿��� �ܷ�

    float   m_GravityAccel = 4160;

    float   m_Friction; 

    float   m_MaxWalkSpeed;         // �ִ� ���� �Ǵ� �ӷ�
    float   m_MaxGravitySpeed = 2000;      // �߷����� ���� �ִ� ���ϼӵ� ����


    bool m_UseGravity;
    bool m_OnGround;

    // Player ����
    float m_maxDashSpeed;           

    // CallBack (�⺻������ nullptr �ʱ�ȭ)
    std::function<void()>   m_GroundCallbackFunc;
    std::function<void()>   m_AirCallbackFunc;

public:
    void AddForce(Vec2 _force) { m_Force += _force; }
    void AddVelocity(Vec2 _vel) { m_Velocity += _vel; }

    void SetMass(float _m) { m_fMass = _m; }
    void SetFriction(float _friction) { m_Friction = _friction; }
    void SetMaxWalkSpeed(float _max) { m_MaxWalkSpeed = _max; }
    void SetMaxGravitySpeed(float _max) { m_MaxGravitySpeed = _max; }
    void SetVelocity(Vec2 _vel) { m_Velocity = _vel; }
    void SetVelocity_X(float _vel) { m_Velocity.x = _vel; }
    void SetVelocity_Y(float _vel) { m_Velocity.y = _vel; }
    void SetOnGround(bool _b);

    float GetMass() { return m_fMass; }
    Vec2 GetVelocity() { return m_Velocity; }
    bool IsOnGround() { return m_OnGround; }

    // CallBack �Լ� ����
    void SetGroundCallbackFunc(std::function<void()> func) { m_GroundCallbackFunc = func; }
    void SetAirCallbackFunc(std::function<void()> func) { m_AirCallbackFunc = func; }

public:
    virtual void finaltick() override;

public:
    CRigidbody();
    CRigidbody(const CRigidbody& _other);
    ~CRigidbody();
};

