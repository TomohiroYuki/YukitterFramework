#pragma once
#include "source\math\Vector.h"
using namespace Yukitter;

struct Matrix
{
	float m[4][4];

	F_INLINE Matrix(Vector in_x, Vector in_y, Vector in_z, Vector in_w);

	F_INLINE Matrix operator *= (const Matrix& other);
	F_INLINE Matrix operator * (const Matrix& other);
};

F_INLINE Matrix Matrix::operator *= (const Matrix& other)
{
}

F_INLINE Matrix Matrix::operator * (const Matrix& other)
{

}