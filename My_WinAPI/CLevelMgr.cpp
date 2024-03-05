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
	// 모든 레벨 생성
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;

	// 현재 레벨 지정
	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	// 레벨에 물체 추가하기
	CObj* pObj = new CObj;
	pObj->SetPos(640.f, 384.f);
	pObj->SetScale(100, 100);

	m_pCurrentLevel->add
}

void CLevelMgr::progress()
{
}


