#include "pch.h"
#include "CGuidedMissile.h"
#include "CLevel.h"
#include "CLevelMgr.h"

CGuidedMissile::CGuidedMissile() :
	m_Target{},
	m_fRange(300)
{
}

CGuidedMissile::~CGuidedMissile()
{
}

void CGuidedMissile::FindTarget()
{
	if (GetLayerType() == LAYER_TYPE::PLAYER_MISSILE)
	{
		m_Target = nullptr;

		// ���͸� Ž��
		CLevel* pCurLevel = CLevelMgr::GetInstance().GetCurrentLevel();
		const vector<CObj*>& vecMonster = pCurLevel->GetObjvec(LAYER_TYPE::MONSTER);

		float fMinDist = m_fRange;

		for (const auto& monster : vecMonster)
		{
			if (monster->IsDead())
				continue;

			// �̻��ϰ� ���� ���� �Ÿ�
			float fDist = GetPos().GetDistanceWith(monster->GetPos());

			if (fDist < fMinDist)
			{
				fMinDist = fDist;
				m_Target = monster;
			}
		}
	}
}

void CGuidedMissile::tick()
{
	// ������ ����� �ִ��� ������ Ȯ��
	// Ÿ���� ���� ���ų� ���� Ÿ���� �׾������� �ٽ� Ÿ�� Ž��
  	if (!IsValid(m_Target))
	{
		FindTarget();
	}

	Vec2 vDir;

	// ����ִ� ����� ã�� ���
	if (m_Target != nullptr)
	{
		vDir = m_Target->GetPos() - GetPos();
		vDir.Normalize();

		m_fAngle = atan2f(vDir.y, vDir.x);
	}

	// ����� Ž���ߴµ��� ���� Ÿ���� ���ٸ� ���� ������ ���ư���.
	else
	{
		vDir = Vec2(cosf(m_fAngle), sinf(m_fAngle));
		vDir.Normalize();
	}

	SetPos(GetPos() + vDir * m_fSpeed * DT);
}

