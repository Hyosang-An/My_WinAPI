#pragma once
#include "CObj.h"
class Question_Mark :
	public CObj
{
private:
	CCollider* m_Question_Mark_Collider;

	float m_LifeDuration = 2;
	float m_accLifeTime = 0;

public:
	virtual void begin();
	virtual void tick();

	virtual Question_Mark* Clone() { return new Question_Mark(*this); }

public:
	Question_Mark();
	Question_Mark(const Question_Mark& _other);
	~Question_Mark();

};

