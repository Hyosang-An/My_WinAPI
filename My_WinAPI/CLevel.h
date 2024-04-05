#pragma once
#include "CEntity.h"

#include "CCamera.h"
#include "CCollisionMgr.h"

class CObj;
class CCollider;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>   m_arrObjvec[(UINT)LAYER_TYPE::END];

protected:
    void DeleteAllObjects();
    void DeleteObjectsOfLayer(LAYER_TYPE _LayerType);

public:
    virtual void begin();
    virtual void tick();
    virtual void finaltick();
    virtual void render();

    virtual void LoadBackground() = 0;
    virtual void LoadObject() = 0;
    virtual void SetCollision() = 0;

    virtual void Enter() = 0;   // 레벨이 전환되고 처음 초기화 작업
    virtual void Exit() = 0;    // 레벨이 끝날때 할 일

public:
    void AddObject(LAYER_TYPE _type, CObj* _pObj);
    const vector<CObj*> &GetObjvecOfLayer(LAYER_TYPE _type);
    CObj* FindObjectByName(const wstring& _strName);

public:
    CLevel();
    ~CLevel();
};

