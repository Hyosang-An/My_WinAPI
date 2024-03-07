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

    float      m_DeltaTime;    // ������ �ð� ����
    float      m_Time;         // ���α׷��� ���� ���ķ� ����� �ð�

public:
    void init();
    void tick();

    float  GetDeltaTime() { return m_DeltaTime; }
    float  GetTime() { return m_Time; }
    UINT    GetFPS() { return m_FPS; }

private:
    CTimeMgr();
    ~CTimeMgr();
};

