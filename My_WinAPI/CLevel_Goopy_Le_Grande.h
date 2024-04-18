#pragma once
#include "CLevel.h"

#include "Goopy_Le_Grande.h"

class CLevel_Goopy_Le_Grande :
	public CLevel
{
private:
	CPlayer*			m_player;
	Goopy_Le_Grande*	m_Boss;

	float m_KnockOutframeElapsedTime = 0;
	float m_KnockOutframeDuration = 0.15f;
	int   m_CurKnockOutFrameIdx = 0;

public:
	void ChangeBoss(Goopy_Le_Grande* _phase3_boss) { m_Boss = _phase3_boss; }

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

	virtual void LevelClear() override;

public:
	CLevel_Goopy_Le_Grande();
	~CLevel_Goopy_Le_Grande();
};

