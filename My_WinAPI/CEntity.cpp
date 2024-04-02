#include "pch.h"
#include "CEntity.h"

// ���� ��� ���� �ʱ�ȭ
UINT CEntity::g_NextID = 0;

CEntity::CEntity()
	: m_ID(g_NextID++)
{
}

CEntity::CEntity(const CEntity& _other) :
	m_ID(g_NextID++),
	m_strName(_other.m_strName)
{
}

CEntity::~CEntity()
{
}
