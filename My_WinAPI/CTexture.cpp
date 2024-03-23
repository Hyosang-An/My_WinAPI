#include "pch.h"
#include "CTexture.h"
#include "CEngine.h"

#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "GdiPlus.lib")
using namespace Gdiplus;

#include <filesystem>
namespace fs = std::filesystem;

CTexture::CTexture() :
	m_hDC{},
	m_hBitmap{},
	m_Info{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBitmap);
}

int CTexture::Load(const wstring& _strFilePath)
{
    // ���� ���� �ڵ�
    //wchar_t szExt[50] = {};
    //_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 50);

    fs::path filePath = _strFilePath;
    wstring ext = filePath.extension().wstring();


    if (ext == L".bmp")
    {
        m_hBitmap = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str()
            , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (nullptr == m_hBitmap)
        {
            MessageBox(nullptr, L"��Ʈ�� �ε� ����", L"Asset �ε� ����", MB_OK);
            return E_FAIL;
        }        
    }

    else if (ext == L".png")
    {
        ULONG_PTR gdiplusToken = 0;
        GdiplusStartupInput gdiplusinput = {};
        GdiplusStartup(&gdiplusToken, &gdiplusinput, nullptr);

        Image* pImg = Image::FromFile(_strFilePath.c_str(), 0);
        Bitmap* pBitmap = (Bitmap*)pImg->Clone();
        Gdiplus::Status status = pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBitmap);
        assert(status == Gdiplus::Status::Ok);
    }

    else
    {
        assert(nullptr);
    }

    // �ε�� ��Ʈ���� ������ Ȯ���Ѵ�.
    GetObject(m_hBitmap, sizeof(BITMAP), &m_Info);

    // DC �� �������Ѽ� �ε�� ��Ʈ���̶� �����Ѵ�.
    m_hDC = CreateCompatibleDC(CEngine::GetInstance().GetMainDC());
    DeleteObject(SelectObject(m_hDC, m_hBitmap));

    return S_OK;
}

int CTexture::Create(UINT _width, UINT _height)
{
	// DC ����
	m_hDC = CreateCompatibleDC(CEngine::GetInstance().GetMainDC());

	// Bitmap ����
	m_hBitmap = CreateCompatibleBitmap(CEngine::GetInstance().GetMainDC(), _width, _height);

	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hDC, m_hBitmap);
	DeleteObject(hPrevBitmap);

	GetObject(m_hBitmap, sizeof(BITMAP), &m_Info);

	return S_OK;
}
