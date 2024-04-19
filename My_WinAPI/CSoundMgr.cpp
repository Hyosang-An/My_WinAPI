#include "pch.h"
#include "CSoundMgr.h"

CSoundMgr::CSoundMgr() :
    m_pSound{}
{
}

CSoundMgr::~CSoundMgr()
{
    // DirectSound8 ��ü �޸� ����
    m_pSound->Release();
}

int CSoundMgr::init()
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"���� ����̽� ���� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// ���� �������� ����
	HWND hWnd = CEngine::GetInstance().GetMainWnd();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"���� �Ŵ��� �ʱ�ȭ ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void CSoundMgr::RegisterToBGM(CSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}

