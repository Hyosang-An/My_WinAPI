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

	// ���� ������ ����
	const tAnimationFrame& frm = m_vecAnimFrame[m_CurFrameIdx];

	// �ִϸ��̼��� ����ϰ� �ִ� ������Ʈ
	CObj* pOwnerObj = m_Animator->GetOwner();

	// ������Ʈ ��ġ
	Vec2 vPos = pOwnerObj->GetPos();

	// ���� ������ �̹����� ������Ʈ ��ġ�� ������
	TransparentBlt(SUBDC, (int)(vPos.x - frm.SliceSize.x / 2.f + frm.Offset.x), (int)(vPos.y - frm.SliceSize.y / 2.f + frm.Offset.y), (int)frm.SliceSize.x, (int)frm.SliceSize.y,
		m_Atlas->GetDC(), (int)frm.StartPos.x, (int)frm.StartPos.y, (int)frm.SliceSize.x, (int)frm.SliceSize.y, RGB(255, 0, 255));
}

void CAnimation::Create(CTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS)
{
	m_Atlas = _AtlasTex;

	// ������ ���� ����
	for (int i = 0; i < _FrameCount; i++)
	{
		tAnimationFrame frm{};
		frm.fDuration = 1.f / float(_FPS);
		frm.StartPos = _StartPos + Vec2(_SliceSize.x * i, 0);   // ��Ʋ�� �ؽ��Ŀ��� �� �ִϸ��̼� �ؽ��İ� ���������� ����Ǵ� ��쿡 ���ؼ�.
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

