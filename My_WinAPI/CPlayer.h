#pragma once
#include "CObj.h"

enum class SHOOTING_DIR
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,

	END
};

enum class BASE_STATE
{
	IDLE,
	DUCK,
	FIXED,
	RUN,
	DASH,
	AIRBONE,
	DEATH
};

enum class JUMP_STATE
{
	NONE,
	JUMP_START,
	JUMPING
};

enum class ACTION_STATE 
{
	NONE,
	SHOOTING, 
	HITTED,   
	PARRYING  
};

enum class PLAYER_ATTACK_STATE
{
	NORMAL_ATT_1,
	NORMAL_ATT_2,
	NORMAL_ATT_3,

	ULT_ATT_1,
	ULT_ATT_2,
	ULT_ATT_3,

	END
};

class CPlayer :
	public CObj
{
private:
	float m_fSpeed;

	bool			m_bFacingRight;

	float m_DashDuration = 0.5;		// 대쉬 지속 시간
	float m_HittedDuration = 0.5;	// Hitted 상태 지속 시간

	bool m_bInvincibleState = false;	// 무적 상태
	float m_InvincibleDuratoin = 2;		// 무적 지속 시간

	float m_bJumping = false;			// 점프 중인지
	float m_JumpingTime = 0;
	float m_LowJumpKeyTime = 0.5;
	float m_HighJumpKeyTime = 1;		// 높은 점프를 하기 위한 키 누름 지속 시간

	

	SHOOTING_DIR    m_CurShootingDir;
	BASE_STATE		m_CurBaseState;
	JUMP_STATE		m_CurJumpState;
	ACTION_STATE	m_CurActionState;

	SHOOTING_DIR	m_PrevShootingDir;
	BASE_STATE		m_PrevBaseState;
	JUMP_STATE		m_PrevJumpState;
	ACTION_STATE	m_PrevActionState;



	CTexture* m_Texture;

	//CCollider* m_HeadCol;
	CCollider* m_PlayerCollider;

private:
	void UpdateState();
	void MoveAndAction();
	void UpdateAnimation();

	void Shoot(SHOOTING_DIR _dir);

	// Callback 함수
	void EnterGround();
	void LeaveGround();

public:
	BASE_STATE	GetBaseState() { return m_CurBaseState; }

	// 상태 추가
	void AddActionState(ACTION_STATE newState)
	{
		m_CurActionState = static_cast<ACTION_STATE>(static_cast<int>(m_CurActionState) | static_cast<int>(newState));
	}

	// 상태 제거
	void RemoveActionState(ACTION_STATE removeState)
	{
		m_CurActionState = static_cast<ACTION_STATE>(static_cast<int>(m_CurActionState) & ~static_cast<int>(removeState));
	}

	// 상태 확인
	bool IsInActionState(ACTION_STATE checkState)
	{
		return static_cast<int>(m_CurActionState) & static_cast<int>(checkState);
	}


public:
	virtual void begin();
	virtual void tick();

	virtual void render();

	virtual CPlayer* Clone() override { return new CPlayer(*this); }

public:
	CPlayer();
	~CPlayer();
};

