#pragma once

template <typename T> 
class Singleton
{
public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}

	Singleton(const Singleton& _other) = delete;
	Singleton& operator= (const Singleton& _other) = delete;

protected:
	Singleton() {}
	virtual ~Singleton() {}
};