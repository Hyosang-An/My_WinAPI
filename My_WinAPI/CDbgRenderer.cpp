#include "pch.h"
#include "CDbgRenderer.h"
#include "CKeyMgr.h"
#include "CEngine.h"
#include "CTimeMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"

CDbgRenderer::CDbgRenderer() :
	m_bDBGMode(false),
	m_LogDuration(2),
	m_LogSpace(18),
	m_LogPos(Vec2(10, 10))
{
}

CDbgRenderer::~CDbgRenderer()
{
}

void CDbgRenderer::AddDbgRenderInfo(const tDbgRenderInfo& _info)
{
	m_RenderList.push_back(_info);
}

void CDbgRenderer::AddDbgLog(const tDbgLog _tDbgLog)
{
	m_LogList.push_back(_tDbgLog);
	if (m_LogList.size() > 10)
		m_LogList.pop_front();
}

void CDbgRenderer::tick()
{
#ifdef _DEBUG
	if (KEY_JUST_PRESSED(KEY::_0))
	{
		m_bDBGMode = !m_bDBGMode;
	}
#endif // _DEBUG
}

void CDbgRenderer::render()
{
#ifdef _DEBUG

	if (m_bDBGMode == false)
		return;

	// RenderList 출력
	auto iter_RenderList = m_RenderList.begin();

	for (; iter_RenderList != m_RenderList.end(); )
	{
		USE_BRUSH(SUBDC, BRUSH_TYPE::HOLLOW);
		USE_PEN(SUBDC, iter_RenderList->Color);

		// 렌더링 포지션으로 전환
		iter_RenderList->Position = CCamera::GetInstance().GetRenderPos(iter_RenderList->Position);

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

			case DBG_SHAPE::LINE:
			{
				MoveToEx(SUBDC, (int)(iter_RenderList->Position.x), (int)(iter_RenderList->Position.y), nullptr);

				iter_RenderList->Scale = CCamera::GetInstance().GetRenderPos(iter_RenderList->Scale);

				LineTo(SUBDC, (int)iter_RenderList->Scale.x, (int)iter_RenderList->Scale.y);
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

	// 마우스 좌표 출력
	Vec2 mousePos = CKeyMgr::GetInstance().GetMousePos();
	mousePos = CCamera::GetInstance().GetRealPos(mousePos);
	wstring strMousePos = std::to_wstring((int)mousePos.x) + L", " + std::to_wstring((int)mousePos.y);
	TextOut(SUBDC, (int)(CEngine::GetInstance().GetResolution().x * 0.5f) - 50, 5,
		strMousePos.c_str(), (int)strMousePos.length());

	// 오브젝트 좌표 출력
	if (CLevelMgr::GetInstance().GetCurrentLevel() == nullptr)
		return;
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; i++)
	{
		const auto &ObjvecLayer = CLevelMgr::GetInstance().GetCurrentLevel()->GetObjvecOfLayer((LAYER_TYPE)i);

		for (auto obj : ObjvecLayer)
		{
			auto objpos = obj->GetPos();
			wstring strObjPos = std::to_wstring((int)objpos.x) + L", " + std::to_wstring((int)objpos.y);
			TextOut(SUBDC, (int)obj->GetRenderPos().x, (int)obj->GetRenderPos().y,
				strObjPos.c_str(), (int)strObjPos.length());
		}
	}


	// 충돌체 렌더링
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; i++)
	{
		// !디버깅
		if ((LAYER_TYPE)i == LAYER_TYPE::PLAYER)
		{
			int a = 0;
		}

		const auto& ObjvecLayer = CLevelMgr::GetInstance().GetCurrentLevel()->GetObjvecOfLayer((LAYER_TYPE)i);

		for (auto obj : ObjvecLayer)
		{
			const auto& vecCollider = obj->GetVecCollider();

			for (auto collider : vecCollider)
			{
				if (!collider->IsActive())
					continue;

				if (collider->IsCollision())
				{
					USE_BRUSH(SUBDC, BRUSH_TYPE::HOLLOW);
					USE_PEN(SUBDC, PEN_TYPE::RED);

					auto colliderPos = collider->GetFinalPos();
					auto colliderRenderPos = CCamera::GetInstance().GetRenderPos(colliderPos);
					auto colliderScale = collider->GetScale();

					Rectangle(SUBDC
						, (int)(colliderRenderPos.x - colliderScale.x / 2.f)
						, (int)(colliderRenderPos.y - colliderScale.y / 2.f)
						, (int)(colliderRenderPos.x + colliderScale.x / 2.f)
						, (int)(colliderRenderPos.y + colliderScale.y / 2.f));
				}
				else
				{
					USE_BRUSH(SUBDC, BRUSH_TYPE::HOLLOW);
					USE_PEN(SUBDC, PEN_TYPE::GREEN);

					auto colliderPos = collider->GetFinalPos();
					auto colliderRenderPos = CCamera::GetInstance().GetRenderPos(colliderPos);
					auto colliderScale = collider->GetScale();

					Rectangle(SUBDC
						, (int)(colliderRenderPos.x - colliderScale.x / 2.f)
						, (int)(colliderRenderPos.y - colliderScale.y / 2.f)
						, (int)(colliderRenderPos.x + colliderScale.x / 2.f)
						, (int)(colliderRenderPos.y + colliderScale.y / 2.f));
				}
				
			}			
		}
	}

#endif // _DEBUG
}

