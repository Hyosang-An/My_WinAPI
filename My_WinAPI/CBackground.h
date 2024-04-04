#pragma once
#include "CObj.h"
class CBackground :
    public CObj
{
private:
    CTexture* m_Texture;

public:
    void SetTexture(CTexture* _texture) { m_Texture = _texture; }

public:
    virtual void render() override;

    // Ŭ�� ������� ����
    virtual CBackground* Clone() { return nullptr; }

public:
    CBackground();
    ~CBackground();
};

