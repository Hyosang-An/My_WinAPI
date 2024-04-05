#pragma once
#include "CComponent.h"

#include <functional>

class CRigidbody :
    public CComponent
{
public:
    float   m_fMass;
    Vec2    m_Velocity;
    Vec2    m_Force;                // 중력 이외의 외력

    float   m_GravityAccel = 4160;

    float   m_Friction; 

    float   m_MaxWalkSpeed;         // 최대 제한 건는 속력
    float   m_MaxGravitySpeed = 2000;      // 중력으로 인한 최대 낙하속도 제한


    bool m_UseGravity;
    bool m_OnGround;

    // Player 전용
    float m_maxDashSpeed;           

    // CallBack (기본적으로 nullptr 초기화)
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

    // CallBack 함수 설정
    void SetGroundCallbackFunc(std::function<void()> func) { m_GroundCallbackFunc = func; }
    void SetAirCallbackFunc(std::function<void()> func) { m_AirCallbackFunc = func; }

public:
    virtual void finaltick() override;

public:
    CRigidbody();
    CRigidbody(const CRigidbody& _other);
    ~CRigidbody();
};

