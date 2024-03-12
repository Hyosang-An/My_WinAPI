#include "pch.h"
#include "CEntity.h"

// 정적 멤버 변수 초기화
UINT CEntity::g_NextID = 0;

CEntity::CEntity()
	: m_ID(g_NextID++)
{
}

CEntity::~CEntity()
{
}
