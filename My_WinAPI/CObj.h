#pragma once
#include "CEntity.h"

class CCollider;
class CComponent;

class CObj :
	public CEntity
{
private:
	Vec2    m_Pos;
	Vec2    m_Scale;

	vector<CComponent*> m_vecComponent;

	

public:
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	void SetPos(float x, float y) { m_Pos = Vec2(x, y); }
	void SetScale(float x, float y) { m_Scale = Vec2(x, y); }

	Vec2 GetPos() { return m_Pos; }
	Vec2 GetScale() { return m_Scale; }

	CComponent* AddComponent(CComponent* _component);

	// 유튜브 강의 코드
	void CreateCollider();
	CCollider* m_pCollider;

public:
	virtual void begin();
	virtual void tick();
	virtual void finaltick();
	virtual void render();

	virtual CObj* Clone() = 0;

public:
	CObj();
	~CObj();
};

