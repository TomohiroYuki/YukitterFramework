#pragma once
#include "source\system\Core.h"
#include <DirectXMath.h>

namespace Yukitter 
{

	struct Vector
	{
	public:

		float x;
		float y;
		float z;

	public:

		F_INLINE Vector() :
			x(0), y(0), z(0){}

		F_INLINE Vector(float x,float y,float z) :
			x(x), y(y), z(z){}

		F_INLINE Vector(float in_f) :
			x(in_f), y(in_f), z(in_f) {}

		F_INLINE Vector(DirectX::XMFLOAT3 in_v) :
			x(in_v.x), y(in_v.y), z(in_v.z) {}


		//	オペレーター
		F_INLINE Vector& operator =  (const Vector& v) { x = v.x; y = v.y; z = v.z; return *this; }
		F_INLINE Vector& operator += (const Vector& v) { x += v.x; y += v.y; z += v.z; return *this; }
		F_INLINE Vector& operator -= (const Vector& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		F_INLINE Vector& operator *= (float v) { x *= v; y *= v; z *= v; return *this; }
		F_INLINE Vector& operator /= (float v) { x /= v; y /= v; z /= v; return *this; }

		F_INLINE Vector operator + (const Vector& v) const { return Vector(x + v.x, y + v.y, z + v.z); }
		F_INLINE Vector operator - (const Vector& v) const { return Vector(x - v.x, y - v.y, z - v.z); }
		F_INLINE Vector operator * (float v) const { Vector ret(x*v, y*v, z*v); return ret; }
		F_INLINE Vector operator / (float v) const { Vector ret(x / v, y / v, z / v); return ret; }

		F_INLINE bool operator == (const Vector& v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
		F_INLINE bool operator != (const Vector& v) const { return (x != v.x) || (y != v.y) || (z != v.z); }

		F_INLINE Vector operator + (const DirectX::XMFLOAT3& v) const { return Vector(x + v.x, y + v.y, z + v.z); }
		F_INLINE Vector operator - (const DirectX::XMFLOAT3& v) const { return Vector(x - v.x, y - v.y, z - v.z); }
		F_INLINE Vector& operator =  (const DirectX::XMFLOAT3& v) { x = v.x; y = v.y; z = v.z; return *this; }
	


		F_INLINE float Length() { return sqrtf(x*x + y*y + z*z); }
		F_INLINE float LengthSq() { return x*x + y*y + z*z; }

		F_INLINE Vector GetNormalize()
		{
			Vector copy(x, y, z);
			float l = Length();
			return l != .0f ? Vector(copy.x / l, copy.y / l, copy.z / l) : Vector();
		}




	};

	F_INLINE float Absolute(float in_f)
	{
		return in_f > 0 ? in_f : -1 * in_f;
	}

}