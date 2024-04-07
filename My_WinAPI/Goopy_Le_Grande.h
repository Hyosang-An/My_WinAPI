#pragma once
#include "CObj.h"



class Goopy_Le_Grande :
    public CObj
{
public:
    enum class PHASE_STATE
    {
        PHASE1,
        PHASE2,
        PHASE3,
    };

    enum class BASE_STATE
    {
        INTRO,
        JUMP,
        AIR_UP,
        UP_DOWN_TRANSITION,
        AIR_DOWN,
        PUNCH,
        TRANSITION_TO_PH2,

    };

private:
    bool                m_bFacingRight = false;

    PHASE_STATE         m_PhaseState = PHASE_STATE::PHASE1;
    BASE_STATE          m_BaseState = BASE_STATE::INTRO;

    CCollider*          m_BodyCollider;
    CCollider*          m_PunchCollider;
    CCollider*          m_SmashCollider;

    vector<CTexture*>   m_ShadowTextureVec;

private:
    void UpdateState();
    void MoveAndAction();
    void UpdateAnimation();

    void LoadAnimation();

    // 콜백함수
    void EnterGround();
    void LeaveGround();
    
public:
    virtual void begin();
    virtual void tick();			
    virtual void render();

    virtual void OnCollisionEnter(CCollider* _pOtherCollider);
    virtual void OnCollisionStay(CCollider* _pOtherCollider);
    virtual void OnCollisionExit(CCollider* _pOtherCollider);

    // 보스 클론 X
    virtual Goopy_Le_Grande* Clone() { return nullptr; }

public:
    Goopy_Le_Grande();
    ~Goopy_Le_Grande();
};

