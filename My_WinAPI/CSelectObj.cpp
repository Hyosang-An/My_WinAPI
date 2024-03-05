#include "pch.h"
#include "CSelectObj.h"

CSelectObj::CSelectObj(HDC _dc, HGDIOBJ _SelectedObj)
	: m_DC(_dc)
	, m_hPrev(nullptr)
{
	m_hPrev = SelectObject(m_DC, _SelectedObj);
}

CSelectObj::~CSelectObj()
{
	SelectObject(m_DC, m_hPrev);

	// DeleteObject(SelectObject(m_DC, m_hPrev)); 를 하지 않는 이유는 매개변수로 
	// 들어온 펜이나 브러쉬 객체를 지우지 않고 재사용 할 수 있도록 하기 위함이다.
}
