#include "pch.h"
#include "CLevel.h"

#include "CObj.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
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
	for (auto pObj : m_vecObj)
	{
		pObj->tick();
	}
}

void CLevel::finaltick()
{
	for (auto pObj : m_vecObj)
	{
		pObj->finaltick();
	}
}

void CLevel::render()
{
	for (auto pObj : m_vecObj)
	{
		pObj->render();
	}
}

