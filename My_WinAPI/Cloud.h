#pragma once
#include "CBackground.h"
class Cloud :
    public CBackground
{
private:
    float m_StageLeftLimit = 0;
    float m_StageRightLimit = 0;

    float m_Speed = 0;

public:
    void SetSpeed(float speed) { m_Speed = speed; }
    void SetStageLimit(float leftLimit, float rightLimit);
public:
    virtual void begin() override;
    virtual void tick() override;

    // Clone »ç¿ë X
    Cloud* Clone() { return nullptr; }

public:
    Cloud();
    ~Cloud();
};

