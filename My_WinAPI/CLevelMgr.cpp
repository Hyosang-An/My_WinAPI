#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CLevel_Test.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCollisionMgr.h"
#include "CPlatform.h"
#include "CGround.h"
#include "CStage_Goopy_Le_Grande.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{
	
}

CLevelMgr::~CLevelMgr()
{
	Safe_Del_Arr(m_arrLevel);
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _nextLevelType)
{
	if (m_arrLevel[(UINT)_nextLevelType] == m_pCurrentLevel)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"현재 레벨과 변경하려는 레벨이 동일합니다.");
		return;
	}

	if (m_arrLevel[(UINT)_nextLevelType] == NULL)
	{
		std::wstring message = L"다음 레벨이 없음!";
		MessageBox(NULL, message.c_str(), L"Error", MB_ICONERROR | MB_OK);
		return;
	}

	// 기존 레벨에서 Exit 한다
	if (m_pCurrentLevel)
	{
		m_pCurrentLevel->Exit();
	}

	// 새로운 레벨로 포인터의 주소값을 교체한다.

	m_pCurrentLevel = m_arrLevel[(UINT)_nextLevelType];
	assert(m_pCurrentLevel);

	// 변경된 새로운 레벨로 Enter 한다.
	m_pCurrentLevel->Enter();
	m_pCurrentLevel->begin();
}

void CLevelMgr::init()
{
	// 모든 레벨 생성
	m_arrLevel[(UINT)LEVEL_TYPE::Test] = new CLevel_Test;
	m_arrLevel[(UINT)LEVEL_TYPE::BOSS_STAGE_1] = new CStage_Goopy_Le_Grande;

	// 초기 레벨 지정
	::ChangeLevel(LEVEL_TYPE::Test);
}

void CLevelMgr::progress()
{
	if (m_pCurrentLevel == nullptr)
		return;

	m_pCurrentLevel->tick();
	m_pCurrentLevel->finaltick();

}

void CLevelMgr::render()
{
	if (nullptr == m_pCurrentLevel)
		return;

	m_pCurrentLevel->render();
}

CObj* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	return m_pCurrentLevel->FindObjectByName(_strName);
}


