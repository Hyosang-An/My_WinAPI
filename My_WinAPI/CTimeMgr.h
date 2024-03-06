#pragma once
#include "Singleton.h"
class CTimeMgr :
    public Singleton<CTimeMgr>
{
    friend Singleton<CTimeMgr>;

private:
    // LARGE_INTEGER - 8바이트 정수 대용
    LARGE_INTEGER   m_llCurCount;
    LARGE_INTEGER   m_llPrevCount;
    LARGE_INTEGER   m_llFrequency;

    UINT            m_FPS;

    double      m_DeltaTime;    // 프레임 시간 간격
    double      m_Time;         // 프로그램이 켜진 이후로 진행된 시간

public:
    void init();
    void tick();

private:
    CTimeMgr();
    ~CTimeMgr();
};

