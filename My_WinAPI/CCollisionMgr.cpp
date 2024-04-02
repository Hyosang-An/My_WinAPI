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
	const auto& leftObjVec = pCurLevel->GetObjvecOfLayer(_leftLayer);
	const auto& rightObjVec = pCurLevel->GetObjvecOfLayer(_rightLayer);

	auto iter = m_mapCollisionInfo.begin();

	for (size_t i = 0; i < leftObjVec.size(); i++)
	{
		/*if (leftObjVec[i]->GetCollider() == nullptr)
			continue;*/

		for (size_t j = 0; j < rightObjVec.size(); j++)
		{
			/*if (rightObjVec[j]->GetCollider() == nullptr || leftObjVec == rightObjVec)
				continue;*/

			if (leftObjVec[i] == rightObjVec[j])
				continue;

			auto& leftColliderVec = leftObjVec[i]->GetVecCollider();
			auto& rightColliderVec = rightObjVec[j]->GetVecCollider();

			for (auto& leftCollider : leftColliderVec)
			{
				if (leftCollider == nullptr)
					continue;

				for (auto& rightCollider : rightColliderVec)
				{
					if (rightCollider == nullptr)
						continue;

					// 두 충돌체 조합 ID 생성
					COLLIDER_ID ID{};
					ID.LeftID = leftCollider->GetID();
					ID.RightID = rightCollider->GetID();

					iter = m_mapCollisionInfo.find(ID.ID);

					if (iter == m_mapCollisionInfo.end())
					{
						auto result = m_mapCollisionInfo.insert(make_pair(ID.ID, false));
						iter = result.first;
					}

					if (IsCollision(leftCollider, rightCollider))
					{
						// 현재 충돌 중이다.

						// 두 충돌체 모두 Active한 경우
						if (leftCollider->IsActive() && rightCollider->IsActive())
						{
							if (iter->second)
							{
								// 이전에도 충돌중이다.-> 충돌 유지
								leftCollider->OnCollisionStay(rightCollider);
								rightCollider->OnCollisionStay(leftCollider);
							}
							else
							{
								// 이전에는 충돌 중이 아니었다. -> 충돌 시작
								leftCollider->OnCollisionEnter(rightCollider);
								rightCollider->OnCollisionEnter(leftCollider);

								iter->second = true;
							}
						}

						// 두 충돌체 중 한개가 Active하지 않게 되었는데, 이전에 충돌 중인 경우
						else if (iter->second)
						{
							// 충돌 종료
							leftCollider->OnCollisionExit(rightCollider);
							rightCollider->OnCollisionExit(leftCollider);

							iter->second = false;
						}
					}
					else
					{
						// 현재 충돌 중이 아니다.

						if (iter->second)
						{
							// 이전에는 충돌 중이다. -> 충돌 종료
							leftCollider->OnCollisionExit(rightCollider);
							rightCollider->OnCollisionExit(leftCollider);

							iter->second = false;
						}
					}
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
		iCol = (UINT)_leftLayer;
		iRow = (UINT)_rightLayer;
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
