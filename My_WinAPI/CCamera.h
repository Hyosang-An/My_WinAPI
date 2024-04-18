#pragma once
#include "Singleton.h"

class CPlayer;
class Worldmap_Player;

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
	WORLD_MAP,
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
	Worldmap_Player* m_Worldmap_Player;


	float       m_CamSpeed = 500;
	list<CAM_EFFECT_INFO>   m_listEffect;

	CTexture* m_FadeTex;
	CTexture* m_RedTex;

	// Screen FX
	vector<CTexture*>	m_vecScreenFX;
	float				m_ScreenFXframeElapsedTime = 0;		// Screen FX 텍스쳐 재생 시간
	float				m_ScreenFXframeDuration = 0.08f;
	int					m_CurScreenFXFrameIdx = 0;			// 현재 프레임 인덱스
	bool				m_bScreenFXFinished = false;			// Screen FX 재생이 종료됨을 알림

	CAM_TRACKING_STATE    m_bTrackingState = CAM_TRACKING_STATE::NONE;

	// !디버깅
	Vec2 m_diff;

private:
	void Move();
	void UpdateCameraEffect();
	void TrackingPlayer_Worldmap();
	void TrackingPlayer_RunAndGunStage();
	void TrackingPlayer_BossStage();


public:
	Vec2 GetRenderPos(Vec2 _realPos) { return _realPos - m_CameraLeftTopPos; }
	Vec2 GetRealPos(Vec2 _renderPos) { return _renderPos + m_CameraLeftTopPos; }
	Vec2 GetLeftTopPos() { return m_CameraLeftTopPos; }

	CTexture* GetFadeTexture() { return m_FadeTex; }

	Vec2 GetCameraDeltaPos() { return m_CameraLeftTopPos - m_PrevCameraLeftTopPos; }

	void SetCameraLeftTopPos(Vec2 _pos) { m_CameraLeftTopPos = _pos; }
	void SetCameraEffect(CAM_EFFECT _effect, float _duration);
	void SetCameraInitialLookAt(Vec2 _pos);
	void SetCameraLookAt(Vec2 _pos);
	void SetTrackingState(CAM_TRACKING_STATE _state, Vec2 _stageRange = Vec2(0, 0)) { m_bTrackingState = _state; m_StageRange = _stageRange; }

	void SetPlayerToCamera(CPlayer* _player) { m_Player = _player; }
	void SetWorldmapPlayerToCamera(Worldmap_Player* _player) { m_Worldmap_Player = _player; }

public:
	void init();
	void tick();
	void CameraEffectRender();

public:
	CCamera();
	~CCamera();

};

