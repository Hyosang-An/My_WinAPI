#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CLevel_Stage01.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCollisionMgr.h"

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
	pObj->SetName(L"Player");
	pObj->SetPos(640.f, 384.f);
	pObj->SetScale(100, 100);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pObj);

	pObj = new CMonster;
	pObj->SetName(L"Monster");
	pObj->SetPos(100.f, 100.f);
	pObj->SetScale(100.f, 100.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::MONSTER ,pObj);

	// �浹 ����
	// Player�� Monster ���̾� �� �浹 üũ
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInstance().EnableLayerCollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);

	m_pCurrentLevel->begin();
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

CObj* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	return m_pCurrentLevel->FindObjectByName(_strName);
}


