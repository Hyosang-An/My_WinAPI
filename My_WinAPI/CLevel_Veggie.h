#pragma once
#include "CLevel.h"

#include "Veggie.h"
#include "CPlayer.h"

class CLevel_Veggie :
	public CLevel
{
private:
	CPlayer* m_player;
	Veggie* m_Boss;

	void ChangeBoss(Veggie* _next_boss) { m_Boss = _next_boss; }

private:
	virtual void tick();
	virtual void render();

	virtual void LoadBackground();
	virtual void LoadObject();
	virtual void SetCollision();

	virtual void Enter();
	virtual void Exit();

public:
	CLevel_Veggie();
	~CLevel_Veggie();
};

