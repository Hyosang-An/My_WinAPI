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
	vector<CCollider*> m_vecCollider;

	// ��Ʃ�� ���� �ڵ�
	CCollider* m_pCollider;

public:
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	void SetPos(float x, float y) { m_Pos = Vec2(x, y); }
	void SetScale(float x, float y) { m_Scale = Vec2(x, y); }

	Vec2 GetPos() { return m_Pos; }
	Vec2 GetScale() { return m_Scale; }
	LAYER_TYPE GetLayerType() { return m_Type; }
	const vector<CCollider*>& GetVecCollider() { return m_vecCollider; }

	template<typename T>
	T* AddComponent(T* _component)
	{
		_component->m_pOwner = this;
		m_vecComponent.push_back(_component);

		if (CCollider* pCollider = dynamic_cast<CCollider*>(_component))
		{
			m_vecCollider.push_back(pCollider);
		}

		return _component;
	}

	template<typename T>
	T* GetComponent()
	{
		for (size_t i = 0; i < m_vecComponent.size(); i++)
		{
			T* pComponent = dynamic_cast<T*>(m_vecComponent);

			if (pComponent)
			{
				return pComponent;
			}
		}

		return nullptr;
	}

public:
	virtual void begin();
	virtual void tick();			// ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����
	virtual void finaltick() final;	// ������Ʈ�� ������ ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����
	virtual void render();

	virtual void OnCollisionEnter(CCollider* _OwnCollider, CCollider* _pOtherCollider) {}
	virtual void OnCollisionStay(CCollider* _OwnCollider, CCollider* _pOtherCollider) {}
	virtual void OnCollisionExit(CCollider* _OwnCollider, CCollider* _pOtherCollider) {}

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

