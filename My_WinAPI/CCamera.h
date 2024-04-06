#pragma once
#include "Singleton.h"

class CPlayer;

enum class CAM_EFFECT
{
	NONE,
	FADE_IN,
	FADE_OUT,
};

struct CAM_EFFECT_INFO
{
	CAM_EFFECT  Effect;
	float       Duration;
	float       ElapsedTime;
	float       Alpha;
};

enum class CAM_TRACKING_STATE
{
	NONE,
	BOSS_STAGE,
	RUN_AND_GUN_STAGE
};

class CTexture;

class CCamera :
	public Singleton<CCamera>
{
	friend Singleton<CCamera>;

private:
	Vec2        m_CameraLeftTopPos;
	Vec2        m_PrevCameraLeftTopPos;
	Vec2        m_CameraRealCenterPos;

	Vec2		m_resolution;

	Vec2        m_StageRange;

	CPlayer* m_Player;

	float       m_CamSpeed = 500;
	list<CAM_EFFECT_INFO>   m_listEffect;

	CTexture* m_FadeTex;
	CTexture* m_RedTex;

	CAM_TRACKING_STATE    m_bTrackingState = CAM_TRACKING_STATE::NONE;

	// !µð¹ö±ë
	Vec2 m_diff;

private:
	void Move();
	void CameraEffect();
	void TrackingPlayer_RunAndGunStage();
	void TrackingPlayer_BossStage();


public:
	Vec2 GetRenderPos(Vec2 _realPos) { return _realPos - m_CameraLeftTopPos; }
	Vec2 GetRealPos(Vec2 _renderPos) { return _renderPos + m_CameraLeftTopPos; }

	Vec2 GetCameraDeltaPos() { return m_CameraLeftTopPos - m_PrevCameraLeftTopPos; }

	void SetCameraLeftTopPos(Vec2 _pos) { m_CameraLeftTopPos = _pos; }
	void SetCameraEffect(CAM_EFFECT _effect, float _duration);
	void SetCameraInitialLookAt(Vec2 _pos);
	void SetCameraLookAt(Vec2 _pos);
	void SetTrackingState(CAM_TRACKING_STATE _state, Vec2 _stageRange = Vec2(0, 0)) { m_bTrackingState = _state; m_StageRange = _stageRange; }

	void SetPlayerToCamera(CPlayer* _player) { m_Player = _player; }

public:
	void init();
	void tick();
	void CameraEffectRender();

public:
	CCamera();
	~CCamera();

};

