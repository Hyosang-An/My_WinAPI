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
		MessageBox(nullptr, L"비트맵 로딩 실패", L"Asset 로딩 실패", MB_OK);
		return E_FAIL;
	}

	// 로드된 비트맵 정보를 확인한다.
	GetObject(m_hBitmap, sizeof(BITMAP), &m_Info);

	// DC를 생성시켜서 로드된 비트맵이랑 연결한다.
	m_hDC = CreateCompatibleDC(CEngine::GetInstance().GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBitmap));
	
	return S_OK;
}