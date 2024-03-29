#include "pch.h"
#include "CDbgRenderer.h"
#include "CKeyMgr.h"
#include "CEngine.h"
#include "CTimeMgr.h"

CDbgRenderer::CDbgRenderer() :
	m_bRender(true),
	m_LogDuration(2),
	m_LogSpace(18),
	m_LogPos(Vec2(10, 10))
{
}

CDbgRenderer::~CDbgRenderer()
{
}

void CDbgRenderer::tick()
{
#ifdef _DEBUG
	if (KEY_JUST_PRESSED(KEY::_0))
	{
		m_bRender = !m_bRender;
	}
#endif // _DEBUG
}

void CDbgRenderer::render()
{
#ifdef _DEBUG

	if (m_bRender == false)
		return;

	// RenderList 출력
	auto iter_RenderList = m_RenderList.begin();

	for (; iter_RenderList != m_RenderList.end(); )
	{
		USE_BRUSH(SUBDC, BRUSH_TYPE::HOLLOW);
		USE_PEN(SUBDC, iter_RenderList->Color);

		switch (iter_RenderList->Shape)
		{
			case DBG_SHAPE::RECT:
			{
				Rectangle(SUBDC
					, (int)(iter_RenderList->Position.x - iter_RenderList->Scale.x / 2.f)
					, (int)(iter_RenderList->Position.y - iter_RenderList->Scale.y / 2.f)
					, (int)(iter_RenderList->Position.x + iter_RenderList->Scale.x / 2.f)
					, (int)(iter_RenderList->Position.y + iter_RenderList->Scale.y / 2.f));
				break;
			}

			case DBG_SHAPE::CIRCLE:
			{
				Ellipse(SUBDC
					, (int)(iter_RenderList->Position.x - iter_RenderList->Scale.x / 2.f)
					, (int)(iter_RenderList->Position.y - iter_RenderList->Scale.y / 2.f)
					, (int)(iter_RenderList->Position.x + iter_RenderList->Scale.x / 2.f)
					, (int)(iter_RenderList->Position.y + iter_RenderList->Scale.y / 2.f));

				break;
			}
			default:
				break;
		}


		// 해당 디버그렌더 정보가 수명을 다하면 리스트에서 제거한다.
		(*iter_RenderList).fElapsedTime += DT;
		if (iter_RenderList->fDuration < iter_RenderList->fElapsedTime)
		{
			iter_RenderList = m_RenderList.erase(iter_RenderList);
		}
		else
		{
			++iter_RenderList;
		}
	}

	// LogList 출력
	auto iter_LogList = m_LogList.begin();

	SetBkMode(SUBDC, TRANSPARENT);

	int i = 0;
	for (; iter_LogList != m_LogList.end();)
	{
		int yoffset = ((int)m_LogList.size() - i + 1) * m_LogSpace;

		switch (iter_LogList->Type)
		{
			case LOG_TYPE::DBG_LOG:
			{
				SetTextColor(SUBDC, RGB(255, 255, 255));
				break;
			}

			case LOG_TYPE::DBG_WARNING:
			{
				SetTextColor(SUBDC, RGB(240, 240, 20));
				break;
			}

			case LOG_TYPE::DBG_ERROR:
			{
				SetTextColor(SUBDC, RGB(240, 20, 20));
				break;
			}
		}

		TextOut(SUBDC, (int)m_LogPos.x, (int)m_LogPos.y + yoffset,
			iter_LogList->strLog.c_str(), (int)iter_LogList->strLog.length());

		iter_LogList->fElapsedTime += DT;

		if (m_LogDuration <= iter_LogList->fElapsedTime)
			iter_LogList = m_LogList.erase(iter_LogList);
		else
			++iter_LogList;

		i++;
	}

	SetBkMode(SUBDC, OPAQUE);
	SetTextColor(SUBDC, RGB(0, 0, 0));

#endif // _DEBUG
}

