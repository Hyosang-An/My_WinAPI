#include "pch.h"
#include "CWorldmap_Point.h"

#include "CKeyMgr.h"
#include "CStage_Title_Card.h"

CWorldmap_Point::CWorldmap_Point() :
	m_Stage{},
	m_Stage_Title_Card{}
{
	m_Animator = AddComponent(new CAnimator);

	m_Worldmap_Point_Collider = AddComponent(new CCollider);
	m_Worldmap_Point_Collider->SetScale(Vec2(150, 150));

	m_Stage_Title_Card = new CStage_Title_Card;
}

CWorldmap_Point::~CWorldmap_Point()
{
}

void CWorldmap_Point::begin()
{
	SpawnObject(LAYER_TYPE::UI, m_Stage_Title_Card);
}

void CWorldmap_Point::tick()
{
	if (m_Stage_Title_Card->IsActive() && KEY_JUST_PRESSED(KEY::Z))
	{
		ChangeLevel(m_Stage);
	}
}

void CWorldmap_Point::SetAnimation(const wstring& _strRelativeAnimFilePath)
{
	m_Animator->Play(m_Animator->LoadAnimation(_strRelativeAnimFilePath)->GetName(), true);
}

void CWorldmap_Point::SetStage(LEVEL_TYPE _levelType)
{
	m_Stage = _levelType;

	switch (m_Stage)
	{
		case LEVEL_TYPE::BOSS_STAGE_1:
			m_Stage_Title_Card->SetTitleTex(L"Goopy Le Grande");
			break;
		case LEVEL_TYPE::BOSS_STAGE_2:
			m_Stage_Title_Card->SetTitleTex(L"The Root Pack");
			break;
	}
}

void CWorldmap_Point::SetColliderOffset(Vec2 _vec)
{
	m_Worldmap_Point_Collider->SetOffsetPos(_vec);
}

void CWorldmap_Point::SelectStage()
{
	m_Stage_Title_Card->SetActive(true);
}

void CWorldmap_Point::DeselectStage()
{
	m_Stage_Title_Card->SetActive(false);
}



void CWorldmap_Point::OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider)
{
	//if (_pOtherCollider->GetOwner()->GetLayerType() == LAYER_TYPE::WORLDMAP_PLAYER)
	//{
	//	if (!m_Stage_Title_Card->IsActive())
	//	{
	//		if (KEY_JUST_PRESSED(KEY::Z))
	//			m_Stage_Title_Card->SetActive(true);
	//	}
	//	else
	//	{
	//		if (KEY_JUST_PRESSED(KEY::Z))
	//			ChangeLevel(m_Stage);

	//		else if (KEY_JUST_PRESSED(KEY::ESC))
	//			m_Stage_Title_Card->SetActive(false);
	//	}
	//}
}


