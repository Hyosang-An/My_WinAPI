#include "pch.h"
#include "CBackground.h"
#include "CCamera.h"

CBackground::CBackground() :
	m_Texture{}
{
}

CBackground::~CBackground()
{
}


void CBackground::SetAnimation(const wstring& strRelativeAnimFilePath, bool _RepeatReverse)
{
	// _RepeatReverse �⺻���� false

	if (m_Animator == nullptr)
		m_Animator = AddComponent(new CAnimator);
	
	m_Animator->Play(m_Animator->LoadAnimation(strRelativeAnimFilePath)->GetName(), true, _RepeatReverse);
}
	

void CBackground::begin()
{
	
}

void CBackground::tick()
{
	auto CameraDeltaPos = CCamera::GetInstance().GetCameraDeltaPos();

	switch (m_Depth)
	{
		case BACKGROUND_DEPTH::Fore:
			break;
		case BACKGROUND_DEPTH::Middle:
		{
			SetPos(GetPos() + 0.5*CameraDeltaPos);
			break;
		}
		case BACKGROUND_DEPTH::Far:
		{
			SetPos(GetPos() + CameraDeltaPos);
			break;
		}
		default:
			break;
	}
}

void CBackground::render()
{
	if (m_Texture == nullptr && m_Animator != nullptr)
	{
		m_Animator->render();
		return;
	}

	// !�����
	if (GetName() == L"Burst_Dust1")
	{
		int a = 0;
	}

	// ������Ʈ ��ġ
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();

	int Texture_width = m_Texture->GetWidth();
	int Texture_height = m_Texture->GetHeight();

	// AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	// ���� ������ �̹����� ������Ʈ ��ġ�� ������
	AlphaBlend(SUBDC,
		(int)(vRenderPos.x - Texture_width / 2.f), (int)(vRenderPos.y - Texture_height / 2.f), Texture_width, Texture_height,
		m_Texture->GetDC(), 0, 0, Texture_width, Texture_height,
		bf);
}
