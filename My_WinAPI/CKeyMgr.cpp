#include "pch.h"
#include "CKeyMgr.h"

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
	for (UINT i = 0; i < (UINT)KEY::END; ++i)
	{
		auto &KeyInfo = m_vecKeyInfo[i];
		// 현재 키가 눌렸는지 체크
		if (0x8001 & GetAsyncKeyState(m_RealKey[i]))
		{
			//이전에도 눌려 있었는지
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
			//이전에도 눌려 있었는지
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
}


