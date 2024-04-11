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
	m_bFinished(false),
	m_bPlayingForward(true),
	m_bRepeatReverse(false)
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
	m_bPlayingForward = true;
}

void CAnimation::ResetReverse()
{
	m_frameElapsedTime = 0;
	m_CurFrameIdx = (int)m_vecAnimFrame.size() - 2;
	m_bFinished = false;
	m_bPlayingForward = false;
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

		// ������ ������� ������ ������� ����
		if (m_bPlayingForward)
		{
			// �������� �������� ������ ���
			if (m_vecAnimFrame.size() - 1 <= m_CurFrameIdx)
			{
				// �պ� ��� ����� ���
				if (m_bRepeatReverse)
				{
					m_bPlayingForward = false;
					m_CurFrameIdx--;
				}
				else
					m_bFinished = true;
			}
			else
				++m_CurFrameIdx;
		}
		else
		{
			// �������� ó���� ������ ��� (1�� �ؾ� �� ó�� �������� ��� ���� ����. �ݺ��� �� ������ ����ϴϱ�.)
			if (m_CurFrameIdx <= 1)
			{
				m_bPlayingForward = true;
				m_bFinished = true;
			}
			else
				--m_CurFrameIdx;
		}

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
	Vec2 vRenderPos = pOwnerObj->GetRenderPos();

	// AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	// ���� ������ �̹����� ������Ʈ ��ġ�� ������
	AlphaBlend(SUBDC, 
		(int)(vRenderPos.x - frm.SliceSize.x / 2.f + frm.Offset.x), (int)(vRenderPos.y - frm.SliceSize.y / 2.f + frm.Offset.y), (int)frm.SliceSize.x, (int)frm.SliceSize.y,
		m_Atlas->GetDC(), (int)frm.PosInAtlas.x, (int)frm.PosInAtlas.y, (int)frm.SliceSize.x, (int)frm.SliceSize.y, 
		bf);

	//TransparentBlt(SUBDC, (int)(vPos.x - frm.SliceSize.x / 2.f + frm.Offset.x), (int)(vPos.y - frm.SliceSize.y / 2.f + frm.Offset.y), (int)frm.SliceSize.x, (int)frm.SliceSize.y,
	//	m_Atlas->GetDC(), (int)frm.PosInAtlas.x, (int)frm.PosInAtlas.y, (int)frm.SliceSize.x, (int)frm.SliceSize.y, RGB(255, 0, 255));
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
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� ���� ����");
		return;
	}

	// �ִϸ��̼� �̸� ����
	outFile << L"[ANIMATION_NAME]\n" << GetName() << L"\n\n";

	// ��Ʋ�� �ؽ�ó ���� ����
	outFile << L"[ATLAS_TEXTURE]\n";
	if (nullptr == m_Atlas)
	{
		outFile << L"[ATLAS_KEY]\tNone\n";
		outFile << L"[ATLAS_PATH]\tNone\n";
	}
	else
	{
		outFile << L"[ATLAS_KEY]\t" << m_Atlas->GetKey() << L"\n";
		outFile << L"[ATLAS_PATH]\t" << m_Atlas->GetRelativePath() << L"\n";
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

int CAnimation::Load(const std::wstring& _strRelativeAnimFilePath)
{
	fs::path filePath = CPathMgr::GetInstance().GetContentsPath();
	filePath /= _strRelativeAnimFilePath;

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
		else if (tag == L"[ATLAS_TEXTURE]")
		{
			std::wstring atlasKey, atlasPath;
			while (std::getline(inFile, line) && !line.empty())
			{
				// ']'�� ã���ϴ�.
				size_t endOfKey = line.find(L']');
				if (endOfKey == std::wstring::npos) continue; // ']'�� ã�� ���� ���, ���� �ٷ� �Ѿ�ϴ�.

				// Ű�� �����մϴ�. ('['���� ']'����)
				std::wstring key = line.substr(0, endOfKey + 1);

				// ']' ���������� ���ڿ����� ù ��° ������ �ƴ� ���ڸ� ã���ϴ�.
				size_t startOfValue = line.find_first_not_of(L" \t\n", endOfKey + 1);
				std::wstring value;
				if (startOfValue != std::wstring::npos) {
					// ���� �����մϴ�.
					value = line.substr(startOfValue);
				}

				// Ű�� ���� ���� ������ ó���մϴ�.
				if (key == L"[ATLAS_KEY]") {
					atlasKey = value;
				}
				else if (key == L"[ATLAS_PATH]") {
					atlasPath = value;
				}
			}

			if (!atlasKey.empty() && !atlasPath.empty()) {
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

				// �� �� ó��
				std::getline(inFile, line);

				m_vecAnimFrame[i] = frm;
			}
		}
	}

	return S_OK;
}

