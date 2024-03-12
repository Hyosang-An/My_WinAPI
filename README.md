# My_WinAPI

### 추후 추가할 사항
**1.** 타일맵 사이즈 변경 시 기존 정보 유지
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

**2.** 다이얼로그 창 종료 시 키 입력 초기화
```
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
