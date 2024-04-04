#pragma once
#include "CObj.h"

class CMonster :
	public CObj
{
private:
	int			m_iHP;
	float		m_fDetectRange;

	CCollider*	m_pCollider;

	CFSM*		m_pFSM;

public:
	virtual void begin() override;
	virtual void tick() override;
	virtual void render() override;

	virtual CMonster* Clone() override { return new CMonster(*this); }

	virtual void OnCollisionEnter(CCollider* _pOtherCollider);
	virtual void OnCollisionStay(CCollider* _pOtherCollider);
	virtual void OnCollisionExit(CCollider* _pOtherCollider);

public:
	CMonster();
	CMonster(const CMonster& _other);
	~CMonster();
};

