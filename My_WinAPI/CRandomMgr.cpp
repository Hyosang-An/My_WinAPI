#include "pch.h"
#include "CRandomMgr.h"

CRandomMgr::CRandomMgr()
{
}

CRandomMgr::~CRandomMgr()
{
}

void CRandomMgr::init()
{
	std::random_device rd; // 하드웨어 기반 난수 생성기
	gen = std::mt19937(rd()); //메르센 트위스터 엔진, 초기화에 random_device 사용
}

float CRandomMgr::GetRandomFloat_from_UniformDist(float _min, float _max)
{
	std::uniform_real_distribution<float> dis(_min, _max);
	return dis(gen);
}

int CRandomMgr::GetRandomInt_from_UniformDist(int _min, int _max)
{
	std::uniform_int_distribution<> dis(_min, _max);
	return dis(gen);
}

bool CRandomMgr::GetRandomBool(float _probability)
{
	if (_probability > 1 || _probability < 0)
	{
		std::wstring message = L"잘못된 확률 : " + std::to_wstring(_probability);
		MessageBox(NULL, message.c_str(), L"Error", MB_ICONERROR | MB_OK);
		return false;
	}

	std::bernoulli_distribution dis(_probability);
	
	return dis(gen);
}

