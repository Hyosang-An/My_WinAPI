#pragma once
#include "CObj.h"
class CEffect :
    public CObj
{
private:
    CObj*   m_ParentObj;
    Vec2    m_OffsetPos;

    wstring m_AnimName;

    bool    m_bRepeat = false;

public:
    void SetAnimation(const wstring& _strRelativeAnimFilePath, bool _repeat = false);
    void SetParentAndOffset(CObj* _parent, Vec2 _offset);
    void PlayEffect();

public:
    virtual void begin();
    virtual void tick();

    virtual CEffect* Clone() override { return new CEffect(*this); }
public:
    CEffect();
    CEffect(const CEffect& _other);
    ~CEffect();
};

