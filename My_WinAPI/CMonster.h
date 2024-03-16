#pragma once
#include "CObj.h"
class CMonster :
	public CObj
{
private:
	int			m_iHP;
	CCollider*	m_pCollider;

public:
	virtual void tick() override;
	virtual void render() override;

	virtual CMonster* Clone() override { return new CMonster(*this); }

	virtual void OnCollisionEnter(CCollider* _pOwnCollider, CCollider* _pOtherCollider);
	virtual void OnCollisionStay(CCollider* _pOwnCollider, CCollider* _pOtherCollider);
	virtual void OnCollisionExit(CCollider* _pOwnCollider, CCollider* _pOtherCollider);

public:
	CMonster();
	~CMonster();
};

