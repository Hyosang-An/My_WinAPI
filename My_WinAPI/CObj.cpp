#include "pch.h"
#include "CObj.h"

#include "CEngine.h"
#include "CTimeMgr.h"

CObj::CObj()
{
}

CObj::~CObj()
{
}

void CObj::begin()
{
}

void CObj::tick()
{
	
}

void CObj::finaltick()
{
}

void CObj::render()
{
	Rectangle(SUBDC, (int)(m_Pos.x - m_Scale.x * 0.5f)
		, (int)(m_Pos.y - m_Scale.y * 0.5f)
		, (int)(m_Pos.x + m_Scale.x * 0.5f)
		, (int)(m_Pos.y + m_Scale.y * 0.5f));
}


