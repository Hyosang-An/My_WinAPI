#pragma once
#include "CComponent.h"

class CAnimation;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnimation;
    CAnimation*                 m_CurAnimation;

    bool                        m_bRepeat;

public:
    virtual void finaltick() override;
    
    void render();

    CAnimation* CreateAnimation(const wstring& _AnimName, CTexture* _Atlas, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS);

    CAnimation* FindAnimation(const wstring& _AnimName);
    void LoadAnimation(wstring _strRelativeFilePath);

    void Play(const wstring& _AnimName, bool _Repeat);

    CLONE(CAnimator)

public:
    CAnimator();
    ~CAnimator();
};

