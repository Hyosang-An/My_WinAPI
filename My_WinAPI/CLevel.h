#pragma once
#include "CEntity.h"

class CObj;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>   m_arrObjvec[(UINT)LAYER_TYPE::END];

public:
    virtual void begin();
    virtual void tick();
    virtual void finaltick();
    virtual void render();

    virtual void progress();

    virtual CLevel* Clone() = 0;

public:
    void AddObject(LAYER_TYPE _type, CObj* _pObj);

public:
    CLevel();
    ~CLevel();
};

