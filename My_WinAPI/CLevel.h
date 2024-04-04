#pragma once
#include "CEntity.h"

#include "CCamera.h"

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

    virtual void Enter() = 0;   // ������ ��ȯ�ǰ� ó�� �ʱ�ȭ �۾�
    virtual void Exit() = 0;    // ������ ������ �� ��

public:
    void AddObject(LAYER_TYPE _type, CObj* _pObj);
    const vector<CObj*> &GetObjvecOfLayer(LAYER_TYPE _type);
    CObj* FindObjectByName(const wstring& _strName);

public:
    CLevel();
    ~CLevel();
};

