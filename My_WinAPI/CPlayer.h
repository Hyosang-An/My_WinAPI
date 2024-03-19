#pragma once
#include "CObj.h"
class CPlayer :
    public CObj
{
private:
    float m_fSpeed;

    CTexture* m_Texture;

    CCollider* m_HeadCol;
    CCollider* m_BodyCol;

public:
    virtual void begin();
    virtual void tick();
    virtual void render();

    virtual CPlayer* Clone() override { return new CPlayer(*this); }

public:
    CPlayer();
    ~CPlayer();
};

