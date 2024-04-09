#pragma once
#include "CLevel.h"

class CLevel_Goopy_Le_Grande :
	public CLevel
{
private:
	CPlayer* m_player;

	//!µð¹ö±ë
	bool m_bStopTick = false;

private:
	virtual void LoadBackground() override;
	virtual void LoadObject() override;
	virtual void SetCollision() override;

public:
	virtual void Enter() override;
	virtual void tick() override;
	virtual void finaltick() override;
	virtual void render() override;

	virtual void Exit() override;

public:
	CLevel_Goopy_Le_Grande();
	~CLevel_Goopy_Le_Grande();
};

