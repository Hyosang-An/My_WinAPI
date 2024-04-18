#include "pch.h"
#include "CStage_Title_Card.h"


CStage_Title_Card::CStage_Title_Card()
{
	m_bActive = false;

	m_FadeTex = CCamera::GetInstance().GetFadeTexture();
	m_PanelTex = CAssetMgr::GetInstance().LoadTexture(L"Panel_Tex", L"texture\\UI\\stage cards\\Panel.png");
	m_TitleTex = nullptr;
}

CStage_Title_Card::~CStage_Title_Card()
{

}


void CStage_Title_Card::SetTitleTex(wstring _title_name)
{
	wstring relativeFolderPath = L"texture\\UI\\stage cards\\";
	wstring relativeFilePath = relativeFolderPath + _title_name + L".png";

	m_TitleTex = CAssetMgr::GetInstance().LoadTexture(_title_name, relativeFilePath);
}

void CStage_Title_Card::render()
{
	BLENDFUNCTION bf{};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = (int)(255 * 0.5);
	// m_FadeTex ·»´õ¸µ
	AlphaBlend(SUBDC, 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight()
		, m_FadeTex->GetDC(), 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight(), bf);

	// Panel°ú Å¸ÀÌÆ² ·»´õ¸µ
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;
	auto res = CEngine::GetInstance().GetResolution();
	AlphaBlend(SUBDC, res.x * 0.5f - m_PanelTex->GetWidth() * 0.5f, res.y * 0.5f - m_PanelTex->GetHeight() * 0.5f, m_PanelTex->GetWidth(), m_PanelTex->GetHeight()
		, m_PanelTex->GetDC(), 0, 0, m_PanelTex->GetWidth(), m_PanelTex->GetHeight(), bf);

	AlphaBlend(SUBDC, res.x * 0.5f - m_TitleTex->GetWidth() * 0.5f, res.y * 0.5f - m_TitleTex->GetHeight() * 0.5f, m_TitleTex->GetWidth(), m_TitleTex->GetHeight()
		, m_TitleTex->GetDC(), 0, 0, m_TitleTex->GetWidth(), m_TitleTex->GetHeight(), bf);
}
