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

enum class PARRY_STATE
{
	NONE,
	PARRY,
	PARRY_PINK
};

enum class ACTION_STATE 
{
	NONE,
	SHOOTING, 
	HITTED  
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
	float m_RunSpeed = 200;
	float m_DashSpeed = 300;

	bool	m_bFacingRight = true;			// 바라보는 방향

	float m_DashDuration = 0.5;		// 대쉬 지속 시간
	bool m_bAirboneDashed = false;	// 공중에서 대쉬 했는지

	float m_HittedDuration = 0.5;	// Hitted 상태 지속 시간

	float m_InvincibleDuratoin = 2;		// 무적 지속 시간

	float m_LowJumpKeyTime = 0.5;
	float m_HighJumpKeyTime = 1;		// 높은 점프를 하기 위한 키 누름 지속 시간

	float m_ParryDuration = 0.5;		// 패링 지속 시간
	int m_ParryCount = 1;				// 패링 가능 횟수

	bool m_bOnPlatform = false;			// 플랫폼 위에 있는지

	
	// 플레이어 각종 상태 변수들

	bool m_bInvincibleState = false;	// 무적 상태

	SHOOTING_DIR    m_CurShootingDir = SHOOTING_DIR::RIGHT;
	BASE_STATE		m_CurBaseState = BASE_STATE::IDLE;
	JUMP_STATE		m_CurJumpState = JUMP_STATE::NONE;
	PARRY_STATE		m_CurParryState = PARRY_STATE::NONE;
	ACTION_STATE	m_CurActionState = ACTION_STATE::NONE;
	SHOOTING_DIR	m_PrevShootingDir = SHOOTING_DIR::RIGHT;
	BASE_STATE		m_PrevBaseState = BASE_STATE::IDLE;
	JUMP_STATE		m_PrevJumpState = JUMP_STATE::NONE;
	PARRY_STATE		m_PrevParryState = PARRY_STATE::NONE;
	ACTION_STATE	m_PrevActionState = ACTION_STATE::NONE;


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
	
	void SetOnPlatform(bool _b) { m_bOnPlatform = _b; }

public:
	virtual void begin();
	virtual void tick();

	virtual void render();

	void StatusRender();

	virtual CPlayer* Clone() override { return new CPlayer(*this); }

public:
	CPlayer();
	CPlayer(const CPlayer& _other);
	~CPlayer();
};

