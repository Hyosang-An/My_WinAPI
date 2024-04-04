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
	// 오브젝트 위치
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

	// 현재 프레임 이미지를 오브젝트 위치에 렌더링
	AlphaBlend(SUBDC,
		(int)(vRenderPos.x - Texture_width / 2.f), (int)(vRenderPos.y - Texture_height / 2.f), Texture_width, Texture_height,
		m_Texture->GetDC(), 0, 0, Texture_width, Texture_height,
		bf);
}
