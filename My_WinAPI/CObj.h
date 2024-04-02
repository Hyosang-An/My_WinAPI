#pragma once
#include "CEntity.h"

#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"

#include "CComponent.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CFSM.h"
#include "CRigidbody.h"



class CObj :
	public CEntity
{
public:
	friend class CLevel;
	friend class CTaskMgr;

private:
	list<CComponent*> m_listComponent;
	vector<CCollider*> m_vecCollider;

protected:
	Vec2    m_Pos;
	Vec2    m_Scale;
	Vec2	m_Dir;
	float	m_fSpeed;

	bool	m_bAlive;

	LAYER_TYPE	m_eType;
	CAnimator* m_Animator;
	CRigidbody* m_Rigidbody;


private:
	void SetDead() { m_bAlive = false; }

public:
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetPos(float x, float y) { m_Pos = Vec2(x, y); }

	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	void SetScale(float x, float y) { m_Scale = Vec2(x, y); }

	void SetDir(Vec2 _dir) { m_Dir = _dir; m_Dir.Normalize(); }
	void SetDir(float x, float y) { m_Dir = Vec2(x, y); m_Dir.Normalize(); }

	void SetSpeed(float _speed) { m_fSpeed = _speed; }


	void Destroy();

	Vec2 GetPos() { return m_Pos; }
	Vec2 GetRenderPos() { return CCamera::GetInstance().GetRenderPos(m_Pos); }
	Vec2 GetScale() { return m_Scale; }
	Vec2 GetDir() { return m_Dir; }
	float GetSpeed() { return m_fSpeed; }

	bool IsDead() { return !m_bAlive; }
	LAYER_TYPE GetLayerType() { return m_eType; }
	const vector<CCollider*>& GetVecCollider() { return m_vecCollider; }

	template<typename T>
	T* AddComponent(T* _component)
	{
		_component->m_pOwner = this;

		// Collider는 맨 뒤에 추가하고 나머지는 앞에 추가
		if (CCollider* pCollider = dynamic_cast<CCollider*>(_component))
		{
			m_vecCollider.push_back(pCollider);
			m_listComponent.push_back(_component);
		}

		else if (CAnimator* pAnimator = dynamic_cast<CAnimator*>(_component))
		{
			m_Animator = pAnimator;
			m_listComponent.push_front(_component);
		}

		else
			m_listComponent.push_front(_component);

		return _component;
	}

	template<typename T>
	T* GetComponent()
	{
		for (auto& e : m_listComponent)
		{
			T* pComponent = dynamic_cast<T*>(e);
			if (pComponent)
			{
				return pComponent;
			}
		}

		return nullptr;
	}

public:
	virtual void begin();
	virtual void tick();			// 오브젝트의 논리 업데이트 (입력 처리, 상태 변화, 게임 로직 실행 등)
	virtual void finaltick() final;	// 오브젝트가 소유한 컴포넌트 업데이트. 물리 업데이트 (가속도에 의한 속도 변화, 속도에 의한 위치 변화 등)
	virtual void render();

	virtual void OnCollisionEnter(CCollider* _pOtherCollider) {}
	virtual void OnCollisionStay(CCollider* _pOtherCollider) {}
	virtual void OnCollisionExit(CCollider* _pOtherCollider) {}

	virtual CObj* Clone() = 0;

public:
	CObj();
	~CObj();
};

