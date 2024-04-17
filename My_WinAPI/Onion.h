#pragma once
#include "Veggie.h"

#include "Onion_TearLoop.h"

class CMissile;
class CEffect;

class Onion :
    public Veggie
{
public:
	enum class STATE
	{
		INTRO,
		IDLE,
		CRY_INTRO,
		CRY,
		CRY_OUTRO,
		DEATH
	};

private:
	STATE m_State = STATE::INTRO;
	CCollider* m_BodyCollider;
	map<wstring, CEffect*> m_mapEffect;

	float m_DropTearFrequency = 2;
	CMissile* m_TearDrop = nullptr;

	Onion_TearLoop* m_Onion_TearLoop = nullptr;


	// ���� �ð�
	float m_accIdleTime = 0;
	float m_accCryTime = 0;
	float m_acctimeSinceLastTearDrop = 0;

private:
	void DropTear();

	virtual void LoadAnimation() override;

	virtual void UpdateState() override;
	virtual void UpdateAnimation() override;
	virtual void MoveAndAction() override;

	void SpawnEffect(const wstring& _effectName, Vec2 _pos);

public:
	STATE GetState() { return m_State; }

public:
	virtual void begin();
	virtual void tick();
	//virtual void render();

	virtual void OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider);

	// Clone ��� X
	virtual Onion* Clone() { return nullptr; }

public:
	Onion();
	~Onion();
};

