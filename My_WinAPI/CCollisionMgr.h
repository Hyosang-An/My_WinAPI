#pragma once
#include "Singleton.h"

class CCollider;

union COLLIDER_ID
{
    struct {
        DWORD LeftID;
        DWORD RightID;
    };
    ULONGLONG ID;
};

class CCollisionMgr :
    public Singleton<CCollisionMgr>
{
    friend Singleton<CCollisionMgr>;

private:
    UINT    m_arrCheck[(UINT)LAYER_TYPE::END];  // 레이어 간의 충동 체크 매트릭스


public:
    void init();
    void tick();

    void EnableLayerCollisionCheck(LAYER_TYPE _leftLayer, LAYER_TYPE _rightLayer);
    void DisableLayerCollisionCheck(LAYER_TYPE _leftLayer, LAYER_TYPE _rightLayer);
    void CollisionCheckReset();

private:
    void CollisionCheck(LAYER_TYPE _leftLayer, LAYER_TYPE _rightLayer);
    bool IsObjCollision(CCollider* _pLeftCollider, CCollider* _pRightCollider);

private:
    CCollisionMgr();
    ~CCollisionMgr();
};

