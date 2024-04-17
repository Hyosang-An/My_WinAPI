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
	m_bUseGroundCollision(_other.m_bUseGroundCollision),
	m_iGroundCollisionCnt(_other.m_iGroundCollisionCnt),
	m_bAbleParry(_other.m_bAbleParry),
	m_eType(_other.m_eType),
	m_Rigidbody{},
	m_Animator{}
{
	if (_other.m_Rigidbody)
		m_Rigidbody = AddComponent(new CRigidbody(*_other.m_Rigidbody));
	if (_other.m_Animator)
		m_Animator = AddComponent(new CAnimator(*_other.m_Animator));
}

CObj::~CObj()
{
	Safe_Del_List(m_listComponent);

	//if (m_pCollider != nullptr)
	//	delete m_pCollider;
}

void CObj::SelfDestruct()
{
	tTask task{};
	task.eType = TASK_TYPE::DELETE_OBJECT;
	task.param1 = reinterpret_cast<DWORD_PTR>(this);

	if (task.param1 == 0)
	{
		int a = 0;
	}

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
	for (auto& commponent : m_listComponent)
	{
		commponent->finaltick();
	}
}

void CObj::render()
{
	if (m_Animator == nullptr)
		return;

	m_Animator->render();
}

