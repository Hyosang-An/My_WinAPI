#pragma once
#include "Singleton.h"
class CTimeMgr :
    public Singleton<CTimeMgr>
{
    friend Singleton<CTimeMgr>;

private:
    // LARGE_INTEGER - 8����Ʈ ���� ���
    LARGE_INTEGER   m_llCurCount;
    LARGE_INTEGER   m_llPrevCount;
    LARGE_INTEGER   m_llFrequency;

    UINT            m_FPS;

    double      m_DeltaTime;    // ������ �ð� ����
    double      m_Time;         // ���α׷��� ���� ���ķ� ����� �ð�

public:
    void init();
    void tick();

private:
    CTimeMgr();
    ~CTimeMgr();
};

