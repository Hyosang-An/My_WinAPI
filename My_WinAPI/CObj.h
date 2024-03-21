#pragma once
#include "CEntity.h"

#include "CAssetMgr.h"
#include "CTimeMgr.h"

class CCollider;
class CComponent;
class CAnimator;

class CObj :
	public CEntity
{
	friend class CLevel;
	friend class CTaskMgr;

private:
	Vec2    m_Pos;
	Vec2    m_Scale;
	bool	m_bAlive;

	vector<CComponent*> m_vecComponent;
	vector<CCollider*> m_vecCollider;

protected:
	LAYER_TYPE	m_eType;
	CAnimator* m_Animator;

private:
	void SetDead() { m_bAlive = false; }

public:
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	void SetPos(float x, float y) { m_Pos = Vec2(x, y); }
	void SetScale(float x, float y) { m_Scale = Vec2(x, y); }
	void Destroy();

	Vec2 GetPos() { return m_Pos; }
	Vec2 GetScale() { return m_Scale; }
	bool IsDead() { return !m_bAlive; }
	LAYER_TYPE GetLayerType() { return m_eType; }
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
	virtual void tick();			// 오브젝트가 매 프레임마다 해야할 작업을 구현
	virtual void finaltick() final;	// 오브젝트가 소유한 컴포넌트가 매 프레임마다 해야할 작업을 구현
	virtual void render();

	virtual void OnCollisionEnter(CCollider* _pOwnCollider, CCollider* _pOtherCollider) {}
	virtual void OnCollisionStay(CCollider* _pOwnCollider, CCollider* _pOtherCollider) {}
	virtual void OnCollisionExit(CCollider* _pOwnCollider, CCollider* _pOtherCollider) {}

	virtual CObj* Clone() = 0;

public:
	CObj();
	~CObj();
};

