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
	// 더 작은 값이 left Layer
	auto pCurLevel = CLevelMgr::GetInstance().GetCurrentLevel();
	const auto& leftObjVec = pCurLevel->GetObjvec(_leftLayer);
	const auto& rightObjVec = pCurLevel->GetObjvec(_rightLayer);

	auto iter = m_mapCollisionInfo.begin();

	for (size_t i = 0; i < leftObjVec.size(); i++)
	{
		if (leftObjVec[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < rightObjVec.size(); j++)
		{
			if (rightObjVec[j]->GetCollider() == nullptr || leftObjVec == rightObjVec)
				continue;

			// 두 오브젝트 조합 ID 생성
			COLLIDER_ID ID{};
			ID.LeftID = leftObjVec[i]->GetID();
			ID.RightID = rightObjVec[j]->GetID();

			iter = m_mapCollisionInfo.find(ID.ID);

			if (iter == m_mapCollisionInfo.end())
			{
				auto result = m_mapCollisionInfo.insert(make_pair(ID.ID, false));
				iter = result.first;
			}

			auto pLeftCollider = leftObjVec[i]->GetCollider();
			auto pRightCollider = rightObjVec[j]->GetCollider();

			if (IsCollision(pLeftCollider, pRightCollider))
			{
				// 현재 충돌 중이다.

				if (iter->second)
				{
					// 이전에도 충돌중이다.
					pLeftCollider->OnCollisionStay(pRightCollider);
					pRightCollider->OnCollisionStay(pLeftCollider);
				}
				else
				{
					// 이전에는 충돌 중이 아니었다.
					pLeftCollider->OnCollisionEnter(pRightCollider);
					pRightCollider->OnCollisionEnter(pLeftCollider);

					iter->second = true;
				}
			}
			else
			{
				// 현재 충돌 중이 아니다.

				if (iter->second)
				{
					// 이전에는 충돌 중이다.
					pLeftCollider->OnCollisionExit(pRightCollider);
					pRightCollider->OnCollisionExit(pLeftCollider);

					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCollider, CCollider* _pRightCollider)
{
	Vec2 vLeftPos = _pLeftCollider->GetFinalPos();
	Vec2 vLeftScale = _pLeftCollider->GetScale();
	Vec2 vRightPos = _pRightCollider->GetFinalPos();
	Vec2 vRightScale = _pRightCollider->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) <= (abs(vLeftScale.x + vRightScale.x) * 0.5f) &&
		abs(vRightPos.y - vLeftPos.y) <= (abs(vLeftScale.y + vRightScale.y) * 0.5f))
	{
		return true;
	}
	return false;
}

void CCollisionMgr::EnableLayerCollisionCheck(LAYER_TYPE _leftLayer, LAYER_TYPE _rightLayer)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 더 큰 값을 열(비트)로 사용

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
	// 더 작은 값의 그룹 타입을 행으로,
	// 더 큰 값을 열(비트)로 사용

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
