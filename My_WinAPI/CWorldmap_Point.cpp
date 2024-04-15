#include "pch.h"
#include "CWorldmap_Point.h"

#include "CKeyMgr.h"

CWorldmap_Point::CWorldmap_Point() :
	m_Stage{}
{
	m_Animator = AddComponent(new CAnimator);

	m_Worldmap_Point_Collider = AddComponent(new CCollider);
	m_Worldmap_Point_Collider->SetScale(Vec2(150, 150));
}

CWorldmap_Point::~CWorldmap_Point()
{
}

void CWorldmap_Point::SetAnimation(const wstring& _strRelativeAnimFilePath)
{
	;
	m_Animator->Play(m_Animator->LoadAnimation(_strRelativeAnimFilePath)->GetName(), true);
}

void CWorldmap_Point::SetColliderOffset(Vec2 _vec)
{
	m_Worldmap_Point_Collider->SetOffsetPos(_vec);
}

void CWorldmap_Point::OnCollisionStay(CCollider* _myCollider, CCollider* _pOtherCollider)
{
	if (_pOtherCollider->GetOwner()->GetLayerType() == LAYER_TYPE::WORLDMAP_PLAYER)
	{
		if (KEY_JUST_PRESSED(KEY::Z))
		{
			ChangeLevel(m_Stage);
		}
	}
}


