#pragma once
#include "CComponent.h"

enum class DATA_TYPE
{
    INT,
    FLOAT,
    VEC2,
    OBJ_PTR
};

struct tBlackboardData
{
    DATA_TYPE   Type;
    void*       pData;
};

class CState;

class CFSM :
    public CComponent
{
private:
    static map<wstring, tBlackboardData>    m_mapGlobalData;    // 전역데이터

private:
    map<wstring, tBlackboardData>           m_mapData;          // 각 객체가 가지는 데이터
    map<wstring, CState*>                   m_mapState;         // 상태들
    CState*                                 m_CurState;         // 현재 상태

public:
    void AddState(const wstring& _strStateName, CState* _state);
    CState* FindState(const wstring& _strStateName);
    void ChangeState(const wstring& _strNextStateName);
    void SetBlackboardData(const wstring& _DataKey, DATA_TYPE _Type, void* _pData);

    template<typename T>
    T GetBlackboardData(const wstring& _DataKey);

public:
    virtual void finaltick() override;

public:
    CLONE(CFSM);
    CFSM();
    ~CFSM();
};

template<typename T>
inline T CFSM::GetBlackboardData(const wstring& _DataKey)
{
    map<wstring, tBlackboardData>::iterator iter = m_mapData.find(_DataKey);

    assert(iter != m_mapData.end());

    if (std::is_same_v<int, T>)
    {
        assert(DATA_TYPE::INT == iter->second.Type);
        return *((T*)iter->second.pData);
    }

    if (std::is_same_v<float, T>)
    {
        assert(DATA_TYPE::FLOAT == iter->second.Type);
        return *((T*)iter->second.pData);
    }

    if (std::is_same_v<Vec2, T>)
    {
        assert(DATA_TYPE::VEC2 == iter->second.Type);
        return *((T*)iter->second.pData);
    }

    if constexpr (std::is_same_v<CObj*, T>)
    {
        assert(DATA_TYPE::OBJ_PTR == iter->second.Type);
        return (T)iter->second.pData;
    }
}