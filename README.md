# My_WinAPI

### ���� �߰��� ����
**1.** Ÿ�ϸ� ������ ���� �� ���� ���� ����
```cpp
void CTileMap::SetRowCol(UINT _Row, UINT _Col)
{
	// CTileMap �����ڿ� m_vecTileInfo = vector<tTileInfo>(m_Row * m_Col); �߰��ؾߵ�.

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