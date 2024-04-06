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
    PHASE_STATE     m_PhaseState;
    BASE_STATE      m_BaseState;
    
public:
    virtual void begin();
    virtual void tick();			// ������Ʈ�� �� ������Ʈ (�Է� ó��, ���� ��ȭ, ���� ���� ���� ��)
    virtual void render();

    virtual void OnCollisionEnter(CCollider* _pOtherCollider) {}
    virtual void OnCollisionStay(CCollider* _pOtherCollider) {}
    virtual void OnCollisionExit(CCollider* _pOtherCollider) {}

public:
    Goopy_Le_Grande();
    ~Goopy_Le_Grande();
};

