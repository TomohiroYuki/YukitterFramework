#pragma once
#include <cmath>
#include <DirectXMath.h>
const float G_ACCEL_P_60F = 9.80665f / 60.0f;
const float PI = 3.14159265f;

struct VECTORIV
{
	float x, y, z, w;//r,g,b,a
	//	コンストラクタ
	VECTORIV() :
		x(.0f),
		y(.0f),
		z(.0f),
		w(.0f)
	{};
	inline VECTORIV(float x, float y, float z, float w) { this->x = x, this->y = y, this->z = z; this->w = w; }


	//	距離計算
	inline float Length() { return sqrtf(x*x + y*y + z*z); }//sqrtfあり
	inline float LengthSq() { return x*x + y*y + z*z; }

	//	正規化
	void Normalize()
	{
		float l = Length();
		if (l != .0f) { x /= l; y /= l; z /= l; }
	}

	//	オペレーター
	inline VECTORIV& operator =  (const VECTORIV& v) { x = v.x; y = v.y; z = v.z; return *this; }
	inline VECTORIV& operator += (const VECTORIV& v) { x += v.x; y += v.y; z += v.z; return *this; }
	inline VECTORIV& operator -= (const VECTORIV& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	inline VECTORIV& operator *= (float v) { x *= v; y *= v; z *= v; return *this; }
	inline VECTORIV& operator /= (float v) { x /= v; y /= v; z /= v; return *this; }

	inline VECTORIV operator + (const VECTORIV& v) const { return VECTORIV(x + v.x, y + v.y, z + v.z, w + v.w); }
	inline VECTORIV operator - (const VECTORIV& v) const { return VECTORIV(x - v.x, y - v.y, z - v.z, w - v.w); }
	inline VECTORIV operator * (float v) const { VECTORIV ret(x*v, y*v, z*v, w*v); return ret; }
	inline VECTORIV operator / (float v) const { VECTORIV ret(x / v, y / v, z / v, w / v); return ret; }

	bool operator == (const VECTORIV& v) const { return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w); }
	bool operator != (const VECTORIV& v) const { return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w); }

	inline VECTORIV& operator =  (const unsigned long& dword) { x = static_cast<float>(dword); y = static_cast<float>(dword); z = static_cast<float>(dword); w = static_cast<float>(dword); return *this; }


};




struct VECTORIII
{
	float x, y, z;
	//	コンストラクタ
	VECTORIII() :
		x(0),
		y(0),
		z(0)
	{};
	inline VECTORIII(float x, float y, float z) { this->x = x, this->y = y, this->z = z; }
	inline VECTORIII(DirectX::XMFLOAT3 v) { this->x = v.x, this->y = v.y, this->z = v.z; }


	//	距離計算
	inline float Length() { return sqrtf(x*x + y*y + z*z); }
	inline float LengthSq() { return x*x + y*y + z*z; }

	//	正規化
	/*void Normalize()
	{
		float l = Length();
		if (l != .0f) { x /= l; y /= l; z /= l; }
	}*/

	inline void Normalize()
	{

		float l = Length();
		if (l != .0f)
		{
			x /= l;
			y /= l;
			z /= l;;
		}

	}
	inline VECTORIII GetNormalize()
	{
		VECTORIII copy(x, y, z);
		float l = Length();
		if (l != .0f)
		{
			return VECTORIII(copy.x / l, copy.y / l, copy.z / l);
		}
		else
		{
			return VECTORIII();
		}
	}


	//	オペレーター
	inline VECTORIII& operator =  (const VECTORIII& v) { x = v.x; y = v.y; z = v.z; return *this; }
	inline VECTORIII& operator += (const VECTORIII& v) { x += v.x; y += v.y; z += v.z; return *this; }
	inline VECTORIII& operator -= (const VECTORIII& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	inline VECTORIII& operator *= (float v) { x *= v; y *= v; z *= v; return *this; }
	inline VECTORIII& operator /= (float v) { x /= v; y /= v; z /= v; return *this; }

	inline VECTORIII operator + (const VECTORIII& v) const { return VECTORIII(x + v.x, y + v.y, z + v.z); }
	inline VECTORIII operator - (const VECTORIII& v) const { return VECTORIII(x - v.x, y - v.y, z - v.z); }
	inline VECTORIII operator * (float v) const { VECTORIII ret(x*v, y*v, z*v); return ret; }
	inline VECTORIII operator / (float v) const { VECTORIII ret(x / v, y / v, z / v); return ret; }

	bool operator == (const VECTORIII& v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
	bool operator != (const VECTORIII& v) const { return (x != v.x) || (y != v.y) || (z != v.z); }


	inline VECTORIII operator + (const DirectX::XMFLOAT3& v) const { return VECTORIII(x + v.x, y + v.y, z + v.z); }
	inline VECTORIII operator - (const DirectX::XMFLOAT3& v) const { return VECTORIII(x - v.x, y - v.y, z - v.z); }

	inline VECTORIII& operator =  (const DirectX::XMFLOAT3& v) { x = v.x; y = v.y; z = v.z; return *this; }

};
struct VECTORII {
	float x, y;
	VECTORII() :
		x(0),
		y(0)
	{}
	VECTORII(float x, float y) :
		x(x),
		y(y)
	{}
	inline float Length() { return sqrtf(x*x + y*y); }
	inline float LengthSq() { return x*x + y*y; }

	//	正規化
	inline void Normalize()
	{
		float l = Length();
		if (l != .0f) { x /= l; y /= l; }
	}

	inline VECTORII& operator =  (const VECTORII& v) { x = v.x; y = v.y; return *this; }
	inline VECTORII& operator += (const VECTORII& v) { x += v.x; y += v.y; return *this; }
	inline VECTORII& operator -= (const VECTORII& v) { x -= v.x; y -= v.y; return *this; }
	inline VECTORII& operator *= (float v) { x *= v; y *= v;  return *this; }
	inline VECTORII& operator /= (float v) { x /= v; y /= v;  return *this; }

	inline VECTORII operator + () const { VECTORII ret(x, y); return ret; }
	inline VECTORII operator - () const { VECTORII ret(-x, -y); return ret; }

	inline VECTORII operator + (const VECTORII& v) const { return VECTORII(x + v.x, y + v.y); }
	inline VECTORII operator - (const VECTORII& v) const { return VECTORII(x - v.x, y - v.y); }
	inline VECTORII operator * (const VECTORII& v) const { return VECTORII(x*v.x, y*v.y); }
	inline VECTORII operator * (float v) const { VECTORII ret(x*v, y*v); return ret; }
	inline VECTORII operator / (float v) const { VECTORII ret(x / v, y / v); return ret; }

	inline VECTORII operator + (const int& i) const { return VECTORII(x + i, y + i); }
	inline VECTORII operator - (const int& i) const { return VECTORII(x - i, y - i); }

	inline VECTORII operator + (const float& i) const { return VECTORII(x + i, y + i); }
	inline VECTORII operator - (const float& i) const { return VECTORII(x - i, y - i); }


	bool operator == (const VECTORII& v) const { return (x == v.x) && (y == v.y); }
	bool operator != (const VECTORII& v) const { return (x != v.x) || (y != v.y); }

}typedef vII;
struct iVECTORII {
	int x, y;
	iVECTORII() :
		x(0),
		y(0)
	{}
	iVECTORII(int x, int y) :
		x(x),
		y(y)
	{}
};

struct YMFLOAT4 {
	float x, y, z, w;
	YMFLOAT4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};


const float		gravity_per_frame = 9.8f / 60.0f;


//float			GetLength(float x1,float y1, float x2, float y2);
inline float	YMabsolute(float a)
{
	return a < 0 ? (a *= -1) : a;
}
float			YMatanf(float x);
float			YMatan2f(float y, float x);
inline int		GetValue(int n)//桁を返す
{
	int out = 1;
	while (n >= 10)
	{
		n /= 10;
		out++;
	}
	return out;
}
inline float	YM_GetDist_sq(float x1, float y1, float x2, float y2) { return sqrtf((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)); }
inline float	YM_GetDist(float x1, float y1, float x2, float y2) { return ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)); }

//*未完成*****************************
inline void		YM_GetRotatePosition(float center_x, float center_y, VECTORII& pos, float rot_angle)
{

	float x1 = pos.x, y1 = pos.y;
	pos.x = x1 * cosf(rot_angle) - y1 * sinf(rot_angle) + center_x;
	pos.y = x1 * sinf(rot_angle) + y1 * cosf(rot_angle) + center_y;
}



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Collision
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool	HitCheck3DCapsule(VECTORIII s_point, VECTORIII e_point, float r1, VECTORIII P, float r2);
bool	HitCheck2DCapsule(VECTORII s_point, VECTORII e_point, float r1, VECTORII p, float r2);




//awa-Attack Water Army-(2017.3)専用拡張
bool	HitCheck2DCapsule(VECTORII s_point, VECTORII e_point, float r1, VECTORII p, float r2, VECTORII& OUT_VECT, float& OUT_R);
inline bool	HitCheckCircle(VECTORII p1, float r1, VECTORII p2, float r2)
{
	float r = r1 + r2;
	if ((p2 - p1).LengthSq() < r*r)return true;
	return false;

}

inline bool	HitCheckSphere(VECTORIII p1, float r1, VECTORIII p2, float r2)
{
	float r = r1 + r2;
	if ((p2 - p1).LengthSq() < r*r)return true;
	return false;

}