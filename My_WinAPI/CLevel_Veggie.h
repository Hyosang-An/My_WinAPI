#pragma once
#include "CLevel.h"

#include "Veggie.h"
#include "CPlayer.h"

class CBackground;

class CLevel_Veggie :
	public CLevel
{
public:
	enum class PHASE_STATE
	{
		PHASE1,
		PHASE2,
		PHASE3
	};

private:
	PHASE_STATE m_PhaseState = PHASE_STATE::PHASE1;

	CPlayer* m_player;
	Veggie* m_Boss;

	bool m_BossSpawnFlag = false;
	CEffect* m_BurstEffect;
	CBackground* m_BurstDust;

public:
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

