#pragma once
#include "CObj.h"
class CGround :
	public CObj
{
private:
	static int havePlayerCnt;

	CTexture* m_Texture;

	CCollider* m_GroundCollider;

public:
	void SetColliderScale(Vec2 _scale);

public:
	virtual void begin() override;
	virtual void tick() override;

	virtual void OnCollisionEnter(CCollider* _myCollider, CCollider* _pOtherCollider) override;
	virtual void OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider) override;
	virtual void OnCollisionExit(CCollider* _myCollider, CCollider* _pOtherCollider) override;

public:
	virtual CGround* Clone() override { return new CGround(*this); };
	CGround();
	CGround(const CGround& _other);
	~CGround();
};

