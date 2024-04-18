#pragma once
#include "CObj.h"
class Z_Button :
    public CObj
{
private:
    CTexture* m_ButtonTex;

    CObj* m_WorldmapPlayer;

public:
    void SetWorldmapPlayer(CObj* _worldmapPlayer) { m_WorldmapPlayer = _worldmapPlayer; }

public:
    virtual void render() override;

    // Clone »ç¿ë X
    virtual Z_Button* Clone() { return nullptr; }

public:
    Z_Button();
    ~Z_Button();
};

