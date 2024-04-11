#include "pch.h"
#include "CEffect.h"

CEffect::CEffect() :
	m_ParentObj{}
{
	m_Animator = AddComponent(new CAnimator);
}

CEffect::CEffect(const CEffect& _other) :
	m_ParentObj(_other.m_ParentObj)
{
}

CEffect::~CEffect()
{
}

void CEffect::SetAnimation(const wstring& _strRelativeAnimFilePath)
{
	m_Animator->LoadAnimation(_strRelativeAnimFilePath);
	
}

void CEffect::SetParentAndOffset(CObj* _parent, Vec2 _offset)
{
	m_ParentObj = _parent;
	m_OffsetPos = _offset;
}

void CEffect::PlayEffect()
{
	auto anim_name = m_Animator->get
	m_Animator->Play()
}

void CEffect::tick()
{
	if (m_ParentObj)
		m_Pos = m_ParentObj->GetPos() + m_OffsetPos;

	if (m_Animator->IsCurAnimationFinished())
		SelfDestruct();
}