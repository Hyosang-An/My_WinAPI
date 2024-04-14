#pragma once
#include "CMissile.h"
class Peashooter :
    public CMissile
{
private:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

    void OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider);

    virtual Peashooter* Clone() { return new Peashooter(*this); }

public:
    Peashooter();
    Peashooter(const Peashooter& _other);
    ~Peashooter();
};

