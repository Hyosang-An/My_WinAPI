#pragma once
#include "CObj.h"
class CWorldmap_Point :
    public CObj
{
private:
    LEVEL_TYPE m_Stage;

    CCollider* m_Worldmap_Point_Collider;
public:
    void SetAnimation(const wstring& _strRelativeAnimFilePath);
    void SetStage(LEVEL_TYPE _levelType) { m_Stage = _levelType; }
    void SetColliderOffset(Vec2 _vec);

    virtual void OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider);

    // Clone »ç¿ë X
    CWorldmap_Point* Clone() { return nullptr; }
public:
    CWorldmap_Point();
    ~CWorldmap_Point();
};

