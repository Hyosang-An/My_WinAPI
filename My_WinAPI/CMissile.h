#pragma once
#include "CObj.h"
class CMissile :
	public CObj
{
protected:
	float   m_fSpeed;
	float	m_fAngle;

	CCollider* m_Collider;

	int		m_iOffensePower = 1;

public:
	void SetSpeed(float _speed) { m_fSpeed = _speed; }
	void SetAngle(float _angle) { m_fAngle = _angle; }

	float GetSpeed() const { return m_fSpeed; }
	float GetAngle() const { return m_fAngle; }

	int GetOffensePower() const { return m_iOffensePower; }

public:
	virtual void begin() override {};
	virtual void tick() override;
	virtual void render() override;

public:
	virtual CMissile* Clone() { return new CMissile(*this); }

	virtual void OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider) override;
	virtual void OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider) override;
	virtual void OnCollisionExit(CCollider* _myCollider, CCollider* _pOtherCollider) override;

public:
	CMissile();
	CMissile(const CMissile& _other);
	~CMissile();
};

