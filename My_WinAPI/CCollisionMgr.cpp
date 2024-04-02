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

					// �� �浹ü ���� ID ����
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
						// ���� �浹 ���̴�.

						// �� �浹ü ��� Active�� ���
						if (leftCollider->IsActive() && rightCollider->IsActive())
						{
							if (iter->second)
							{
								// �������� �浹���̴�.-> �浹 ����
								leftCollider->OnCollisionStay(rightCollider);
								rightCollider->OnCollisionStay(leftCollider);
							}
							else
							{
								// �������� �浹 ���� �ƴϾ���. -> �浹 ����
								leftCollider->OnCollisionEnter(rightCollider);
								rightCollider->OnCollisionEnter(leftCollider);

								iter->second = true;
							}
						}

						// �� �浹ü �� �Ѱ��� Active���� �ʰ� �Ǿ��µ�, ������ �浹 ���� ���
						else if (iter->second)
						{
							// �浹 ����
							leftCollider->OnCollisionExit(rightCollider);
							rightCollider->OnCollisionExit(leftCollider);

							iter->second = false;
						}
					}
					else
					{
						// ���� �浹 ���� �ƴϴ�.

						if (iter->second)
						{
							// �������� �浹 ���̴�. -> �浹 ����
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
	// �� ���� ���� �׷� Ÿ���� ������,
	// �� ū ���� ��(��Ʈ)�� ���

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
