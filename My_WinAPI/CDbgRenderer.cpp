#include "pch.h"
#include "CDbgRenderer.h"
#include "CKeyMgr.h"
#include "CEngine.h"
#include "CTimeMgr.h"

CDbgRenderer::CDbgRenderer()
	: m_bRender(true)
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
	auto iter = m_RenderList.begin();

	for (; iter != m_RenderList.end(); )
	{
		if (m_bRender)
		{
			USE_BRUSH(SUBDC, BRUSH_TYPE::HOLLOW);
			USE_PEN(SUBDC, iter->Color);

			switch (iter->Shape)
			{
			case DBG_SHAPE::RECT:
			{
				Rectangle(SUBDC
					, (int)(iter->Position.x - iter->Scale.x / 2.f)
					, (int)(iter->Position.y - iter->Scale.y / 2.f)
					, (int)(iter->Position.x + iter->Scale.x / 2.f)
					, (int)(iter->Position.y + iter->Scale.y / 2.f));
				break;
			}

			case DBG_SHAPE::CIRCLE:
			{
				Ellipse(SUBDC
					, (int)(iter->Position.x - iter->Scale.x / 2.f)
					, (int)(iter->Position.y - iter->Scale.y / 2.f)
					, (int)(iter->Position.x + iter->Scale.x / 2.f)
					, (int)(iter->Position.y + iter->Scale.y / 2.f));

				break;
			}
			default:
				break;
			}
		}

		// 해당 디버그렌더 정보가 수명을 다하면 리스트에서 제거한다.
		(*iter).Age += DT;
		if (iter->Duration < iter->Age)
		{
			iter = m_RenderList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
#endif // _DEBUG
}

