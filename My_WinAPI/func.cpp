#include "pch.h"
#include "func.h"
#include "CLevelMgr.h"

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

void SpawnObject(LAYER_TYPE _type, CObj* _pSpawned)
{
	tTask task{};
	task.eType = TASK_TYPE::SPAWN_OBJECT;
	task.param1 = reinterpret_cast<DWORD_PTR>(CLevelMgr::GetInstance().GetCurrentLevel());
	task.param2 = static_cast<DWORD_PTR>(_type);
	task.param3 = reinterpret_cast<DWORD_PTR>(_pSpawned);

	CTaskMgr::GetInstance().AddTask(task);

}

void ChangeLevel(LEVEL_TYPE _NextLevelType)
{
    tTask task{};
    task.eType = TASK_TYPE::CHANGE_LEVEL;
    task.param1 = (DWORD_PTR)_NextLevelType;

    CTaskMgr::GetInstance().AddTask(task);
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
    _str.clear();

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

wstring ExtractFileName(const wstring& fullPath)
{
    // 파일 이름이 시작되는 위치 찾기 (마지막 '\\'의 다음 위치)
    size_t lastSlashPos = fullPath.find_last_of(L"\\");
    if (lastSlashPos == std::wstring::npos) {
        // '\\'가 없다면, fullPath가 이미 파일 이름일 수 있음
        lastSlashPos = 0;
    }
    else {
        // 파일 이름만 추출하기 위해 lastSlashPos을 1 증가
        lastSlashPos++;
    }

    // 파일 이름 추출 (확장자 포함)
    std::wstring fileNameWithExt = fullPath.substr(lastSlashPos);

    // 확장자 제거하기 위해 마지막 '.'의 위치 찾기
    size_t lastDotPos = fileNameWithExt.find_last_of(L".");
    if (lastDotPos == std::wstring::npos) {
        // '.'가 없다면, 확장자가 없는 경우임
        return fileNameWithExt;
    }

    // 확장자 제거한 순수 파일 이름 반환
    return fileNameWithExt.substr(0, lastDotPos);
}