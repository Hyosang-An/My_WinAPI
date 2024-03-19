#pragma once

struct Vec2
{
public:
	float x;
	float y;

public:
	bool IsZero()
	{
		return x == 0.f && y == 0.f;
	}

	float GetDistanceWith(Vec2 _other)
	{
		// vector 라이브러리에 sqrtf 포함
		return sqrtf((x - _other.x) * (x - _other.x) + (y - _other.y) * (y - _other.y));
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	void Normalize()
	{
		// 크기가 0인 벡터를 정규화 하는 것에 대한 예외처리
		assert(!IsZero());

		float fLen = Length();
		x /= fLen;
		y /= fLen;
	}

	Vec2 operator +(float f) { return Vec2(x + f, y + f); }
	Vec2 operator -(float f) { return Vec2(x - f, y - f); }
	Vec2 operator *(float f) { return Vec2(x * f, y * f); }
	Vec2 operator /(float f) { assert(f); return Vec2(x / f, y / f); }

	Vec2 operator + (Vec2 _Other) { return Vec2(x + _Other.x, y + _Other.y); }
	Vec2 operator - (Vec2 _Other) { return Vec2(x - _Other.x, y - _Other.y); }
	Vec2 operator * (Vec2 _Other) { return Vec2(x * _Other.x, y * _Other.y); }
	Vec2 operator / (Vec2 _Other) { assert(!(0.f == _Other.x || 0.f == _Other.y)); return Vec2(x / _Other.x, y / _Other.y); }

	void operator +=(float _f)
	{
		x += _f;
		y += _f;
	}

	void operator +=(Vec2 _Other)
	{
		x += _Other.x;
		y += _Other.y;
	}

	void operator -=(float _f)
	{
		x -= _f;
		y -= _f;
	}

	void operator -=(Vec2 _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
	}

	void operator *=(float _f)
	{
		x *= _f;
		y *= _f;
	}

	void operator *=(Vec2 _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
	}

	void operator /=(float _f)
	{
		assert(_f);

		x /= _f;
		y /= _f;
	}

	void operator /=(Vec2 _Other)
	{
		assert(_Other.x && _Other.y);

		x /= _Other.x;
		y /= _Other.y;
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

	~Vec2()
	{}
};

inline Vec2 operator*(float f, const Vec2& vec) 
{
	return Vec2(f * vec.x, f * vec.y);
}