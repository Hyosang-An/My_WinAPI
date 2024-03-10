#pragma once
#include "CEntity.h"

class CCollider;
class CComponent;

class CObj :
	public CEntity
{
	friend class CLevel;

private:
	Vec2    m_Pos;
	Vec2    m_Scale;

	LAYER_TYPE m_Type;

	vector<CComponent*> m_vecComponent;

	// ��Ʃ�� ���� �ڵ�
	CCollider* m_pCollider;

public:
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	void SetPos(float x, float y) { m_Pos = Vec2(x, y); }
	void SetScale(float x, float y) { m_Scale = Vec2(x, y); }

	Vec2 GetPos() { return m_Pos; }
	Vec2 GetScale() { return m_Scale; }

	CComponent* AddComponent(CComponent* _component);

	

public:
	virtual void begin();
	virtual void tick();			// ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����
	virtual void finaltick() final;	// ������Ʈ�� ������ ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����
	virtual void render();

	virtual CObj* Clone() = 0;

public:
	// ��Ʃ�� ���� �ڵ�
	void CreateCollider();
	/*void ComponentRender();*/
	CCollider* GetCollider() { return m_pCollider; }

public:
	CObj();
	~CObj();
};

