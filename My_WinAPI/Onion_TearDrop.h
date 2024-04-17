#pragma once
#include "CMissile.h"
class Onion_TearDrop :
    public CMissile
{
private:
    bool m_bFalling = true;

    CTexture* m_Texture;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

    virtual void OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider) override;

    virtual Onion_TearDrop* Clone() { return new Onion_TearDrop(*this); }

public:
    Onion_TearDrop();
    Onion_TearDrop(const Onion_TearDrop& _other);
    ~Onion_TearDrop();
};

