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
	virtual void begin() override;
	virtual void tick() override;
	virtual void render() override;

	virtual void OnCollisionEnter(CCollider* _pOtherCollider) override;
	virtual void OnCollisionStay(CCollider* _pOtherCollider) override;
	virtual void OnCollisionExit(CCollider* _pOtherCollider) override;

public:
	virtual CGround* Clone() override { return new CGround(*this); };
	CGround();
	CGround(const CGround& _other);
	~CGround();
};

