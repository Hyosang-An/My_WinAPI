#include "pch.h"
#include "CEffect.h"

CEffect::CEffect() :
	m_ParentObj{}
{
	m_Animator = AddComponent(new CAnimator);
}

CEffect::CEffect(const CEffect& _other) :
	CObj(_other),
	m_ParentObj(_other.m_ParentObj),
	m_OffsetPos(_other.m_OffsetPos),
	m_AnimName(_other.m_AnimName),
	m_bRepeat(_other.m_bRepeat)
{
}

CEffect::~CEffect()
{
}

void CEffect::SetAnimation(const wstring& _strRelativeAnimFilePath, bool _repeat)
{
	// repeat은 기본적으로 false
	auto anim = m_Animator->LoadAnimation(_strRelativeAnimFilePath);
	m_AnimName = anim->GetName();
	m_bRepeat = _repeat;
}

void CEffect::SetParentAndOffset(CObj* _parent, Vec2 _offset)
{
	m_ParentObj = _parent;
	m_OffsetPos = _offset;
}

void CEffect::PlayEffect()
{
	m_Animator->Play(m_AnimName, m_bRepeat);
}

void CEffect::tick()
{
	if (m_ParentObj)
		m_Pos = m_ParentObj->GetPos() + m_OffsetPos;

	if (m_Animator->IsCurAnimationFinished() && !m_bRepeat)
		SelfDestruct();
}