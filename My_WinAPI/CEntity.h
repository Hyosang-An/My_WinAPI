#pragma once
class CEntity
{
private:
	// ���� ��� ����
	static UINT g_NextID;

	const UINT	m_ID;
	wstring		m_strName;

public:
	UINT GetID() { return m_ID; }
	void SetName(const wstring& _name) { m_strName = _name; }
	const wstring& GetName() { return m_strName; }

public:
	// CEntity�� �߻�Ŭ�����̴�.
	virtual CEntity* Clone() = 0;

public:
	CEntity();
	virtual ~CEntity();
};