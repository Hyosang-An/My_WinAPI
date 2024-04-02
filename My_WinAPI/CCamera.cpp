#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CCamera::CCamera() :
	m_FadeTex{},
	m_RedTex{}
{
}

CCamera::~CCamera()
{
}

void CCamera::Move()
{
	if (KEY_PRESSED(KEY::W))
		m_CameraLeftTopPos.y -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::S))
		m_CameraLeftTopPos.y += DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::A))
		m_CameraLeftTopPos.x -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::D))
		m_CameraLeftTopPos.x += DT * m_CamSpeed;
}

void CCamera::CameraEffect()
{
	// �Ϸ�� ����Ʈ ����
	while (!m_listEffect.empty())
	{
		CAM_EFFECT_INFO& info = m_listEffect.front();

		if (info.Duration < info.ElapsedTime)
			m_listEffect.pop_front();
		else
			break;
	}

	if (m_listEffect.empty())
		return;

	// ����Ʈ ���� ������Ʈ
	CAM_EFFECT_INFO& info = m_listEffect.front();
	info.ElapsedTime += DT;

	const float ALPHA_MAX = 255.f;

	switch (info.Effect)
	{
		case CAM_EFFECT::FADE_IN:
			info.Alpha = (1.f - (info.ElapsedTime / info.Duration)) * ALPHA_MAX;
			break;
		case CAM_EFFECT::FADE_OUT:
			info.Alpha = (info.ElapsedTime / info.Duration) * ALPHA_MAX;
			break;
		default:
			break;
	}

}

void CCamera::SetCameraEffect(CAM_EFFECT _effect, float _duration)
{
	CAM_EFFECT_INFO info{};

	info.Effect = _effect;
	info.Duration = _duration;
	info.ElapsedTime = 0;
	info.Alpha = 0;

	m_listEffect.push_back(info);
}

void CCamera::init()
{
	// ī�޶� ���� ��ġ
	m_CameraLeftTopPos = Vec2(0, 0);

	// ������ �ػ󵵶� ������ ũ���� ������ �ؽ��ĸ� ����
	Vec2 resolution = CEngine::GetInstance().GetResolution();
	m_FadeTex = CAssetMgr::GetInstance().CreateTexture(L"Fade Textrue", (UINT)resolution.x, (UINT)resolution.y);	
}

void CCamera::tick()
{
	// ī�޶� �̵�
	Move();
	
	// ī�޶� ����Ʈ ����
	CameraEffect();
}

void CCamera::render()
{
	if (m_listEffect.empty())
		return;

	CAM_EFFECT_INFO info = m_listEffect.front();

	BLENDFUNCTION bf{};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)info.Alpha;
	bf.AlphaFormat = 0;

	AlphaBlend(SUBDC, 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight()
		, m_FadeTex->GetDC(), 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight(), bf);
}
