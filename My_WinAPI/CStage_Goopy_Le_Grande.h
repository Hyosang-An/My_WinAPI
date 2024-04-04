#pragma once
#include "CLevel.h"

class CStage_Goopy_Le_Grande :
	public CLevel
{
private:
	void LoadBackGround();

public:
	virtual void Enter() override;
	virtual void tick() override;

	virtual void Exit() override;

public:
	CStage_Goopy_Le_Grande();
	~CStage_Goopy_Le_Grande();
};

