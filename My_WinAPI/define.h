#pragma once

#define USE_PEN(_DC, _PEN_TYPE) CSelectObj SelectPen(_DC, CEngine::GetInstance().GetPen(_PEN_TYPE))
#define USE_BRUSH(_DC, _BRUSH_TYPE) CSelectObj SelectBrush(_DC, CEngine::GetInstance().GetBrush(_BRUSH_TYPE))

#define DT CTimeMgr::GetInstance().GetDeltaTime()
#define SUBDC CEngine::GetInstance().GetSubDC()