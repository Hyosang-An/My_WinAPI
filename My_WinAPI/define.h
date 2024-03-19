#pragma once

#define USE_PEN(_DC, _PEN_TYPE) CSelectObj SelectPen(_DC, CEngine::GetInstance().GetPen(_PEN_TYPE))
#define USE_BRUSH(_DC, _BRUSH_TYPE) CSelectObj SelectBrush(_DC, CEngine::GetInstance().GetBrush(_BRUSH_TYPE))

#define DT CTimeMgr::GetInstance().GetDeltaTime()
#define SUBDC CEngine::GetInstance().GetSubDC()

#define CLONE(type)	virtual type* Clone() override { return new type(*this); };
#define CLONE_DISABLE(type) virtual type* Clone() override { return nullptr; };