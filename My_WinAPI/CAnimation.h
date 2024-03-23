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
	CAnimator*					m_Animator;				// Animation�� �����ϰ� �ִ� Animator
	CTexture*					m_Atlas;				// Animation �̹����� �����ϰ� �ִ� Atlas Texture
	vector<tAnimationFrame>		m_vecAnimFrame;	// �� ������ ������ ���� ����

	float						m_frameElapsedTime;			// �ִϸ��̼� ��� �ð�
	int							m_CurFrameIdx;			// ���� ������ �ε���
	bool						m_bFinished;			// �ִϸ��̼� ����� ������� �˸�

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

	void Save(const wstring& _strRelativeFolderPath);
	int	Load(const wstring& _strRelativeFilePath);

	CLONE(CAnimation)

public:
	CAnimation();
	~CAnimation();

};

