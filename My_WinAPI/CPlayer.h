#pragma once
#include "CObj.h"

class CPlayer :
	public CObj
{
	friend class CCamera;

public:
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
		INTRO,
		IDLE,
		DUCK,
		FIXED,
		RUN,
		DASH,
		AIRBONE,
		HITTED,
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
		SPECIAL_ATTACK
	};

	enum class PLAYER_ATTACK_STATE
	{
		PEASHOOTER,
		SPREAD,

		END
	};

private:
	float m_RunSpeed = 400;
	float m_DashSpeed = 800;
	float m_JumpSpeed = 900; //1040

	bool	m_bFacingRight = true;			// 바라보는 방향

	int		m_iHP = 3;

	float m_DashDuration = 0.3f;		// 대쉬 지속 시간
	bool m_bAirboneDashed = false;	// 공중에서 대쉬 했는지

	float m_HittedDuration = 0.45f;	// Hitted 상태 지속 시간

	float m_InvincibleDuratoin = 2.f;		// 무적 지속 시간

	float m_LowJumpKeyTime = 0.0f;		// 높은 점프를 하기위한 최소 키 누름 지속 시간
	float m_HighJumpKeyTime = 0.16f;		// 높은 점프를 하기 위한 최대 키 누름 지속 시간

	float m_ParryDuration = 0.5f;		// 패링 지속 시간
	int m_ParryCount = 1;				// 패링 가능 횟수

	bool m_bOnPlatform = false;			// 플랫폼 위에 있는지

	
	// 플레이어 각종 상태 변수들

	bool m_bInvincibleState = false;	// 무적 상태

	SHOOTING_DIR    m_CurShootingDir = SHOOTING_DIR::RIGHT;
	BASE_STATE		m_CurBaseState = BASE_STATE::INTRO;
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


	// 액션 누적 시간 (static 변수들 멤버변수로 전환)
	float invincibleTime = 0;
	float HittedTime = 0;
	float DashTime = 0;
	float m_JumpingTime = 0;
	float parryTime = 0;
	float timeSinceLastShot = 0;
	float duckingTime = 0;
	float alpha = 0;
	float dir = 1;

private:
	void UpdateState();
	void MoveAndAction();
	void UpdateAnimation();

	void Shoot(SHOOTING_DIR _dir);

	// Callback 함수
	void EnterGround();
	void LeaveGround();

public:
	int			GetHP() { return m_iHP; }
	BASE_STATE	GetBaseState() { return m_CurBaseState; }
	
	void SetOnPlatform(bool _b) { m_bOnPlatform = _b; }

public:
	virtual void begin();
	virtual void tick();

	virtual void render();

	virtual void OnCollisionEnter(CCollider* _pOtherCollider) override;
	virtual void OnCollisionStay(CCollider* _pOtherCollider) override;
	virtual void OnCollisionExit(CCollider* _pOtherCollider) override;

	void StatusRender();

	virtual CPlayer* Clone() override { return new CPlayer(*this); }

public:
	CPlayer();
	CPlayer(const CPlayer& _other);
	~CPlayer();
};

