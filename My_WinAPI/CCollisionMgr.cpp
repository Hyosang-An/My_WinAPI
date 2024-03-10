#include "pch.h"
#include "CCollisionMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::init()
{
}

void CCollisionMgr::tick()
{
	for (UINT iRow = 0; iRow < (UINT)LAYER_TYPE::END; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)LAYER_TYPE::END; iCol++)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionCheck((LAYER_TYPE)iRow, (LAYER_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionCheck(LAYER_TYPE _leftLayer, LAYER_TYPE _rightLayer)
{
	// �� ���� ���� left Layer
	auto pCurLevel = CLevelMgr::GetInstance().GetCurrentLevel();
	const auto &leftVec = pCurLevel->GetObjvec(_leftLayer);
	const auto &rightVec = pCurLevel->GetObjvec(_rightLayer);

	for (size_t i = 0; i < leftVec.size(); i++)
	{
		if (leftVec[i]->GetCollider() == nullptr)
			continue;
			
		for (size_t j = 0; j < rightVec.size(); j++)
		{
			if (rightVec[j]->GetCollider() == nullptr || leftVec == rightVec)
				continue;

			if (IsObjCollision(leftVec[i]->GetCollider(), rightVec[i]->GetCollider()))
			{

			}
			else
			{

			}
		}
	}
}

bool CCollisionMgr::IsObjCollision(CCollider* _pLeftCollider, CCollider* _pRightCollider)
{


	return false;
}

void CCollisionMgr::EnableLayerCollisionCheck(LAYER_TYPE _leftLayer, LAYER_TYPE _rightLayer)
{
	// �� ���� ���� �׷� Ÿ���� ������,
	// �� ū ���� ��(��Ʈ)�� ���

	UINT iRow = (UINT)_leftLayer;
	UINT iCol = (UINT)_rightLayer;

	if (iCol < iRow)
	{
		UINT iCol = (UINT)_leftLayer;
		UINT iRow = (UINT)_rightLayer;
	}


	m_arrCheck[iRow] |= (1 << iCol);
}

void CCollisionMgr::DisableLayerCollisionCheck(LAYER_TYPE _leftLayer, LAYER_TYPE _rightLayer)
{
	// �� ���� ���� �׷� Ÿ���� ������,
	// �� ū ���� ��(��Ʈ)�� ���

	UINT iRow = (UINT)_leftLayer;
	UINT iCol = (UINT)_rightLayer;

	if (iCol < iRow)
	{
		UINT iCol = (UINT)_leftLayer;
		UINT iRow = (UINT)_rightLayer;
	}

	m_arrCheck[iRow] &= ~(1 << iCol);
}

void CCollisionMgr::CollisionCheckReset()
{
	memset(m_arrCheck, 0, sizeof(m_arrCheck));
}
