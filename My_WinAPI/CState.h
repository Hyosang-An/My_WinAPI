#pragma once
#include "CEntity.h"

#include "CFSM.h"

class CState :
    public CEntity
{
    friend class CFSM;
private:
    CFSM* m_pOwnerFSM;

protected:
    CObj* GetObj() { return m_pOwnerFSM->GetOwner(); }
    CFSM* GetFSM() { return m_pOwnerFSM; }

    template<typename T>
    T GetBlackboardData(const wstring& _DataName)
    {
        return m_pOwnerFSM->GetBlackboardData<T>(_DataName);
    }

public:
    virtual void Enter() = 0; // 상태 진입 시 할 일
    virtual void finaltick() = 0; // 상태를유지하고 있을 때 할 일
    virtual void Exit() = 0; // 상태를 벗어날 때 할 일

    virtual CState* Clone() = 0;

public:
    CState();
    ~CState();

};

