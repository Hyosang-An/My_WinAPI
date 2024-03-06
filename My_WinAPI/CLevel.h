#pragma once
#include "CEntity.h"

class CObj;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>   m_vecObj;

public:
    virtual void begin();
    virtual void tick();
    virtual void finaltick();
    virtual void render();

    virtual void progress();

public:
    void AddObject(CObj* _pObj) { m_vecObj.push_back(_pObj); }

public:
    CLevel();
    ~CLevel();
};

