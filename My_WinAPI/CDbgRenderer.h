#pragma once

#include "Singleton.h"

enum class DBG_SHAPE
{
	CIRCLE,
	RECT,
	LINE
};

struct tDbgRenderInfo
{
	DBG_SHAPE	Shape;
	Vec2		Position;
	Vec2		Scale;
	PEN_TYPE	Color;

	float		fDuration;
	float		fElapsedTime;
};

struct tDbgLog
{
	LOG_TYPE	Type;
	wstring		strLog;
	float		fElapsedTime;
};

class CDbgRenderer :
	public Singleton<CDbgRenderer>
{
	friend Singleton<CDbgRenderer>;

private:
	list<tDbgRenderInfo>	m_RenderList;
	list<tDbgLog>			m_LogList;
	bool					m_bRender;

	float					m_LogDuration;	// 로그 지속시간
	int						m_LogSpace;		// 로그 줄간격
	Vec2					m_LogPos;		// 로그 위치

public:
	void AddDbgRenderInfo(const tDbgRenderInfo& _info);
	void AddDbgLog(const tDbgLog _tDbgLog);

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
	info.fDuration = _Time;
	info.fElapsedTime = 0.f;

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
	info.fDuration = _Time;
	info.fElapsedTime = 0.f;

	CDbgRenderer::GetInstance().AddDbgRenderInfo(info);
#endif
}

inline void DrawDebugLine(PEN_TYPE _Type, Vec2 _LineStartPos, Vec2 _LineEndPos, float _Time)
{
#ifdef _DEBUG
	tDbgRenderInfo info{};
	info.Shape = DBG_SHAPE::LINE;
	info.Color = _Type;
	info.Position = _LineStartPos;
	info.Scale = _LineEndPos;
	info.fDuration = _Time;
	info.fElapsedTime = 0.f;

	CDbgRenderer::GetInstance().AddDbgRenderInfo(info);
#endif
}