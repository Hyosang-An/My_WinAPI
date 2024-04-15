#include "pch.h"
#include "Cloud.h"

Cloud::Cloud()
{
}

Cloud::~Cloud()
{
}

void Cloud::SetStageLimit(float leftLimit, float rightLimit)
{
	m_StageLeftLimit = leftLimit; 
	m_StageRightLimit = rightLimit;
}

void Cloud::begin()
{
	m_Scale.x = m_Texture->GetWidth();
	m_Scale.y = m_Texture->GetHeight();
}

void Cloud::tick()
{
	CBackground::tick();

	// 스테이지 리밋 배율
	float constant = 2.f;

	if (m_Speed < 0)
	{
		if (m_Pos.x + m_Scale.x * 0.5f < m_StageLeftLimit * constant)
			m_Pos.x = m_StageRightLimit * constant + m_Scale.x * 0.5f;
	}
	else
	{
		if (m_StageRightLimit * constant < m_Pos.x - m_Scale.x * 0.5f)
			m_Pos.x = m_StageLeftLimit * constant - m_Scale.x * 0.5f;
	}

	m_Pos.x += m_Speed * DT;


}

