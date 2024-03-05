#pragma once

#define USE_PEN(_DC, _PEN_TYPE) CSelectObj SelectPen(_DC, CEngine::GetInstance().GetPen(_PEN_TYPE))