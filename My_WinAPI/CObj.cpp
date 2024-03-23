#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"

#include "CTaskMgr.h"



CObj::CObj() :
	m_eType(LAYER_TYPE::NONE),
	m_bAlive(true),
	m_Animator(nullptr)
{
}

CObj::~CObj()
{
	Safe_Del_Vec(m_vecComponent);

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
	for (size_t i = 0; i < m_vecComponent.size(); i++)
	{
		m_vecComponent[i]->finaltick();
	}
}

void CObj::render()
{
	if (m_Animator == nullptr)
		return;

	m_Animator->render();
}

