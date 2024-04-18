#pragma once
#include "CObj.h"
class CStage_Title_Card :
    public CObj
{
private:
    CTexture* m_FadeTex;
    CTexture* m_PanelTex;
    CTexture* m_TitleTex;
    
public:
    void SetTitleTex(wstring _title_name);

    virtual void render();

    // Clone »ç¿ë X
    virtual CStage_Title_Card* Clone() { return nullptr; }

public:
    CStage_Title_Card();
    ~CStage_Title_Card();
};

