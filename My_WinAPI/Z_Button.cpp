#include "pch.h"
#include "Z_Button.h"

Z_Button::Z_Button() :
	m_WorldmapPlayer{}
{
	m_bActive = false;
	m_ButtonTex = CAssetMgr::GetInstance().LoadTexture(L"Z_Button_Tex", L"texture\\UI\\Z Button.png");
}

Z_Button::~Z_Button()
{
}

void Z_Button::render()
{
	auto realPos = m_WorldmapPlayer->GetPos() + Vec2(0, -80);
	auto renderPos = CCamera::GetInstance().GetRenderPos(realPos);

	BLENDFUNCTION bf{};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	// 렌더링 배율 및 width, height
	float magnification = 0.4f;
	auto w = m_ButtonTex->GetWidth() * magnification;
	auto h = m_ButtonTex->GetHeight() * magnification;


	AlphaBlend(SUBDC, renderPos.x - w * 0.5f, renderPos.y - h * 0.5f, w, h
		, m_ButtonTex->GetDC(), 0, 0, m_ButtonTex->GetWidth(), m_ButtonTex->GetHeight(), bf);
}