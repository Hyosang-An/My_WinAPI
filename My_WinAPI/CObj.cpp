#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"

#include "CTaskMgr.h"



CObj::CObj() :
	m_eType(LAYER_TYPE::NONE),
	m_bAlive(true),
	m_fSpeed(0),
	m_Animator(nullptr),
	m_Rigidbody{}
{
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

