#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel_Stage01.h"
#include "CObj.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
}

void CLevelMgr::init()
{
	// ��� ���� ����
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;

	// ���� ���� ����
	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	// ������ ��ü �߰��ϱ�
	CObj* pObj = new CObj;
	pObj->SetPos(640.f, 384.f);
	pObj->SetScale(100, 100);

	m_pCurrentLevel->AddObject(pObj);
}

void CLevelMgr::progress()
{
	if (m_pCurrentLevel == nullptr)
		return;

	m_pCurrentLevel->progress();
}

void CLevelMgr::render()
{
	m_pCurrentLevel->render();
}


