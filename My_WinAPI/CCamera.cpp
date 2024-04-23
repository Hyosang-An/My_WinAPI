#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CEngine.h"
#include "CDbgRenderer.h"
#include "CPlayer.h"
#include "Worldmap_Player.h"
#include "CLevelMgr.h"

CCamera::CCamera() :
	m_FadeTex{},
	m_RedTex{},
	m_Player{},
	m_Worldmap_Player{}
{
}

CCamera::~CCamera()
{
}

void CCamera::init()
{
	// 카메라 시작 위치
	m_CameraLeftTopPos = Vec2(0, 0);

	m_resolution = CEngine::GetInstance().GetResolution();
	m_CameraRealCenterPos = m_resolution / 2.f;
	// 윈도우 해상도랑 동일한 크기의 검은색 텍스쳐를 생성
	
	m_FadeTex = CAssetMgr::GetInstance().CreateTexture(L"Fade Textrue", (UINT)m_resolution.x, (UINT)m_resolution.y);

	// ScreenFX
	for (int i = 0; i < 127; i++)
	{
		wstring strpath = L"texture\\Screen FX\\";
		wstring filename = L"cuphead_screen_fx_";
		wstring num = std::to_wstring(i);
		num = std::wstring(4 - num.length(), L'0') + num;

		m_vecScreenFX.push_back(CAssetMgr::GetInstance().LoadTexture(filename + num, strpath + filename + num + L".png"));
	}
}

void CCamera::tick()
{
	// 카메라 이동
	Move();

	// 카메라 이펙트 업데이트
	UpdateCameraEffect();
}

void CCamera::Move()
{
	m_PrevCameraLeftTopPos = m_CameraLeftTopPos;

	if (CDbgRenderer::GetInstance().IsDBGMode())
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

	else
	{
		switch (m_bTrackingState)
		{
			case CAM_TRACKING_STATE::NONE:
				break;
			case CAM_TRACKING_STATE::WORLD_MAP:
				TrackingPlayer_Worldmap();
				break;
			case CAM_TRACKING_STATE::BOSS_STAGE:
				TrackingPlayer_BossStage();
				break;
			case CAM_TRACKING_STATE::RUN_AND_GUN_STAGE:
				TrackingPlayer_RunAndGunStage();
				break;
			default:
				break;
		}


	}


	m_CameraRealCenterPos = m_CameraLeftTopPos + m_resolution / 2.f;
}


void CCamera::UpdateCameraEffect()
{
	// 완료된 이펙트 제거
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

	// 이펙트 상태 업데이트
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

void CCamera::TrackingPlayer_RunAndGunStage()
{
	if (m_Player == nullptr)
		return;

	Vec2 diff = m_Player->GetPos() - m_CameraRealCenterPos;

	// X방향 카메라 속도 업데이트
	//=================================================================
	float min_camera_speed_X = 80.f;
	static float cameraSpeed_X{};
	static bool bCameraCentering = false;

	// 카메라와 플레이어 간의 거리가 매우 가까울 때 카메라 이동을 멈추게 하는 임계값 설정
	float thresholdDistance_X = 10.0f; // 이 값을 조정하여 카메라와 플레이어 간의 원하는 최소 거리 설정
	float playerRunSpeed = m_Player->m_RunSpeed;
	float lerpFactor = 2.2f;

	// 플레이어와 카메라 간의 이론상 최대 거리 (saturated 거리)
	float max_diff_X = playerRunSpeed / lerpFactor;

	// focus모드 일 때, 임계 거리
	float focus_diff_X = 50;

	if (bCameraCentering == false)
	{
		// diff.x의 절대값이 임계값보다 작으면 카메라 이동을 멈춥니다.
		if (abs(diff.x) < thresholdDistance_X) {
			cameraSpeed_X = 0;
		}
		else
		{
			cameraSpeed_X = max(abs(diff.x * lerpFactor), min_camera_speed_X);
			cameraSpeed_X = diff.x > 0 ? cameraSpeed_X : -cameraSpeed_X;
		}
	}
	else
	{
		if (abs(diff.x) <= focus_diff_X)
			cameraSpeed_X = cameraSpeed_X > 0 ? playerRunSpeed : -playerRunSpeed;

		if (abs(diff.x) < thresholdDistance_X) {
			bCameraCentering = false;
			cameraSpeed_X = 0;
		}
	}

	// cameraCentering 임계 거리는 이론상 최대 멀어지는 거리보다 좀 작게 해야 원활함.
	if (abs(diff.x) >= max_diff_X - 25)
	{
		bCameraCentering = true;
		cameraSpeed_X = cameraSpeed_X > 0 ? playerRunSpeed * 1.4f : -playerRunSpeed * 1.4f;
	}

	//!디버그
	{
		m_diff = diff;
	}

	//if (!CDbgRenderer::GetInstance().IsDBGMode())
	m_CameraLeftTopPos.x += cameraSpeed_X * DT;

	// Y방향 카메라 위치 업데이트
	//=================================================================
	if (diff.y < -200)
	{
		m_CameraLeftTopPos.y += (diff.y + 200);
	}
	else if (diff.y > 150)
	{
		m_CameraLeftTopPos.y += (diff.y - 150);
	}
}

void CCamera::TrackingPlayer_BossStage()
{
	// 카메라 좌표 기준은 lefttop
	float cameraLeftLimit = m_StageRange.x;
	float cameraRightLimit = m_StageRange.y - m_resolution.x;
	float playerLeftLimit = m_StageRange.x + 30;	// 플레이어 충돌체 오프셋
	float playerRightLimit = m_StageRange.y - 30;	// 플레이어 충돌체 오프셋
	float player_posX = m_Player->m_Pos.x;

	float playerPosRatio = (player_posX - playerLeftLimit) / (playerRightLimit - playerLeftLimit);

	m_CameraLeftTopPos.x = cameraLeftLimit + playerPosRatio * (cameraRightLimit - cameraLeftLimit);

}

void CCamera::TrackingPlayer_Worldmap()
{
	if (m_Worldmap_Player == nullptr)
		return;

	Vec2 diff = m_Worldmap_Player->GetPos() - m_CameraRealCenterPos;

	// X방향 카메라 속도 업데이트
	//=================================================================
	float min_camera_speed = 80.f;
	static float cameraSpeed{};
	static bool bCameraCentering = false;

	// 카메라와 플레이어 간의 거리가 매우 가까울 때 카메라 이동을 멈추게 하는 임계값 설정
	float thresholdDistance = 2.0f; // 이 값을 조정하여 카메라와 플레이어 간의 원하는 최소 거리 설정
	float playerWalkSpeed = m_Worldmap_Player->m_WalkSpeed;
	float lerpFactor = 5.2f;

	// 플레이어와 카메라 간의 이론상 최대 거리 (saturated 거리)
	float max_diff = playerWalkSpeed / lerpFactor;

	// focus모드 일 때, 임계 거리
	float focus_diff = 50;


	// diff의 길이가 임계값보다 작으면 카메라 이동을 멈춥니다.
	if (diff.Length() < thresholdDistance) {
		cameraSpeed = 0;
	}
	else
	{
		cameraSpeed = max(diff.Length() * lerpFactor, min_camera_speed);
	}

	if (diff.Length() != 0)
		m_CameraLeftTopPos += diff.Normalize() * cameraSpeed * DT;
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

void CCamera::SetCameraInitialLookAt(Vec2 _pos)
{
	m_CameraRealCenterPos = _pos;
	m_CameraLeftTopPos = _pos - (0.5 * m_resolution);
	m_PrevCameraLeftTopPos = m_CameraLeftTopPos;
}

void CCamera::SetCameraLookAt(Vec2 _pos)
{
	m_CameraRealCenterPos = _pos;
	m_CameraLeftTopPos = _pos - (0.5 * m_resolution);
}

void CCamera::CameraEffectRender()
{
	// !디버그 
	
	if (CLevelMgr::GetInstance().GetCurrentLevel() != nullptr 
		&& CLevelMgr::GetInstance().GetCurrentLevel()->GetName() == L"Test Level"
		&& !CDbgRenderer::GetInstance().IsDBGMode())

	{
		wstring strDiff = L"diff from camera center to player : " + std::to_wstring(m_diff.x) + L", " + std::to_wstring(m_diff.y);
		TextOut(SUBDC, (int)400, 50,
			strDiff.c_str(), (int)strDiff.length());
	}

	BLENDFUNCTION bf{};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;

	if (!m_listEffect.empty())
	{
		CAM_EFFECT_INFO info = m_listEffect.front();
		bf.SourceConstantAlpha = (int)info.Alpha;

		AlphaBlend(SUBDC, 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight()
			, m_FadeTex->GetDC(), 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight(), bf);
	}


	//Screen FX 렌더링

	bf.SourceConstantAlpha = int(255 * 0.2);
	m_ScreenFXframeElapsedTime += DT;

	if (m_ScreenFXframeDuration < m_ScreenFXframeElapsedTime)
	{
		m_ScreenFXframeElapsedTime -= m_ScreenFXframeDuration;
		
		// 프레임이 마지막에 도달한 경우
		if (m_CurScreenFXFrameIdx >= m_vecScreenFX.size() - 1)
		{
			m_CurScreenFXFrameIdx = 0;
		}
		else
			m_CurScreenFXFrameIdx++;
	}

	auto curFrame = m_vecScreenFX[m_CurScreenFXFrameIdx];
	AlphaBlend(SUBDC, 0, 0, (int)m_resolution.x, (int)m_resolution.y
		, curFrame->GetDC(), 0, 0, curFrame->GetWidth(), curFrame->GetHeight(), bf);
}
