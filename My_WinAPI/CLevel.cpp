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
	// m_vecObj[i]->tick() ���ο��� m_vecObj�� ���ο� ��Ҹ� �߰��ϴµ�, 
	// for�� �� ������ m_vecObj.size()�� ���� ����ϱ� ������ �������� �۵��Ѵ�. 
	// �׷��� ������� for�� ���� ������ �����ϴ� �������� ������ ũ�⸦ ����ϰ� �ݺ��� ������ �����ϱ� ������
	// �߰��� ���ο� ��Ұ� �߰��Ǹ� ������ �߻��Ѵ�.
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

