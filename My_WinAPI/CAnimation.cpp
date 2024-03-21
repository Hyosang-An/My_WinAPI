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
		if (m_vecAnimFrame.size() <= m_CurFrameIdx)
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
		m_Atlas->GetDC(), (int)frm.StartPos.x, (int)frm.StartPos.y, (int)frm.SliceSize.x, (int)frm.SliceSize.y, RGB(255, 0, 255));
}

void CAnimation::Create(CTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS)
{
	m_Atlas = _AtlasTex;

	// 프레임 정보 생성
	for (int i = 0; i < _FrameCount; i++)
	{
		tAnimationFrame frm{};
		frm.fDuration = 1.f / float(_FPS);
		frm.StartPos = _StartPos + Vec2(_SliceSize.x * i, 0);   // 아틀라스 텍스쳐에서 각 애니메이션 텍스쳐가 오른쪽으로 진행되는 경우에 대해서.
		m_vecAnimFrame.push_back(frm);
	}
}

void CAnimation::Save(const wstring& _strRelativePath)
{
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
		SaveWStringToFile(m_Atlas->GetRelativePath());
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

