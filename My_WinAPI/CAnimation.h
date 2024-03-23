#pragma once
#include "CEntity.h"

class CAnimator;
class CTexture;

struct tAnimationFrame
{
    Vec2    PosInAtlas;
    Vec2    SliceSize;
    Vec2    Offset;
    float   fDuration;
};

class CAnimation :
    public CEntity
{
	friend class CAnimator;

private:
	CAnimator*					m_Animator;				// Animation을 소유하고 있는 Animator
	CTexture*					m_Atlas;				// Animation 이미지를 보유하고 있는 Atlas Texture
	vector<tAnimationFrame>		m_vecAnimFrame;	// 각 프레임 정보를 담은 벡터

	float						m_frameElapsedTime;			// 애니메이션 재생 시간
	int							m_CurFrameIdx;			// 현재 프레임 인덱스
	bool						m_bFinished;			// 애니메이션 재생이 종료됨을 알림

public:
	bool IsFinished() { return m_bFinished; }
	tAnimationFrame& GetFrame(int _idx) { return m_vecAnimFrame[_idx]; }

	void Reset();
	void SetAtlasTexture(CTexture* _atlas) { m_Atlas = _atlas; }

public:
	void finaltick();
	void render();
	void Create(CTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS);
	void CreateAnimationFrame(Vec2 _PosInAtlas, Vec2 _SliceSize, float _fDuration);

	void Save(wstring _strRelativePath);
	int	Load(const wstring& _strRelativePath);

	void Save2(const wstring& _strRelativeFolderPath);
	int	Load2(const wstring& _strRelativeFilePath);

	CLONE(CAnimation)

public:
	CAnimation();
	~CAnimation();

};

