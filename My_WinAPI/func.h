#pragma once

template<typename T>
inline void Safe_Del_Vec(vector<T*>& _vec)
{
	for (auto &e : _vec)
	{
		if (e == nullptr)
			continue;
		delete e;
	}

	_vec.clear();
}

template<typename T, size_t arr_size>
inline void Safe_Del_Arr(T* (&arr)[arr_size])
{
	for (auto &e : arr)
	{
		if (e == nullptr)
			continue;
		delete e;
		e = nullptr;
	}
}

template<typename T1, typename T2>
inline void Safe_Del_Map(map<T1, T2>& _map)
{
	for (const auto& _pair : _map)
	{
		if (_pair.second != nullptr)
			delete _pair.second;
	}

	_map.clear();
}

// =============
// Task 관련 함수

class CLevel;
class CObj;

void SpawnObject(CLevel* _Level, LAYER_TYPE _type, CObj* _pSpawned);
void ChangeLevel(LEVEL_TYPE _NextLevelType);
// =============
