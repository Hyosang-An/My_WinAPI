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
	float m_fSpeed;

	bool	m_bFacingRight;			// �ٶ󺸴� ����

	float m_DashDuration = 0.5;		// �뽬 ���� �ð�
	bool m_bAirboneDashed = false;	// ���߿��� �뽬 �ߴ���

	float m_HittedDuration = 0.5;	// Hitted ���� ���� �ð�

	float m_InvincibleDuratoin = 2;		// ���� ���� �ð�

	float m_LowJumpKeyTime = 0.5;
	float m_HighJumpKeyTime = 1;		// ���� ������ �ϱ� ���� Ű ���� ���� �ð�

	float m_ParryDuration = 0.5;		// �и� ���� �ð�
	int m_ParryCount = 1;				// �и� ���� Ƚ��

	bool m_bOnPlatform = false;			// �÷��� ���� �ִ���

	
	// �÷��̾� ���� ���� ������

	bool m_bInvincibleState = false;	// ���� ����

	SHOOTING_DIR    m_CurShootingDir;
	BASE_STATE		m_CurBaseState;
	JUMP_STATE		m_CurJumpState;
	PARRY_STATE		m_CurParryState;
	ACTION_STATE	m_CurActionState;

	SHOOTING_DIR	m_PrevShootingDir;
	BASE_STATE		m_PrevBaseState;
	JUMP_STATE		m_PrevJumpState;
	PARRY_STATE		m_PrevParryState;
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

	void StatusRender();

	virtual CPlayer* Clone() override { return new CPlayer(*this); }

public:
	CPlayer();
	~CPlayer();
};

