#pragma once
#include "Singleton.h"

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
    float       m_CamSpeed = 500;
    list<CAM_EFFECT_INFO>   m_listEffect;

    CTexture* m_FadeTex;
    CTexture* m_RedTex;

private:
    void Move();
    void CameraEffect();

public:
    Vec2 GetRenderPos(Vec2 _realPos) { return _realPos - m_CameraLeftTopPos; }
    Vec2 GetRealPos(Vec2 _renderPos) { return _renderPos + m_CameraLeftTopPos; }

    void SetCameraLeftTopPos(Vec2 _pos) { m_CameraLeftTopPos = _pos; }
    void SetCameraEffect(CAM_EFFECT _effect, float _duration);

public:
    void init();
    void tick();
    void render();

public:
    CCamera();
    ~CCamera();

};

