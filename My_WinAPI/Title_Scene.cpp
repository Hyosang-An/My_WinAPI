#include "pch.h"
#include "Title_Scene.h"


Title_Scene::Title_Scene()
{
	m_TitleBG = CAssetMgr::GetInstance().LoadTexture(L"title_screen_background", L"texture\\Title Scene\\Background\\title_screen_background.png");

	for (int i = 1; i <= 34; i++)
	{
		wstring strpath = L"texture\\Title Scene\\Cuphead and Mugman\\";
		wstring filename = L"cuphead_title_screen_";
		wstring num = std::to_wstring(i);
		num = std::wstring(4 - num.length(), L'0') + num;

		m_vecTitleAnim.push_back(CAssetMgr::GetInstance().LoadTexture(filename + num, strpath + filename + num + L".png"));
	}
}

Title_Scene::~Title_Scene()
{
}

void Title_Scene::Enter()
{
}

void Title_Scene::tick()
{
	if (KEY_JUST_PRESSED(KEY::Z) || KEY_JUST_PRESSED(KEY::ENTER))
		ChangeLevel(LEVEL_TYPE::WORLD_MAP);
}

void Title_Scene::render()
{
	BLENDFUNCTION bf{};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	auto res = CEngine::GetInstance().GetResolution();

	// 배경 렌더링

	AlphaBlend(SUBDC, 0, 0, (int)res.x, (int)res.y
		, m_TitleBG->GetDC(), 0, 0, m_TitleBG->GetWidth(), m_TitleBG->GetHeight(), bf);

	// 애니매이션 렌더링

	m_TitleAnimframeElapsedTime += DT;

	if (m_TitleAnimframeDuration < m_TitleAnimframeElapsedTime)
	{
		m_TitleAnimframeElapsedTime -= m_TitleAnimframeDuration;

		// 프레임이 마지막에 도달한 경우
		if (m_CurTitleAnimFrameIdx >= m_vecTitleAnim.size() - 1)
		{
			m_CurTitleAnimFrameIdx = 0;
		}
		else
			m_CurTitleAnimFrameIdx++;
	}



	auto curFrame = m_vecTitleAnim[m_CurTitleAnimFrameIdx];
	auto w = curFrame->GetWidth();
	auto h = curFrame->GetHeight();

	AlphaBlend(SUBDC, res.x / 2 - w / 2, res.y - h, w, h,
		curFrame->GetDC(), 0, 0, w, h, bf);

}

void Title_Scene::Exit()
{
	DeleteAllObjects();
}

