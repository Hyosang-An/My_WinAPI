#include "pch.h"
#include "CKeyMgr.h"
#include "CEngine.h"

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	for (int i = 0; i < (UINT)KEY::END; i++)
	{
		tKeyInfo KeyInfo{};
		KeyInfo.eKey = (KEY)i;
		KeyInfo.eKeyState = KEY_STATE::NONE;
		KeyInfo.bPressed = false;

		m_vecKeyInfo.push_back(KeyInfo);
	}
}

void CKeyMgr::tick()
{
	// MainWindow�� ��Ŀ�� �����϶��� Ű �Է� ����
	if (CEngine::GetInstance().GetMainWnd() == GetFocus())
	{
		for (UINT i = 0; i < (UINT)KEY::END; ++i)
		{
			auto& KeyInfo = m_vecKeyInfo[i];
			// ���� Ű�� ���ȴ��� üũ
			if (0x8001 & GetAsyncKeyState(m_RealKey[i]))
			{
				//�������� ���� �־�����
				if (KeyInfo.bPressed)
				{
					KeyInfo.eKeyState = KEY_STATE::PRESSED;
				}
				else
				{
					KeyInfo.eKeyState = KEY_STATE::JUST_PRESSED;
					KeyInfo.bPressed = true;
				}
			}

			else
			{
				//�������� ���� �־�����
				if (KeyInfo.bPressed)
				{
					KeyInfo.eKeyState = KEY_STATE::RELEASED;
					KeyInfo.bPressed = false;
				}
				else
				{
					KeyInfo.eKeyState = KEY_STATE::NONE;
				}
			}
		}

		// ���콺 ��ǥ ���
		m_PrevMousePos = m_MousePos;

		POINT ptMousePos{};
		GetCursorPos(&ptMousePos);
		ScreenToClient(CEngine::GetInstance().GetMainWnd(), &ptMousePos);
		m_MousePos = ptMousePos;
		m_DragDir = (m_MousePos - m_PrevMousePos);
	}

	// ������ ��Ŀ���� �����Ǹ� �����ִ� Ű ����(Release)
	else
	{
		for (UINT i = 0; i < (UINT)KEY::END; i++)
		{
			auto& KeyInfo = m_vecKeyInfo[i];

			if (KeyInfo.eKeyState == KEY_STATE::NONE)
				continue;

			if (KeyInfo.eKeyState == KEY_STATE::JUST_PRESSED || KeyInfo.eKeyState == KEY_STATE::PRESSED)
				KeyInfo.eKeyState = KEY_STATE::RELEASED;

			else
				KeyInfo.eKeyState = KEY_STATE::NONE;

			KeyInfo.bPressed = false;
		}
	}
	
}


