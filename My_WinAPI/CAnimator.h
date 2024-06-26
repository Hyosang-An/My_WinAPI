#pragma once
#include "CComponent.h"

#include "CAnimation.h"

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

    void CreateAndSaveAnimationFileByJSON(std::wstring strRelativeJsonFilePath, int _FPS);

    CAnimation* FindAnimation(const wstring& _AnimName);
    CAnimation* LoadAnimation(wstring _strRelativeAnimFilePath);

    void Play(const wstring& _AnimName, bool _Repeat, bool _RepeatReverse = false);

    void PlayFromFrame(const wstring& _AnimName, bool _Repeat, int _frameIdx);

    CAnimation* GetCurAnimation() { return m_CurAnimation; }
    int GetCurAnimationFrmIdx() { return m_CurAnimation->GetCurFrameIdx(); }
    bool IsCurAnimationFinished();

public:
    CAnimator();
    CAnimator(const CAnimator& _other);
    ~CAnimator();
};

