#pragma once
#include "CObj.h"

class Onion_TearLoop :
    public CObj
{
private:
	vector<CObj*> m_vecFX;

public:
	void Start();
	void Stop();

public:
	virtual void begin();			
	virtual void tick();			

	// Clone »ç¿ë X
	virtual Onion_TearLoop* Clone() { return nullptr; }

public:
	Onion_TearLoop();
	~Onion_TearLoop();
};

