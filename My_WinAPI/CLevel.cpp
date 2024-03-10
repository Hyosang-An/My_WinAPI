#include "pch.h"
#include "CLevel.h"

#include "CObj.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	Safe_Del_Vec(m_vecObj);
}

void CLevel::begin()
{
	for (auto pObj : m_vecObj)
	{
		pObj->begin();
	}
}

void CLevel::tick()
{
	// m_vecObj[i]->tick() 내부에서 m_vecObj에 새로운 요소를 추가하는데, 
	// for를 돌 때마다 m_vecObj.size()를 새로 계산하기 때문에 문제없이 작동한다. 
	// 그러나 범위기반 for를 쓰면 루프를 진입하는 시점에서 벡터의 크기를 계산하고 반복자 범위를 제한하기 때문에
	// 중간에 새로운 요소가 추가되면 문제가 발생한다.
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->tick();
	}
}

void CLevel::finaltick()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->finaltick();
	}
}

void CLevel::render()
{
	for (auto pObj : m_vecObj)
	{
		pObj->render();
	}
}

void CLevel::progress()
{
	tick();
	finaltick();
}

