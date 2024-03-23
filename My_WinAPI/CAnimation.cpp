#include "pch.h"
#include "CAnimation.h"

#include "CObj.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CEngine.h"


CAnimation::CAnimation() :
	m_Animator(nullptr),
	m_Atlas(nullptr),
	m_frameElapsedTime(0),
	m_CurFrameIdx(0),
	m_bFinished(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Reset()
{
	m_frameElapsedTime = 0;
	m_CurFrameIdx = 0;
	m_bFinished = false;
}

void CAnimation::finaltick()
{
	if (m_bFinished)
		return;

	// ���� ������ ����
	const tAnimationFrame& frm = m_vecAnimFrame[m_CurFrameIdx];
	m_frameElapsedTime += DT;

	if (frm.fDuration <= m_frameElapsedTime)
	{
		m_frameElapsedTime -= frm.fDuration;

		// �������� �������� ������ ���
		if (m_vecAnimFrame.size() - 1 <= m_CurFrameIdx)
		{
			m_bFinished = true;
		}
		else
			++m_CurFrameIdx;
	}
}

void CAnimation::render()
{
	if (m_Atlas == nullptr)
		return;

	// ���� ������ ����
	const tAnimationFrame& frm = m_vecAnimFrame[m_CurFrameIdx];

	// �ִϸ��̼��� ����ϰ� �ִ� ������Ʈ
	CObj* pOwnerObj = m_Animator->GetOwner();

	// ������Ʈ ��ġ
	Vec2 vPos = pOwnerObj->GetPos();

	// ���� ������ �̹����� ������Ʈ ��ġ�� ������
	TransparentBlt(SUBDC, (int)(vPos.x - frm.SliceSize.x / 2.f + frm.Offset.x), (int)(vPos.y - frm.SliceSize.y / 2.f + frm.Offset.y), (int)frm.SliceSize.x, (int)frm.SliceSize.y,
		m_Atlas->GetDC(), (int)frm.PosInAtlas.x, (int)frm.PosInAtlas.y, (int)frm.SliceSize.x, (int)frm.SliceSize.y, RGB(255, 0, 255));


}

void CAnimation::Create(CTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS)
{
	m_Atlas = _AtlasTex;

	// ������ ���� ����
	for (int i = 0; i < _FrameCount; i++)
	{
		tAnimationFrame frm{};
		frm.fDuration = 1.f / float(_FPS);
		frm.PosInAtlas = _StartPos + Vec2(_SliceSize.x * i, 0);   // ��Ʋ�� �ؽ��Ŀ��� �� �ִϸ��̼� �ؽ��İ� ���������� ����Ǵ� ��쿡 ���ؼ�.
		frm.SliceSize = _SliceSize;
		m_vecAnimFrame.push_back(frm);
	}
}

void CAnimation::CreateAnimationFrame(Vec2 _PosInAtlas, Vec2 _SliceSize, float _fDuration)
{
	tAnimationFrame frm{};
	frm.fDuration = 1.f / float(_fDuration);
	frm.PosInAtlas = _PosInAtlas;
	frm.SliceSize = _SliceSize;
	m_vecAnimFrame.push_back(frm);
}



void CAnimation::Save(wstring _strRelativePath)
{
	// _strRelativeFilePath�� �� �տ� "\"�� ������ �߰�
	if (!_strRelativePath.empty() && _strRelativePath[0] != L'\\')
	{
		_strRelativePath = L"\\" + _strRelativePath;
	}

	wstring strFilePath = CPathMgr::GetInstance().GetContentsPath();
	strFilePath += _strRelativePath;
	strFilePath += GetName();
	strFilePath += L".anim";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (pFile == nullptr)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� ���� ����");
		return;
	}

	// �ִϸ��̼� �̸� ����
	wstring strAnimName = GetName();
	SaveWStringToFile(strAnimName, pFile);

	// ������ ���� ����
	size_t FrmCount = m_vecAnimFrame.size();
	fwrite(&FrmCount, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < FrmCount; i++)
	{
		fwrite(&m_vecAnimFrame[i], sizeof(tAnimationFrame), 1, pFile);
	}

	//��Ʋ�� �ؽ��� ������ ����
	bool bAtlasTex = false;
	if (m_Atlas != nullptr)
		bAtlasTex = true;

	fwrite(&bAtlasTex, sizeof(bool), 1, pFile);

	if (bAtlasTex)
	{
		SaveWStringToFile(m_Atlas->GetKey(), pFile);
		SaveWStringToFile(m_Atlas->GetRelativePath(), pFile);
	}

	fclose(pFile);
}

int CAnimation::Load(const wstring& _strRelativeFilePath)
{
	//wstring strFilePath = CPathMgr::GetInstance().GetContentsPath();
	//strFilePath += _strRelativeFilePath;

	//FILE* pFile = nullptr;
	//_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	//if (nullptr == pFile)
	//	return E_FAIL;

	//// �ִϸ��̼��� �̸� �б�
	//wstring strAnimName;
	//if (LoadWStringFromFile(strAnimName, pFile) == E_FAIL)
	//	return E_FAIL;

	//SetName(strAnimName);

	//// ������ ���� �б�
	//size_t FrameCount = 0;
	//fread(&FrameCount, sizeof(size_t), 1, pFile);
	//
	//for (size_t i = 0; i < FrameCount; i++)
	//{
	//	tAnimationFrame frm{};
	//	fread(&frm, sizeof(tAnimationFrame), 1, pFile);
	//	m_vecAnimFrame.push_back(frm);
	//}

	//bool bAtlasTex = false;
	//fread(&bAtlasTex, sizeof(bool), 1, pFile);

	//// ��Ʋ�� �ؽ��ĸ� ����ϴ� ��� ��Ʋ�� �ؽ��� ���� �б�
	//if (bAtlasTex)
	//{
	//	wstring strKey;
	//	if (LoadWStringFromFile(strKey, pFile) == E_FAIL)
	//		return E_FAIL;

	//	wstring strRelativePath;
	//	if (LoadWStringFromFile(strRelativePath, pFile) == E_FAIL)
	//		return E_FAIL;

	//	m_Atlas = CAssetMgr::GetInstance().LoadTexture(strKey, strRelativePath);
	//}

	//fclose(pFile);

	//return S_OK;

	//======================================================================================================

	wstring strFilePath = CPathMgr::GetInstance().GetContentsPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;
	if (_wfopen_s(&pFile, strFilePath.c_str(), L"rb") != 0 || pFile == nullptr) {
		// ���� ���� ����
		return E_FAIL;
	}

	// RAII�� ����� �ڿ� ������ ������ �� �ִ� ����� ������, ���⼭�� C ��Ÿ�� ���� ������� ����
	// pFile�� nullptr�� �ƴϸ� ���� �ݱ�
	auto fileCloser = [&pFile]() { if (pFile) fclose(pFile); };

	// �ִϸ��̼��� �̸� �б�
	wstring strAnimName;
	if (LoadWStringFromFile(strAnimName, pFile) == E_FAIL) {
		fileCloser();
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� �ҷ����� ����");
		return E_FAIL;
	}
	SetName(strAnimName);

	// ������ ���� �б�
	size_t FrameCount = 0;
	if (fread(&FrameCount, sizeof(size_t), 1, pFile) != 1) {
		fileCloser();
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� �ҷ����� ����");
		return E_FAIL; // ���� ó��
	}

	for (size_t i = 0; i < FrameCount; ++i) {
		tAnimationFrame frm{};
		if (fread(&frm, sizeof(tAnimationFrame), 1, pFile) != 1) {
			fileCloser();
			LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� �ҷ����� ����");
			return E_FAIL; // ���� ó��
		}
		m_vecAnimFrame.push_back(frm);
	}

	// ��Ʋ�� �ؽ��� ��� ���� �б�
	bool bAtlasTex = false;
	if (fread(&bAtlasTex, sizeof(bool), 1, pFile) != 1) {
		fileCloser();
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� �ҷ����� ����");
		return E_FAIL; // ���� ó��
	}

	// ��Ʋ�� �ؽ��� ���� �б�
	if (bAtlasTex) {
		wstring strKey, strRelativePath;
		if (LoadWStringFromFile(strKey, pFile) == E_FAIL ||
			LoadWStringFromFile(strRelativePath, pFile) == E_FAIL) {
			fileCloser();
			LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� �ҷ����� ����");
			return E_FAIL;
		}

		m_Atlas = CAssetMgr::GetInstance().LoadTexture(strKey, strRelativePath);
	}

	fileCloser(); // ���� �ݱ�
	return S_OK;
}



// ============================================================================================================


#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

void CAnimation::Save2(const std::wstring& _strRelativeFolderPath)
{
	fs::path filePath = CPathMgr::GetInstance().GetContentsPath();
	filePath /= _strRelativeFolderPath;
	filePath /= GetName();
	filePath += L".anim";

	std::wofstream outFile(filePath);
	if (!outFile.is_open())
	{
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� ���� ����");
		return;
	}

	// �ִϸ��̼� �̸� ����
	outFile << L"[ANIMATION_NAME]\n" << GetName() << L"\n\n";

	// ��Ʋ�� �ؽ�ó ���� ����
	outFile << L"[ALTAS_TEXTURE]\n";
	if (nullptr == m_Atlas)
	{
		outFile << L"[ALTAS_KEY]\tNone\n";
		outFile << L"[ALTAS_PATH]\tNone\n";
	}
	else
	{
		outFile << L"[ALTAS_KEY]\t" << m_Atlas->GetKey() << L"\n";
		outFile << L"[ALTAS_PATH]\t" << m_Atlas->GetRelativePath() << L"\n";
	}
	outFile << L"\n";

	// ������ ���� ����
	outFile << L"[FRAME_COUNT]\n" << m_vecAnimFrame.size() << L"\n\n";
	for (size_t i = 0; i < m_vecAnimFrame.size(); ++i)
	{
		outFile << L"[FRAME_INDEX]\t" << i << L"\n";
		outFile << L"[POS_IN_ATLAS]\t" << m_vecAnimFrame[i].PosInAtlas.x << L" " << m_vecAnimFrame[i].PosInAtlas.y << L"\n";
		outFile << L"[SLICE_SIZE]\t" << m_vecAnimFrame[i].SliceSize.x << L" " << m_vecAnimFrame[i].SliceSize.y << L"\n";
		outFile << L"[OFFSET]\t" << m_vecAnimFrame[i].Offset.x << L" " << m_vecAnimFrame[i].Offset.y << L"\n";
		outFile << L"[DURATION]\t" << m_vecAnimFrame[i].fDuration << L"\n\n";
	}
}



int CAnimation::Load2(const std::wstring& _strRelativeFilePath)
{
	fs::path filePath = CPathMgr::GetInstance().GetContentsPath();
	filePath /= _strRelativeFilePath;

	std::wifstream inFile(filePath);
	if (!inFile.is_open())
	{
		return E_FAIL;
	}

	std::wstring line;
	while (std::getline(inFile, line))
	{
		std::wistringstream iss(line);
		std::wstring tag;
		iss >> tag;

		if (tag == L"[ANIMATION_NAME]")
		{
			std::getline(inFile, line); // ���� �̸��� �о��
			SetName(line);
		}
		else if (tag == L"[ALTAS_TEXTURE]")
		{
			std::wstring atlasKey, atlasPath;
			while (std::getline(inFile, line) && !line.empty())
			{
				std::wistringstream iss(line);
				std::wstring key;
				iss >> key;
				if (key == L"[ALTAS_KEY]")
				{
					iss >> atlasKey;
				}
				else if (key == L"[ALTAS_PATH]")
				{
					iss >> atlasPath;
				}
			}
			if (!atlasKey.empty() && !atlasPath.empty())
			{
				m_Atlas = CAssetMgr::GetInstance().LoadTexture(atlasKey, atlasPath);
			}
		}
		else if (tag == L"[FRAME_COUNT]")
		{
			size_t frmCount;
			// inFile >> frmCount;
			std::getline(inFile, line); 
			frmCount = std::stoi(line);
			std::getline(inFile, line);	// ���� ���� ������ �κ��� �����ϰ�, ���� �ٷ� �Ѿ�ϴ�.

			m_vecAnimFrame.resize(frmCount);
			for (size_t i = 0; i < frmCount; ++i)
			{
				tAnimationFrame frm = {};
				std::getline(inFile, line); // [FRAME_INDEX] ���� ��ŵ
				std::getline(inFile, line); // [POS_IN_ATLAS] ���� �н��ϴ�.
				std::wistringstream issSP(line);
				std::wstring key;
				issSP >> key >> frm.PosInAtlas.x >> frm.PosInAtlas.y;

				std::getline(inFile, line); // [SLICE_SIZE] ���� �н��ϴ�.
				std::wistringstream issSS(line);
				issSS >> key >> frm.SliceSize.x >> frm.SliceSize.y;

				std::getline(inFile, line); // [OFFSET] ���� �н��ϴ�.
				std::wistringstream issO(line);
				issO >> key >> frm.Offset.x >> frm.Offset.y;

				std::getline(inFile, line); // [DURATION] ���� �н��ϴ�.
				std::wistringstream issD(line);
				issD >> key >> frm.fDuration;

				std::getline(inFile, line);

				m_vecAnimFrame[i] = frm;
			}
		}
	}

	return S_OK;
}


