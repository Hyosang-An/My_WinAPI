#pragma once
#include "CObj.h"
class CMissile :
	public CObj
{
protected:
	float   m_fSpeed;
	float	m_fAngle;

	CCollider* m_pCollider;

public:
	void SetSpeed(float _speed) { m_fSpeed = _speed; }
	void SetAngle(float _angle) { m_fAngle = _angle; }

	float GetSpeed() const { return m_fSpeed; }
	float GetAngle() const { return m_fAngle; }

public:
	virtual void tick() override;
	virtual void render() override;

public:
	virtual CMissile* Clone() { return new CMissile(*this); }

	virtual void OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider) override;
	virtual void OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider) override;
	virtual void OnCollisionExit(CCollider* _myCollider, CCollider* _pOtherCollider) override;

public:
	CMissile();
	~CMissile();
};

