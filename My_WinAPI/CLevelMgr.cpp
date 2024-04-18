#include "pch.h"
#include "CLevelMgr.h"

#include "CKeyMgr.h"
#include "CCollisionMgr.h"

#include "CLevel.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"
#include "CGround.h"

#include "Title_Scene.h"
#include "CLevel_Test.h"
#include "World_Map.h"
#include "CLevel_Goopy_Le_Grande.h"
#include "CLevel_Veggie.h"


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
		LOG(LOG_TYPE::DBG_ERROR, L"���� ������ �����Ϸ��� ������ �����մϴ�.");
		return;
	}

	if (m_arrLevel[(UINT)_nextLevelType] == NULL)
	{
		std::wstring message = L"���� ������ ����!";
		MessageBox(NULL, message.c_str(), L"Error", MB_ICONERROR | MB_OK);
		return;
	}

	// ���� �������� Exit �Ѵ�
	if (m_pCurrentLevel)
	{
		m_pCurrentLevel->Exit();
	}

	// ���ο� ������ �������� �ּҰ��� ��ü�Ѵ�.

	m_pCurrentLevel = m_arrLevel[(UINT)_nextLevelType];
	assert(m_pCurrentLevel);

	// ����� ���ο� ������ Enter �Ѵ�.
	m_pCurrentLevel->Enter();
	m_pCurrentLevel->begin();
}

void CLevelMgr::init()
{
	// ��� ���� ����
	m_arrLevel[(UINT)LEVEL_TYPE::TITLE] = new Title_Scene;
	m_arrLevel[(UINT)LEVEL_TYPE::Test] = new CLevel_Test;
	m_arrLevel[(UINT)LEVEL_TYPE::WORLD_MAP] = new World_Map;
	m_arrLevel[(UINT)LEVEL_TYPE::BOSS_STAGE_1] = new CLevel_Goopy_Le_Grande;
	m_arrLevel[(UINT)LEVEL_TYPE::BOSS_STAGE_2] = new CLevel_Veggie;

	// �ʱ� ���� ����
	::ChangeLevel(LEVEL_TYPE::TITLE);
}

void CLevelMgr::progress()
{
	if (m_pCurrentLevel == nullptr)
		return;

	// !�����
	if (KEY_JUST_PRESSED(KEY::P))
		m_bPauseProgress = !m_bPauseProgress;

	if (m_bPauseProgress)
		return;

	static float freezeTime = 0;
	if (m_bFreeze && freezeTime < m_FreezeDuration)
	{
		freezeTime += DT;
	}
	else
	{
		freezeTime = 0;
		m_bFreeze = false;

		m_pCurrentLevel->tick();
		m_pCurrentLevel->finaltick();
	}



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


