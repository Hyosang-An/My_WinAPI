#pragma once

#define USE_PEN(_DC, _PEN_TYPE) CSelectObj SelectPen(_DC, CEngine::GetInstance().GetPen(_PEN_TYPE))
#define USE_BRUSH(_DC, _BRUSH_TYPE) CSelectObj SelectBrush(_DC, CEngine::GetInstance().GetBrush(_BRUSH_TYPE))

#define DT CTimeMgr::GetInstance().GetDeltaTime()
#define SUBDC CEngine::GetInstance().GetSubDC()

#define CLONE(type)	virtual type* Clone() override { return new type(*this); };
#define CLONE_DISABLE(type) virtual type* Clone() override { return nullptr; };

#define PI 3.1415926535f

#define LOG(_LOG_TYPE, _Msg)	{\
									string FuncName = __FUNCTION__;\
									wstring strFuncName(FuncName.begin(), FuncName.end());\
									wchar_t szLog[256]{};\
									swprintf_s(szLog, L"{%s : %d) : %s", strFuncName.c_str(), __LINE__, _Msg);\
									tDbgLog DbgLog{};\
									DbgLog.Type = _LOG_TYPE;\
									DbgLog.strLog = szLog;\
									CDbgRenderer::GetInstance().AddDbgLog(DbgLog);\
								}