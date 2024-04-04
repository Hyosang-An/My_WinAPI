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

class CTexture;

class CCamera :
    public Singleton<CCamera>
{
    friend Singleton<CCamera>;

private:
    Vec2        m_CameraLeftTopPos;
    Vec2        m_CameraRealCenterPos;

    CPlayer* m_Player;

    float       m_CamSpeed = 500;
    list<CAM_EFFECT_INFO>   m_listEffect;

    CTexture* m_FadeTex;
    CTexture* m_RedTex;

private:
    void Move();
    void CameraEffect();

    float diff_x;

public:
    Vec2 GetRenderPos(Vec2 _realPos) { return _realPos - m_CameraLeftTopPos; }
    Vec2 GetRealPos(Vec2 _renderPos) { return _renderPos + m_CameraLeftTopPos; }

    void SetCameraLeftTopPos(Vec2 _pos) { m_CameraLeftTopPos = _pos; }
    void SetCameraEffect(CAM_EFFECT _effect, float _duration);

    void SetPlayerToCamera(CPlayer* _player) { m_Player = _player; }

public:
    void init();
    void tick();
    void CameraEffectRender();

public:
    CCamera();
    ~CCamera();

};

