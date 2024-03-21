#include "pch.h"
#include "func.h"

bool IsValid(CObj* _pObj)
{
	if (_pObj == nullptr)
		return false;
	else if (_pObj->IsDead())
	{
		_pObj = nullptr;
		return false;
	}

	return true;
}

void SpawnObject(CLevel* _Level, LAYER_TYPE _type, CObj* _pSpawned)
{
	tTask task{};
	task.eType = TASK_TYPE::SPAWN_OBJECT;
	task.param1 = reinterpret_cast<DWORD_PTR>(_Level);
	task.param2 = static_cast<DWORD_PTR>(_type);
	task.param3 = reinterpret_cast<DWORD_PTR>(_pSpawned);

	CTaskMgr::GetInstance().AddTask(task);

}

void ChangeLevel(LEVEL_TYPE _NextLevelType)
{
}

int SaveWStringToFile(_In_ const wstring& _str, _Inout_ FILE* _pFile)
{
    size_t len = _str.length();
    if (fwrite(&len, sizeof(size_t), 1, _pFile) != 1 ||
        fwrite(_str.c_str(), sizeof(wchar_t), len, _pFile) != len)
    {
        return E_FAIL; // 파일 쓰기 실패
    }

    return S_OK;
}

int LoadWStringFromFile(_Out_ std::wstring& _str, _Inout_ FILE* _pFile)
{
    size_t len = 0;
    if (fread(&len, sizeof(size_t), 1, _pFile) != 1)
    {
        return E_FAIL; // 길이 읽기 실패
    }

    _str.resize(len);

    if (fread(_str.data(), sizeof(wchar_t), len, _pFile) != len)
    {
        return E_FAIL; // 문자열 읽기 실패
    }

    return S_OK;
}


