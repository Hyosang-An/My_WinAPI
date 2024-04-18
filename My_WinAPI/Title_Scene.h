#pragma once
#include "CLevel.h"
class Title_Scene :
    public CLevel
{
private:
    CTexture*           m_TitleBG;


    // Title Anim
    vector<CTexture*>   m_vecTitleAnim;
    float				m_TitleAnimframeElapsedTime = 0;		// Screen FX 텍스쳐 재생 시간
    float				m_TitleAnimframeDuration = 0.08f;
    int					m_CurTitleAnimFrameIdx = 0;			// 현재 프레임 인덱스
    bool				m_bTitleAnimFinished = false;			// Screen FX 재생이 종료됨을 알림

public:
    virtual void tick();
    virtual void render();

    virtual void LoadBackground() {}
    virtual void LoadObject() {}
    virtual void SetCollision() {}

    virtual void Enter();
    virtual void Exit();

public:
    Title_Scene();
    ~Title_Scene();
};

