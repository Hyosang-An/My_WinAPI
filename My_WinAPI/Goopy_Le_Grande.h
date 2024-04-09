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
        IDLE,
        JUMP,
        AIR_UP,
        UP_DOWN_TRANSITION,
        AIR_DOWN,
        PUNCH,

        TRANSITION_TO_PH2,

        DEATH
    };

private:
    bool                m_bFacingRight = false;

    float               m_HorizontalSpeed = 600;
    vector<float>       m_vecJumpSpeed = { -1500, -1300 };

    int                 m_iHP = 5;
    int                 m_iJumpCnt = 0;
    int                 m_iMaxJumpCnt = 2;

    float               m_IdleTime = 0;  // 2페이즈 시작 직후 idle 타임

    PHASE_STATE         m_PhaseState = PHASE_STATE::PHASE1;
    BASE_STATE          m_BaseState = BASE_STATE::INTRO;

    CCollider*          m_BodyCollider;
    CCollider*          m_PunchCollider;
    CCollider*          m_SmashCollider;

    vector<CTexture*>   m_ShadowTextureVec;

    CPlayer*            m_player{};

private:
    void UpdateState();
    void MoveAndAction();
    void UpdateAnimation();

    void Phase1_Update();
    void Phase2_Update();
    void Phase3_Update();

    //void ChangePhaseState(PHASE_STATE _phaseState);
    //void ChangeBaseState(BASE_STATE _baseState);

    void LoadAnimation();

    // 콜백함수
    void EnterGround();
    void LeaveGround();

public:
    int GetHP() { return m_iHP; }
    void SetPhase3Intro() { m_PhaseState = PHASE_STATE::PHASE3; m_BaseState = BASE_STATE::INTRO; }
    
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

