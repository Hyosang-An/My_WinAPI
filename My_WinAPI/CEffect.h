#pragma once
#include "CObj.h"
class CEffect :
    public CObj
{
private:
    CObj*   m_ParentObj;
    Vec2    m_OffsetPos;

public:
    void SetAnimation(const wstring& _strRelativeAnimFilePath);
    void SetParentAndOffset(CObj* _parent, Vec2 _offset);
    void PlayEffect();

public:
    virtual void tick();

    virtual CEffect* Clone() override { return new CEffect(*this); }
public:
    CEffect();
    CEffect(const CEffect& _other);
    ~CEffect();
};

