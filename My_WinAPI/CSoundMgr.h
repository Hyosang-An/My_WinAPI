#pragma once

#include "Singleton.h"

class CSound;

class CSoundMgr :
    public Singleton<CSoundMgr>
{
    friend Singleton<CSoundMgr>;

private:
    LPDIRECTSOUND8  m_pSound;       // ����ī�� ����
    CSound*         m_pBGM;         // BGM Sound

public:
    int init();
    LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
    void RegisterToBGM(CSound* _pSound);

private:
    CSoundMgr();
    ~CSoundMgr();
};

