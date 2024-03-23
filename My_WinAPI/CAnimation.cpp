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

	// AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	// 현재 프레임 이미지를 오브젝트 위치에 렌더링
	AlphaBlend(SUBDC, 
		(int)(vPos.x - frm.SliceSize.x / 2.f + frm.Offset.x), (int)(vPos.y - frm.SliceSize.y / 2.f + frm.Offset.y), (int)frm.SliceSize.x, (int)frm.SliceSize.y,
		m_Atlas->GetDC(), (int)frm.PosInAtlas.x, (int)frm.PosInAtlas.y, (int)frm.SliceSize.x, (int)frm.SliceSize.y, 
		bf);

	//TransparentBlt(SUBDC, (int)(vPos.x - frm.SliceSize.x / 2.f + frm.Offset.x), (int)(vPos.y - frm.SliceSize.y / 2.f + frm.Offset.y), (int)frm.SliceSize.x, (int)frm.SliceSize.y,
	//	m_Atlas->GetDC(), (int)frm.PosInAtlas.x, (int)frm.PosInAtlas.y, (int)frm.SliceSize.x, (int)frm.SliceSize.y, RGB(255, 0, 255));
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
	frm.fDuration = _fDuration;
	frm.PosInAtlas = _PosInAtlas;
	frm.SliceSize = _SliceSize;
	m_vecAnimFrame.push_back(frm);
}


// ============================================================================================================


#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

void CAnimation::Save(const std::wstring& _strRelativeFolderPath)
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



int CAnimation::Load(const std::wstring& _strRelativeFilePath)
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


