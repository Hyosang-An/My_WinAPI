# My_WinAPI

### 추후 추가할 사항
---

- 메세지로 마우스 클릭 처리
```cpp
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN: // 마우스 왼쪽 버튼 눌림
		{
			int xPos = LOWORD(lParam); // x 좌표
			int yPos = HIWORD(lParam); // y 좌표
			// 마우스 왼쪽 버튼이 눌린 위치 처리
			break;
		}
	case WM_LBUTTONUP: // 마우스 왼쪽 버튼 뗌
		{
			int xPos = LOWORD(lParam); // x 좌표
			int yPos = HIWORD(lParam); // y 좌표
			// 마우스 왼쪽 버튼이 떼어진 위치 처리
			break;
		}
	case WM_RBUTTONDOWN: // 마우스 오른쪽 버튼 눌림
		{
			int xPos = LOWORD(lParam); // x 좌표
			int yPos = HIWORD(lParam); // y 좌표
			// 마우스 오른쪽 버튼이 눌린 위치 처리
			break;
		}
	case WM_RBUTTONUP: // 마우스 오른쪽 버튼 뗌
		{
			int xPos = LOWORD(lParam); // x 좌표
			int yPos = HIWORD(lParam); // y 좌표
			// 마우스 오른쪽 버튼이 떼어진 위치 처리
			break;
		}
	// 다른 메시지들...
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
```
<br>

```cpp
// 마우스 이벤트 구조체
struct MouseEvent
{
    int xPos;
    int yPos;
    enum class Button
    {
        Left,
        Right
    } button;
    enum class State
    {
        Down,
        Up
    } state;
};

// 키 매니저 내 마우스 이벤트 큐
std::queue<MouseEvent> mouseEvents;

// WindowProc에서 마우스 이벤트 추가
void AddMouseEvent(MouseEvent event)
{
    mouseEvents.push(event);
}

// 매 프레임마다 마우스 이벤트 처리
void CKeyMgr::tick()
{
    while (!mouseEvents.empty())
    {
        MouseEvent event = mouseEvents.front();
        mouseEvents.pop();

        // 이벤트에 따라 적절한 처리 수행
        // 예: event.button, event.state 등을 확인하여 처리
    }
}
```
<br>

- 마우스 버튼 뗄 때 처리
```cpp
void CUIMgr::tick()
{
	// 마우스 상태 확인
	bool LBtnTap = KEY_TAP(KEY::LBTN);
	bool LBtnReleased = KEY_RELEASED(KEY::LBTN);

	// 현재 레벨에 있는 UI 들의 이벤트를 처리한다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr == pCurLevel)
		return;

	const vector<CObj*>& vecUI = pCurLevel->GetObjects(LAYER_TYPE::UI);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		//pUI = GetPriorityUI(pUI);

		// 왼쪽버튼이 눌렸고, 그게 해당 UI 안에서 라면
		if (LBtnTap && pUI->IsMouseOn())
		{
			// 왼쪽버튼 눌림 호출
			pUI->LButtonDown();
		}

		// 왼쪽 버튼이 떼졌고, 그게 해당 UI 안에서면
		else if (LBtnReleased && pUI->IsMouseOn())
		{
			// 왼쪽버틈 뗌 호출
			pUI->LButtonUp();

			// 이전에 왼쪽버튼에 눌린적이 있으면
			if (pUI->IsLbtnDowned())
			{
				// 왼쪽버튼 클릭 호출
				pUI->LButtonCliecked();
			}

			pUI->m_MouseLbtnDown = false;
		}

		else if (LBtnReleased)
		{
			pUI->m_MouseLbtnDown = false;
		}
	}
}
```
<br>

- 타일맵 사이즈 변경 시 기존 정보 유지
```cpp
void CTileMap::SetRowCol(UINT _Row, UINT _Col)
{
	// CTileMap 생성자에 m_vecTileInfo = vector<tTileInfo>(m_Row * m_Col); 추가해야됨.

	auto prev_row = m_Row;
	auto prev_col = m_Col;

	m_Row = _Row;
	m_Col = _Col;

	vector<tTileInfo> tmpVec = m_vecTileInfo;
	auto min_row = min(prev_row, _Row);
	auto min_col = min(prev_col, _Col);

	m_vecTileInfo.clear();
	m_vecTileInfo.resize((size_t)m_Row * m_Col);

	for (size_t r = 0; r < min_row; r++)
	{
		for (size_t c = 0; c < min_col; c++)
		{
			m_vecTileInfo[m_Col * r + c] = tmpVec[prev_col * r + c];
		}
	}
}
```
<br>

* 다이얼로그 창 종료 시 키 입력 초기화
```cpp
case WM_COMMAND:
	if (LOWORD(wParam) == IDOK)
	{
		// 다이얼로그 초기화 작업 메세지
		// 현재 레벨을 가져와서 에디터 레벨이 맞는지 확인
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		// 에디터 레벨에 있는  EditControl 의 정보를 가져와서, Tile Object 에 적용
		CTile* pTile = pEditorLevel->GetEditTile();

		UINT Row = 0, Col = 0;
		Row = GetDlgItemInt(hDlg, IDC_ROW, nullptr, true);
		Col = GetDlgItemInt(hDlg, IDC_COL, nullptr, true);

		pTile->SetRowCol(Row, Col);

		EndDialog(hDlg, LOWORD(wParam));
		CKeyMgr::GetInst()->tick();

		return (INT_PTR)TRUE;
	}

	else if (LOWORD(wParam) == IDCANCEL)
	{
		EndDialog(hDlg, LOWORD(wParam));
		CKeyMgr::GetInst()->tick();

		return (INT_PTR)TRUE;
	}
	break;
}
```
