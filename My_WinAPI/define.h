#pragma once

#define USE_PEN(_DC, _PEN_TYPE) CSelectObj SelectPen(_DC, CEngine::GetInstance().GetPen(_PEN_TYPE))
#define USE_BRUSH(_DC, _BRUSH_TYPE) CSelectObj SelectBrush(_DC, CEngine::GetInstance().GetBrush(_BRUSH_TYPE))

#define DT CTimeMgr::GetInstance().GetDeltaTime()
#define SUBDC CEngine::GetInstance().GetSubDC()

//#define KEY_CHECK(_key, _state)	CKeyMgr::GetInstance().GetKeyState(_key) == _state
//
//#define KEY_JUST_PRESSED(_key)	KEY_CHECK(_key, KEY_STATE::JUST_PRESSED)
//#define KEY_PRESSED(_key)		KEY_CHECK(_key, KEY_STATE::PRESSED)
//#define KEY_RELEASED(_key)		KEY_CHECK(_key, KEY_STATE::RELEASED)
//#define KEY_NONE(_key)			KEY_CHECK(_key, KEY_STATE::NONE)
