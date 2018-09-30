#pragma once
#include "source\system\Core.h"
#include <DirectXMath.h>

namespace Yukitter
{

	struct Vector2D
	{
	public:
		float x;
		float y;
	public:
		F_INLINE Vector2D(float in_x, float in_y) :
			x(in_x),
			y(in_y) {}
		F_INLINE Vector2D() :
			x(0),
			y(0) {}
		F_INLINE Vector2D(float in_float) :
			x(in_float),
			y(in_float) {}


		//	オペレーター
		F_INLINE Vector2D& operator =  (const Vector2D& v) { x = v.x; y = v.y;  return *this; }
		F_INLINE Vector2D& operator += (const Vector2D& v) { x += v.x; y += v.y;  return *this; }
		F_INLINE Vector2D& operator -= (const Vector2D& v) { x -= v.x; y -= v.y;  return *this; }
		F_INLINE Vector2D& operator *= (float v) { x *= v; y *= v;  return *this; }
		F_INLINE Vector2D& operator /= (float v) { x /= v; y /= v;  return *this; }

		F_INLINE Vector2D operator + (const Vector2D& v) const { return Vector2D(x + v.x, y + v.y); }
		F_INLINE Vector2D operator - (const Vector2D& v) const { return Vector2D(x - v.x, y - v.y); }
		F_INLINE Vector2D operator * (float v) const { Vector2D ret(x*v, y*v); return ret; }
		F_INLINE Vector2D operator / (float v) const { Vector2D ret(x / v, y / v); return ret; }

		F_INLINE bool operator == (const Vector2D& v) const { return (x == v.x) && (y == v.y); }
		F_INLINE bool operator != (const Vector2D& v) const { return (x != v.x) || (y != v.y); }

		F_INLINE Vector2D operator + (const DirectX::XMFLOAT2& v) const { return Vector2D(x + v.x, y + v.y); }
		F_INLINE Vector2D operator - (const DirectX::XMFLOAT2& v) const { return Vector2D(x - v.x, y - v.y); }
		F_INLINE Vector2D& operator =  (const DirectX::XMFLOAT2& v) { x = v.x; y = v.y; return *this; }

		F_INLINE float Length() { return sqrtf(x*x + y*y); }
		F_INLINE float LengthSq() { return x*x + y*y; }

	};

}