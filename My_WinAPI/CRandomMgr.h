#pragma once
#include "Singleton.h"

#include <random>

class CRandomMgr :
    public Singleton<CRandomMgr>
{
    friend Singleton<CRandomMgr>;

private:
    std::mt19937 gen;

public:
    void init(); 

    float GetRandomFloat_from_UniformDist(float _min, float _max);
    int GetRandomInt_from_UniformDist(int _min, int _max);
    bool GetRandomBool(float _pobability);

private:
    CRandomMgr();
    ~CRandomMgr();
};

