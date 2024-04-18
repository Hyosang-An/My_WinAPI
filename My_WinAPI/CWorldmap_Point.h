#pragma once
#include "CObj.h"

class CStage_Title_Card;

class CWorldmap_Point :
    public CObj
{
private:
    LEVEL_TYPE m_Stage;

    CCollider* m_Worldmap_Point_Collider;

    CStage_Title_Card* m_Stage_Title_Card;
public:
    void SetAnimation(const wstring& _strRelativeAnimFilePath);
    void SetStage(LEVEL_TYPE _levelType);
    void SetColliderOffset(Vec2 _vec);

    void SelectStage();
    void DeselectStage();

    virtual void begin();
    virtual void tick();

    virtual void OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider);

    // Clone »ç¿ë X
    CWorldmap_Point* Clone() { return nullptr; }
public:
    CWorldmap_Point();
    ~CWorldmap_Point();
};

