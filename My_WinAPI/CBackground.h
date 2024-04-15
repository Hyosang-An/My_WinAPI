#pragma once
#include "CObj.h"

enum class BACKGROUND_DEPTH
{
    Fore,
    Middle,
    Far
};

class CBackground :
    public CObj
{
protected:
    CTexture* m_Texture;

    BACKGROUND_DEPTH m_Depth = BACKGROUND_DEPTH::Fore;

public:
    void SetTexture(CTexture* _texture) { m_Texture = _texture; }
    void SetAnimation(const wstring& strRelativeAnimPath, bool _RepeatReverse = false);
    void SetDepth(BACKGROUND_DEPTH _depth) { m_Depth = _depth; }

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

    virtual CBackground* Clone() { return new CBackground(*this); }

public:
    CBackground();
    ~CBackground();
};

