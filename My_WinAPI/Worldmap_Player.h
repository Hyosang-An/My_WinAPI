#pragma once
#include "CObj.h"

class Z_Button;

class Worldmap_Player :
    public CObj
{
	friend class CCamera;

public:
	enum class DIR
	{
		RIGHT,
		LEFT,
		UP,
		DOWN,

		UP_RIGHT,
		UP_LEFT,
		DOWN_RIGHT,
		DOWN_LEFT
	};

	enum class STATE
	{
		IDLE,
		WALK,
		WIN
	};

private:
	float		m_WalkSpeed = 500;

	CCollider*	m_Worldmap_Player_Collider;

	DIR			m_Dir = DIR::DOWN;
	STATE		m_State = STATE::IDLE;

	float		m_accWinStateTime = 0;

	bool		m_StageSelect = false;
	Z_Button*	m_Z_Button;

	CSound*		m_WinSound = nullptr;

private:
	void UpdateState();
	void UpdateAnimation();
	void MoveAndAction();

	void LoadAnimation();

public:
	void SetWinState() { m_State = STATE::WIN; }

public:
	virtual void begin();			
	virtual void tick();			

	virtual void OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider);
	virtual void OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider) ;
	virtual void OnCollisionExit(CCollider* _myCollider, CCollider* _pOtherCollider) ;

	// Clone »ç¿ë X
	virtual Worldmap_Player* Clone() { return nullptr; }

public:
    Worldmap_Player();
    ~Worldmap_Player();
};

