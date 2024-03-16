#pragma once
#include "CObj.h"
class CMissile :
	public CObj
{
private:
	float   m_fSpeed;

	CCollider* m_pCollider;

private:
	virtual void tick() override;
	virtual void render() override;

public:
	virtual CMissile* Clone() { return new CMissile(*this); }

	virtual void OnCollisionEnter(CCollider* _pOwnCollider, CCollider* _pOtherCollider) override;
	virtual void OnCollisionStay(CCollider* _pOwnCollider, CCollider* _pOtherCollider) override;
	virtual void OnCollisionExit(CCollider* _pOwnCollider, CCollider* _pOtherCollider) override;

public:
	CMissile();
	~CMissile();
};

