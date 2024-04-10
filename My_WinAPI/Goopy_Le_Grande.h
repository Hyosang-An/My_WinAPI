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
        
        // 1������ ����
        TRANSITION_TO_PH2,

        // 3������ ����
        SMASH,
        MOVE,
        TURN_MID_TO_LEFT,
        TURN_MID_TO_RIGHT,
        TURN_LEFT_TO_RIGHT,
        TURN_RIGHT_TO_LEFT,


        DEATH
    };

private:
    bool                m_bFacingRight = false;

    float               m_SlimeHorizontalSpeed = 600;
    vector<float>       m_vecJumpSpeed = { -1500, -1300 };
    float               m_TombHorizontalSpeed = 800;

    int                 m_iHP = 5;
    int                 m_iJumpCnt = 0;
    int                 m_iMaxJumpCnt = 2;

    float               m_SmashTime = 3; // Move ���¿��� Smash �ϱ���� �ɸ��� �ð�


    PHASE_STATE         m_PhaseState = PHASE_STATE::PHASE1;
    BASE_STATE          m_BaseState = BASE_STATE::INTRO;

    CCollider*          m_BodyCollider;
    CCollider*          m_PunchCollider;
    CCollider*          m_SmashCollider;
    CCollider*          m_TombBottomCollider;

    vector<CTexture*>   m_ShadowTextureVec;

    CPlayer*            m_player{};

    // ���� �ð� ����
    float               m_accIdleTime = 0;  // 2������ ���� ���� idle Ÿ��
    float               m_accDeathTime = 0; // 2������ ��� ���� death Ÿ��
    float               m_accMovingTime = 0; // 3������ ���� Ÿ��

    // 3������ ���� ��ȯ �÷���
    bool                m_bSpawn3Phase = false;

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

    // �ݹ��Լ�
    void EnterGround();
    void LeaveGround();

public:
    int GetHP() { return m_iHP; }
    void SetPhase3Intro() { m_PhaseState = PHASE_STATE::PHASE3; m_BaseState = BASE_STATE::INTRO;}
    
public:
    virtual void begin();
    virtual void tick();			
    virtual void render();

    virtual void OnCollisionEnter(CCollider* _pOtherCollider);
    virtual void OnCollisionStay(CCollider* _pOtherCollider);
    virtual void OnCollisionExit(CCollider* _pOtherCollider);

    // ���� Ŭ�� X
    virtual Goopy_Le_Grande* Clone() { return nullptr; }

public:
    Goopy_Le_Grande();
    ~Goopy_Le_Grande();
};

