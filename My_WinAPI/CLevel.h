#pragma once
#include "CEntity.h"

#include "CCamera.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"

class CObj;
class CCollider;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>   m_arrObjvec[(UINT)LAYER_TYPE::END];
    
protected:
    bool            m_bLevelClear = false;

    CSound* BGM = nullptr;

    float m_KnockOutframeElapsedTime = 0;
    float m_KnockOutframeDuration = 0.1f;
    int   m_CurKnockOutFrameIdx = 0;

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

    virtual void Enter() = 0;   // ������ ��ȯ�ǰ� ó�� �ʱ�ȭ �۾�
    virtual void Exit() = 0;    // ������ ������ �� ��

    virtual void LevelClear() {}

public:
    void AddObject(LAYER_TYPE _type, CObj* _pObj);
    const vector<CObj*> &GetObjvecOfLayer(LAYER_TYPE _type);
    CObj* FindObjectByName(const wstring& _strName);

public:
    CLevel();
    ~CLevel();
};

