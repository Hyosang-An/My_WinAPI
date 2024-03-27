#include "pch.h"
#include "CForce.h"
#include "CLevelMgr.h"
#include "CLevel.h"

CForce::CForce() :
	m_fForceMagnitude(0),
	m_fRange(0),
	m_fDuration(0),
	m_fElapsedTime(0)
{
}

CForce::~CForce()
{
}

void CForce::SetForce(float _force, float _range, float _duration)
{
	m_fForceMagnitude = _force;
	m_fRange = _range;
	m_fDuration = _duration;
}

void CForce::tick()
{
	//AddForce(LAYER_TYPE::MONSTER);
	AddForce(LAYER_TYPE::PLAYER);

	auto pos = GetPos();

	DrawDebugCircle(PEN_TYPE::RED, GetPos(), Vec2(m_fRange * 2.f, m_fRange * 2.f), 0);

	m_fElapsedTime += DT;

	if (m_fDuration < m_fElapsedTime)
	{
		Destroy();
	}
}

void CForce::AddForce(LAYER_TYPE _type)
{
	CLevel* pCurLevel = CLevelMgr::GetInstance().GetCurrentLevel();
	const vector<CObj*>& vecObj = pCurLevel->GetObjvec(_type);

	for (size_t i = 0; i < vecObj.size(); i++)
	{
		float fDist = GetPos().GetDistanceWith(vecObj[i]->GetPos());
		if (fDist <= m_fRange)
		{
			auto rigidbody = vecObj[i]->GetComponent<CRigidbody>();
			if (rigidbody == nullptr)
				continue;

			float fRatio = 1 - (fDist / m_fRange);

			Vec2 force_dir = vecObj[i]->GetPos() - GetPos();
			if (!force_dir.IsZero())
			{
				Vec2 force = force_dir.Normalize() * m_fForceMagnitude * fRatio;
				rigidbody->AddForce(force);
			}

		}
	}
}