#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel_Stage01.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{
	
}

CLevelMgr::~CLevelMgr()
{
	Safe_Del_Arr(m_arrLevel);
}

void CLevelMgr::init()
{
	// ��� ���� ����
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;

	// ���� ���� ����
	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	// ������ ��ü �߰��ϱ�
	CObj* pObj = new CPlayer;
	pObj->SetPos(640.f, 384.f);
	pObj->SetScale(100, 100);
	m_pCurrentLevel->AddObject(pObj);

	pObj = new CMonster;
	pObj->SetPos(800.f, 200.f);
	pObj->SetScale(100.f, 100.f);
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


