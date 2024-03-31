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

	bool	m_bFacingRight;			// �ٶ󺸴� ����

	float m_DashDuration = 0.5;		// �뽬 ���� �ð�
	bool m_bAirboneDashed = false;	// ���߿��� �뽬 �ߴ���
	float m_HittedDuration = 0.5;	// Hitted ���� ���� �ð�

	bool m_bInvincibleState = false;	// ���� ����
	float m_InvincibleDuratoin = 2;		// ���� ���� �ð�

	float m_bJumping = false;			// ���� ������
	float m_JumpingTime = 0;
	float m_LowJumpKeyTime = 0.5;
	float m_HighJumpKeyTime = 1;		// ���� ������ �ϱ� ���� Ű ���� ���� �ð�

	int m_ParryCount = 1;				// �и� ���� Ƚ��

	bool m_bOnPlatform = false;			// �÷��� ���� �ִ���

	

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

	// Callback �Լ�
	void EnterGround();
	void LeaveGround();

public:
	BASE_STATE	GetBaseState() { return m_CurBaseState; }
	
	void SetOnPlatform(bool _b) { m_bOnPlatform = _b; }

public:
	virtual void begin();
	virtual void tick();

	virtual void render();

	virtual CPlayer* Clone() override { return new CPlayer(*this); }

public:
	CPlayer();
	~CPlayer();
};

