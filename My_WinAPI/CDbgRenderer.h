#pragma once

#include "Singleton.h"

enum class DBG_SHAPE
{
	CIRCLE,
	RECT
};

struct tDbgRenderInfo
{
	DBG_SHAPE	Shape;
	Vec2		Position;
	Vec2		Scale;
	PEN_TYPE	Color;

	float		Duration;
	float		Age;
};

class CDbgRenderer :
	public Singleton<CDbgRenderer>
{
	friend Singleton<CDbgRenderer>;

private:
	list<tDbgRenderInfo>	m_RenderList;
	bool					m_bRender;

public:
	void AddDbgRenderInfo(const tDbgRenderInfo& _info)
	{
		m_RenderList.push_back(_info);
	}

	void tick();
	void render();

private:
	CDbgRenderer();
	~CDbgRenderer();
};

inline void DrawDebugRect(PEN_TYPE _Type, Vec2 _Pos, Vec2 _Scale, float _Time)
{
#ifdef _DEBUG
	tDbgRenderInfo info{};
	info.Shape = DBG_SHAPE::RECT;
	info.Color = _Type;
	info.Position = _Pos;
	info.Scale = _Scale;
	info.Duration = _Time;
	info.Age = 0.f;

	CDbgRenderer::GetInstance().AddDbgRenderInfo(info);
#endif
}

inline void DrawDebugCircle(PEN_TYPE _Type, Vec2 _Pos, Vec2 _Scale, float _Time)
{
#ifdef _DEBUG
	tDbgRenderInfo info{};
	info.Shape = DBG_SHAPE::CIRCLE;
	info.Color = _Type;
	info.Position = _Pos;
	info.Scale = _Scale;
	info.Duration = _Time;
	info.Age = 0.f;

	CDbgRenderer::GetInstance().AddDbgRenderInfo(info);
#endif
}

