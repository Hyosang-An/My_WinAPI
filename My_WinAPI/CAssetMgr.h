#pragma once
#include "Singleton.h"
class CAssetMgr :
    public Singleton<CAssetMgr>
{
    friend Singleton<CAssetMgr>;

private:
    CAssetMgr();
    ~CAssetMgr();
};

