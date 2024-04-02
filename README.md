# My_WinAPI

!디버깅 붙어있는 코드는 디버깅 용도

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
<br>

* 게임에서 순간적으로 잠깐 멈추는 효과를 주기 위해서는 `CTimeMgr`의 동작 방식을 조금 조정해야 합니다. 일반적으로 게임은 매 프레임마다 시간 간격(`DeltaTime`)을 계산하여 이를 바탕으로 게임 내 오브젝트들의 이동이나 애니메이션 등의 업데이트를 진행합니다. 여기서 멈칫하는 효과를 주기 위해선, 일정 시간 동안 `DeltaTime`을 0 또는 매우 작은 값으로 고정하여, 그 기간 동안 게임의 상태가 업데이트 되지 않게 만들면 됩니다.

 	이를 위한 가장 간단한 방법은 `CTimeMgr` 클래스에 멈춤 효과를 위한 멤버 변수와 함수를 추가하는 것입니다. 예를 들어, 멈춤 효과의 지속 시간을 관리할 변수와, 멈춤 효과를 시작하는 함수, 그리고 멈춤 효과의 상태를 확인하는 함수를 추가할 수 있습니다.

	다음은 이러한 기능을 `CTimeMgr` 클래스에 추가하는 방법을 보여줍니다.

 1. 멈춤 효과 관련 멤버 변수 추가:

```cpp
private:
    float m_FreezeDuration;   // 멈춤 효과의 지속 시간
    float m_FreezeTimer;      // 현재 멈춤 효과의 타이머, 0보다 클 때 멈춤 효과가 활성화된 것으로 간주
```

 2. 멈춤 효과를 시작하는 함수 추가:

```cpp
public:
    // 멈춤 효과 시작 함수, 지속 시간을 매개변수로 받음
    void StartFreezeEffect(float duration) {
        m_FreezeDuration = duration;
        m_FreezeTimer = duration;
    }
```

 3. `tick` 함수 내에서 멈춤 효과 로직 추가:

```cpp
void CTimeMgr::tick()
{
    // 현재 카운트 계산
    QueryPerformanceCounter(&m_llCurCount);

    if (m_FreezeTimer > 0) {
        // 멈춤 효과가 활성화된 경우, DeltaTime을 0으로 설정하고 타이머 감소
        m_DeltaTime = 0;
        m_FreezeTimer -= (float(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart);
    } else {
        // 멈춤 효과가 비활성화된 경우, 정상적인 DeltaTime 계산
        m_DeltaTime = (float(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart);

        // 디버깅 할 때 DT최솟값 보정
        #ifdef _DEBUG
        if (m_DeltaTime > (1.f / 60.f))
            m_DeltaTime = (1.f / 60.f);
        #endif // _DEBUG

        // 누적시간을 통해서 프로그램이 실행된 이후로 지나간 시간을 기록
        m_Time += m_DeltaTime;
    }

    // 현재 카운트 값을 저장
    m_llPrevCount = m_llCurCount;
    // 이하 코드는 기존과 동일...
}
```

이 방식을 사용하면, `StartFreezeEffect` 함수를 호출하여 지정된 시간 동안 게임의 시간 흐름을 멈추게 할 수 있습니다. 이 기간 동안 `DeltaTime`이 0으로 설정되므로, 게임 로직이 업데이트되지 않아 멈칫하는 효과를 경험할 수 있습니다.