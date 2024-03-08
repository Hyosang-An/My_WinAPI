#pragma once
#include "Singleton.h"

enum class KEY
{
	_0, _1, _2, _3, _4, _5, _6, _7, _8, _9,

	_Q, W, _E, _R, _T, _Y, _U, _I, _O, _P,
	_A, _S, _D, _F, _G, _H, _J, _K, _L,
	_Z, _X, _C, _V, _B, _N, _M,

	LEFT, RIGHT, UP, DOWN,

	ENTER, SPACE, ALT, CTRL, SHIFT, ESC,

	END
};

enum class KEY_STATE
{
	JUST_PRESSED, // Ű�� �� ���� ����
	PRESSED,      // Ű�� �����ִ� ����
	RELEASED,     // Ű�� ������ ����
	NONE
};

struct tKeyInfo
{
	KEY         eKey;       // Ű�� ����
	KEY_STATE   eKeyState;  // Ű�� ���� ����
	bool        bPressed;   // Ű�� ���� �����ִ� ��������
};
class CKeyMgr :
	public Singleton<CKeyMgr>
{
	friend Singleton<CKeyMgr>;

private:
	vector<tKeyInfo>    m_vecKeyInfo;


public:
	void init();
	void tick();

	KEY_STATE GetKeyState(KEY _key) { return m_vecKeyInfo[(UINT)_key].eKeyState; }

private:
	UINT    m_RealKey[(UINT)KEY::END] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,

		VK_RETURN,
		VK_SPACE,
		VK_MENU,
		VK_CONTROL,
		VK_LSHIFT,
		VK_ESCAPE,
	};

private:
	CKeyMgr();
	~CKeyMgr();
};

// Ű ���� üũ ���� ��ũ�� �Լ��� �ζ��� �Լ��� ��ȯ
inline bool KEY_CHECK(KEY _key, KEY_STATE _state) {
	return CKeyMgr::GetInstance().GetKeyState(_key) == _state;
}

inline bool KEY_JUST_PRESSED(KEY _key) {
	return KEY_CHECK(_key, KEY_STATE::JUST_PRESSED);
}

inline bool KEY_PRESSED(KEY _key) {
	return KEY_CHECK(_key, KEY_STATE::PRESSED);
}

inline bool KEY_RELEASED(KEY _key) {
	return KEY_CHECK(_key, KEY_STATE::RELEASED);
}

inline bool KEY_NONE(KEY _key) {
	return KEY_CHECK(_key, KEY_STATE::NONE);
}

