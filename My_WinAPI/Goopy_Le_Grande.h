#pragma once
#include "CObj.h"

class CEffect;

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
        
        // 1페이즈 전용
        TRANSITION_TO_PH2,

        // 3페이즈 전용
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

    float               m_SmashTime = 1.5; // Move 상태에서 Smash 하기까지 걸리는 시간


    PHASE_STATE         m_PhaseState = PHASE_STATE::PHASE1;
    BASE_STATE          m_CurBaseState = BASE_STATE::INTRO;
    BASE_STATE          m_PrevBaseState = BASE_STATE::INTRO;

    CCollider*          m_BodyCollider;
    CCollider*          m_PunchCollider;
    CCollider*          m_SmashCollider;
    CCollider*          m_TombBottomCollider;

    map<wstring, CEffect*>  m_mapEffect;
    vector<CTexture*>       m_vecShadowTexture;

    CPlayer*            m_player{};

    CEffect*            m_3Ph_move_dust_effect_R = nullptr;
    CEffect*            m_3Ph_move_dust_effect_L = nullptr;

    // 누적 시간 변수
    float               m_accIdleTime = 0;  // 2페이즈 시작 직후 idle 타임
    float               m_accDeathTime = 0; // 2페이즈 사망 직후 death 타임
    float               m_accMovingTime = 0; // 3페이즈 무빙 타임
    float               m_accTimeSinceLastExplosionFX = 0;

    // 폭발 효과 frequency
    float               m_ExplosionFX_Frequency = 2;

    // 플래그
    bool    m_bSpawn_question = false;     // 2페이즈 전환 물음표 생성 플래그
    bool    m_bSpawn_smash_effect = false; // 3페이즈 smash effect 생성 플래그   
    bool    m_bSpawn_3ph_intro_effect = false; // 3페이즈 intro effect 생성 플래그
    bool    m_bSpawn3Phase = false;     // 3페이즈 보스 소환 플래그
    bool    m_bClear = false;

private:
    void UpdateState();
    void UpdateAnimation();
    void MoveAndAction();

    void Phase1_Update();
    void Phase2_Update();
    void Phase3_Update();

    void LoadAnimation();

    void SpawnEffect(const wstring& _effectName, Vec2 _pos);
    void SpawnEffectAttachedToParent(const wstring& _effectName);

    // 콜백함수
    void EnterGround();
    void LeaveGround();

public:
    int GetHP() { return m_iHP; }
    void SetPhase3Intro() { m_PhaseState = PHASE_STATE::PHASE3; m_CurBaseState = BASE_STATE::INTRO;}
    
public:
    virtual void begin();
    virtual void tick();			
    virtual void render();

    virtual void OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider);
    virtual void OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider);
    virtual void OnCollisionExit(CCollider* _myCollider, CCollider* _pOtherCollider);

    // 보스 클론 X
    virtual Goopy_Le_Grande* Clone() { return nullptr; }

public:
    Goopy_Le_Grande();
    ~Goopy_Le_Grande();
};

