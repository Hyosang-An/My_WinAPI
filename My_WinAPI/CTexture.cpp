#include "pch.h"
#include "CTexture.h"
#include "CEngine.h"

CTexture::CTexture() :
	m_hDC{},
	m_hBitmap{},
	m_Info{}
{
}

CTexture::~CTexture()
{
}

int CTexture::Load(const wstring& _strFilePath)
{
	m_hBitmap = static_cast<HBITMAP>(LoadImage(	nullptr, _strFilePath.c_str(), 
												IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));

	if (m_hBitmap == nullptr)
	{
		MessageBox(nullptr, L"��Ʈ�� �ε� ����", L"Asset �ε� ����", MB_OK);
		return E_FAIL;
	}

	// �ε�� ��Ʈ�� ������ Ȯ���Ѵ�.
	GetObject(m_hBitmap, sizeof(BITMAP), &m_Info);

	// DC�� �������Ѽ� �ε�� ��Ʈ���̶� �����Ѵ�.
	m_hDC = CreateCompatibleDC(CEngine::GetInstance().GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBitmap));
	
	return S_OK;
}