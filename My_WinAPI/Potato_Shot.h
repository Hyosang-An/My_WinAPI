#pragma once
#include "CMissile.h"
class Potato_Shot :
    public CMissile
{
public:
    virtual void begin() override;
    virtual void render() override;

    virtual Potato_Shot* Clone() { return new Potato_Shot(*this); }

public:
    Potato_Shot();
    Potato_Shot(const Potato_Shot& _other);
    ~Potato_Shot();
};

