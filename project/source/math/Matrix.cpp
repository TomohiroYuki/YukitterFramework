#include "source\math\Matrix.h"

Matrix::Matrix(Vector in_x, Vector in_y, Vector in_z, Vector in_w)
{
	m[0][0] = in_x.x; m[0][1] = in_x.y;  m[0][2] = in_x.z;  m[0][3] = 0;
	m[1][0] = in_y.x; m[1][1] = in_y.y;  m[1][2] = in_y.z;  m[1][3] = 0;
	m[2][0] = in_z.x; m[2][1] = in_z.y;  m[2][2] = in_z.z;  m[2][3] = 0;
	m[3][0] = in_w.x; m[3][1] = in_w.y;  m[3][2] = in_w.z;  m[3][3] = 1;
}
