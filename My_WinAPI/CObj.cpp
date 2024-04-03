#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"

#include "CTaskMgr.h"



CObj::CObj() :
	m_eType(LAYER_TYPE::NONE),
	m_bAlive(true),
	m_Animator(nullptr),
	m_Rigidbody{}
{
}

CObj::CObj(const CObj& _other) :
	CEntity(_other),
	m_Pos(_other.m_Pos),
	m_Scale(_other.m_Scale),
	m_bAlive(_other.m_bAlive),
	m_eType(_other.m_eType),
	m_Rigidbody(nullptr),
	m_Animator(nullptr)
{
	//m_Rigidbody = new CRigidbody(*_other.m_Rigidbody);
	//m_Animator = new CAnimator(*_other.m_Animator);

	// 컴포넌트는 실제 하위 클래스에서 추가
	
	//for (auto component : _other.m_listComponent)
	//{
	//	AddComponent(component->Clone());
	//}

	//for (auto collider : _other.m_vecCollider)
	//{
	//	m_vecCollider.push_back(collider->Clone());
	//}
}

CObj::~CObj()
{
	Safe_Del_List(m_listComponent);

	//if (m_pCollider != nullptr)
	//	delete m_pCollider;
}

void CObj::Destroy()
{
	tTask task{};
	task.eType = TASK_TYPE::DELETE_OBJECT;
	task.param1 = reinterpret_cast<DWORD_PTR>(this);

	CTaskMgr::GetInstance().AddTask(task);
}

void CObj::begin()
{
}

void CObj::tick()
{

}

void CObj::finaltick()
{
	for (auto& e : m_listComponent)
	{
		e->finaltick();
	}
}

void CObj::render()
{
	if (m_Animator == nullptr)
		return;

	m_Animator->render();
}

