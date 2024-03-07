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
void Safe_Del_Arr(T* (&arr)[arr_size])
{
	for (auto &e : arr)
	{
		if (e == nullptr)
			continue;
		delete e;
		e = nullptr;
	}
}


