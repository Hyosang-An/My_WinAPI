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
	CROUCH,
	FIXED,
	RUN,
	DASH,
	JUMP,
	DEATH
};

enum class ACTION_STATE 
{
	NONE = 0,
	SHOOTING = 1 << 0, // 0001
	HITTED = 1 << 1,   // 0010
	PARRYING = 1 << 2  // 0100
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

	SHOOTING_DIR    m_ShootingDir;
	BASE_STATE		m_CurBaseState;
	ACTION_STATE	m_CurActionState;

	BASE_STATE		m_PrevBaseState;


	CTexture* m_Texture;

	CCollider* m_HeadCol;
	CCollider* m_BodyCol;

private:
	void UpdateState();
	void Move();
	void UpdateAnimation();

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

	//virtual void render();

	virtual CPlayer* Clone() override { return new CPlayer(*this); }

public:
	CPlayer();
	~CPlayer();
};

