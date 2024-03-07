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
	HDC SubDC = CEngine::GetInstance().GetSubDC();

	Rectangle(SubDC, m_Pos.x - m_Scale.x * 0.5f
		, m_Pos.y - m_Scale.y * 0.5f
		, m_Pos.x + m_Scale.x * 0.5f
		, m_Pos.y + m_Scale.y * 0.5f);
}


