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
	m_arrLevel[(UINT)LEVEL_TYPE::Test] = new CLevel_Test;
	m_arrLevel[(UINT)LEVEL_TYPE::BOSS_STAGE_1] = new CStage_Goopy_Le_Grande;

	// �ʱ� ���� ����
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


