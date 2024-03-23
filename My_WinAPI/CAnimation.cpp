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

	// 현재 프레임 정보
	const tAnimationFrame& frm = m_vecAnimFrame[m_CurFrameIdx];
	m_frameElapsedTime += DT;

	if (frm.fDuration <= m_frameElapsedTime)
	{
		m_frameElapsedTime -= frm.fDuration;

		// 프레임이 마지막에 도달한 경우
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

	// 현재 프레임 정보
	const tAnimationFrame& frm = m_vecAnimFrame[m_CurFrameIdx];

	// 애니메이션을 재생하고 있는 오브젝트
	CObj* pOwnerObj = m_Animator->GetOwner();

	// 오브젝트 위치
	Vec2 vPos = pOwnerObj->GetPos();

	// 현재 프레임 이미지를 오브젝트 위치에 렌더링
	TransparentBlt(SUBDC, (int)(vPos.x - frm.SliceSize.x / 2.f + frm.Offset.x), (int)(vPos.y - frm.SliceSize.y / 2.f + frm.Offset.y), (int)frm.SliceSize.x, (int)frm.SliceSize.y,
		m_Atlas->GetDC(), (int)frm.PosInAtlas.x, (int)frm.PosInAtlas.y, (int)frm.SliceSize.x, (int)frm.SliceSize.y, RGB(255, 0, 255));


}

void CAnimation::Create(CTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS)
{
	m_Atlas = _AtlasTex;

	// 프레임 정보 생성
	for (int i = 0; i < _FrameCount; i++)
	{
		tAnimationFrame frm{};
		frm.fDuration = 1.f / float(_FPS);
		frm.PosInAtlas = _StartPos + Vec2(_SliceSize.x * i, 0);   // 아틀라스 텍스쳐에서 각 애니메이션 텍스쳐가 오른쪽으로 진행되는 경우에 대해서.
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
	// _strRelativeFilePath의 맨 앞에 "\"가 없으면 추가
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
		LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 저장 실패");
		return;
	}

	// 애니메이션 이름 저장
	wstring strAnimName = GetName();
	SaveWStringToFile(strAnimName, pFile);

	// 프레임 벡터 저장
	size_t FrmCount = m_vecAnimFrame.size();
	fwrite(&FrmCount, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < FrmCount; i++)
	{
		fwrite(&m_vecAnimFrame[i], sizeof(tAnimationFrame), 1, pFile);
	}

	//아틀라스 텍스쳐 정보를 저장
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

	//// 애니메이션의 이름 읽기
	//wstring strAnimName;
	//if (LoadWStringFromFile(strAnimName, pFile) == E_FAIL)
	//	return E_FAIL;

	//SetName(strAnimName);

	//// 프레임 정보 읽기
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

	//// 아틀라스 텍스쳐를 사용하는 경우 아틀라스 텍스쳐 정보 읽기
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
		// 파일 열기 실패
		return E_FAIL;
	}

	// RAII를 사용해 자원 관리를 개선할 수 있는 대안이 있지만, 여기서는 C 스타일 파일 입출력을 유지
	// pFile이 nullptr이 아니면 파일 닫기
	auto fileCloser = [&pFile]() { if (pFile) fclose(pFile); };

	// 애니메이션의 이름 읽기
	wstring strAnimName;
	if (LoadWStringFromFile(strAnimName, pFile) == E_FAIL) {
		fileCloser();
		LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 불러오기 실패");
		return E_FAIL;
	}
	SetName(strAnimName);

	// 프레임 정보 읽기
	size_t FrameCount = 0;
	if (fread(&FrameCount, sizeof(size_t), 1, pFile) != 1) {
		fileCloser();
		LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 불러오기 실패");
		return E_FAIL; // 에러 처리
	}

	for (size_t i = 0; i < FrameCount; ++i) {
		tAnimationFrame frm{};
		if (fread(&frm, sizeof(tAnimationFrame), 1, pFile) != 1) {
			fileCloser();
			LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 불러오기 실패");
			return E_FAIL; // 에러 처리
		}
		m_vecAnimFrame.push_back(frm);
	}

	// 아틀라스 텍스쳐 사용 여부 읽기
	bool bAtlasTex = false;
	if (fread(&bAtlasTex, sizeof(bool), 1, pFile) != 1) {
		fileCloser();
		LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 불러오기 실패");
		return E_FAIL; // 에러 처리
	}

	// 아틀라스 텍스쳐 정보 읽기
	if (bAtlasTex) {
		wstring strKey, strRelativePath;
		if (LoadWStringFromFile(strKey, pFile) == E_FAIL ||
			LoadWStringFromFile(strRelativePath, pFile) == E_FAIL) {
			fileCloser();
			LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 불러오기 실패");
			return E_FAIL;
		}

		m_Atlas = CAssetMgr::GetInstance().LoadTexture(strKey, strRelativePath);
	}

	fileCloser(); // 파일 닫기
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
		LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 저장 실패");
		return;
	}

	// 애니메이션 이름 저장
	outFile << L"[ANIMATION_NAME]\n" << GetName() << L"\n\n";

	// 아틀라스 텍스처 정보 저장
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

	// 프레임 정보 저장
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
			std::getline(inFile, line); // 실제 이름을 읽어옴
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
			std::getline(inFile, line);	// 현재 줄의 나머지 부분을 무시하고, 다음 줄로 넘어갑니다.

			m_vecAnimFrame.resize(frmCount);
			for (size_t i = 0; i < frmCount; ++i)
			{
				tAnimationFrame frm = {};
				std::getline(inFile, line); // [FRAME_INDEX] 라인 스킵
				std::getline(inFile, line); // [POS_IN_ATLAS] 줄을 읽습니다.
				std::wistringstream issSP(line);
				std::wstring key;
				issSP >> key >> frm.PosInAtlas.x >> frm.PosInAtlas.y;

				std::getline(inFile, line); // [SLICE_SIZE] 줄을 읽습니다.
				std::wistringstream issSS(line);
				issSS >> key >> frm.SliceSize.x >> frm.SliceSize.y;

				std::getline(inFile, line); // [OFFSET] 줄을 읽습니다.
				std::wistringstream issO(line);
				issO >> key >> frm.Offset.x >> frm.Offset.y;

				std::getline(inFile, line); // [DURATION] 줄을 읽습니다.
				std::wistringstream issD(line);
				issD >> key >> frm.fDuration;

				std::getline(inFile, line);

				m_vecAnimFrame[i] = frm;
			}
		}
	}

	return S_OK;
}


