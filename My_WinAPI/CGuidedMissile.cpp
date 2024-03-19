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

		// 몬스터를 탐색
		CLevel* pCurLevel = CLevelMgr::GetInstance().GetCurrentLevel();
		const vector<CObj*>& vecMonster = pCurLevel->GetObjvec(LAYER_TYPE::MONSTER);

		float fMinDist = m_fRange;

		for (const auto& monster : vecMonster)
		{
			if (monster->IsDead())
				continue;

			// 미사일과 몬스터 간의 거리
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
	// 추적할 대상이 있는지 없는지 확인
	// 타겟이 현재 없거나 현재 타겟이 죽어있으면 다시 타겟 탐색
  	if (!IsValid(m_Target))
	{
		FindTarget();
	}

	Vec2 vDir;

	// 살아있는 대상을 찾은 경우
	if (m_Target != nullptr)
	{
		vDir = m_Target->GetPos() - GetPos();
		vDir.Normalize();

		m_fAngle = atan2f(vDir.y, vDir.x);
	}

	// 대상을 탐색했는데도 아직 타겟이 없다면 원래 방향대로 날아간다.
	else
	{
		vDir = Vec2(cosf(m_fAngle), sinf(m_fAngle));
		vDir.Normalize();
	}

	SetPos(GetPos() + vDir * m_fSpeed * DT);
}

