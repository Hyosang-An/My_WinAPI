#include "pch.h"
#include "CBackground.h"

CBackground::CBackground() :
	m_Texture{}
{
}

CBackground::~CBackground()
{
}


void CBackground::render()
{
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
