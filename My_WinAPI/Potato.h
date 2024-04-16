#pragma once
#include "Veggie.h"

#include "CEffect.h"

class CMissile;

class Potato :
    public Veggie
{
public:
	enum class STATE
	{
		INTRO,
		IDLE,
		SHOOT,
		DEATH
	};


private:
	STATE m_State = STATE::INTRO;

	CCollider* m_BodyCollider;
	map<wstring, CEffect*>  m_mapEffect;

	int m_numberShotsRemaining = 4;

	// 누적 시간
	float m_accIdleTime = 0;

	bool m_ShootFlag = false;
	CMissile* m_Shot;
	void Shoot();

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

	// Clone 사용 X
	virtual Potato* Clone() { return nullptr; }

public:
	Potato();
	~Potato();
};

