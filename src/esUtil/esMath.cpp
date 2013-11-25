#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "esUtil.h"

void esMatrixIdentity(ESMatrix mat)
{
	mat[0] = mat[5] = mat[10] = mat[15] = 1.0f;
	mat[1] = mat[2] = mat[3] = mat[4] = 0.0f;
	mat[6] = mat[7] = mat[8] = mat[9] = 0.0f;
	mat[11] = mat[12] = mat[13] = mat[14] = 0.0f;
}

void esMatrixTranslate(ESMatrix mat, float x, float y, float z)
{
	esMatrixIdentity(mat);

	mat[12] = x;
	mat[13] = y;
	mat[14] = z;
}

void esMatrixSetTranslate(ESMatrix mat, float x, float y, float z)
{
	mat[12] = x;
	mat[13] = y;
	mat[14] = z;
}

void esMatrixScale(ESMatrix mat, float sx, float sy, float sz)
{
	esMatrixIdentity(mat);

	mat[0] = sx;
	mat[5] = sy;
	mat[10] = sz;
}

void esMatrixRotateX(ESMatrix mat, float degrees)
{
	float radian = DegreeToRadian(degrees);

	esMatrixIdentity(mat);

	mat[5] = cosf(radian);
	mat[6] = -sinf(radian);
	mat[9] = -mat[6];
	mat[10] = mat[5];
}

void esMatrixRotateY(ESMatrix mat, float degrees)
{
	float radian = DegreeToRadian(degrees);

	esMatrixIdentity(mat);

	mat[0] = cosf(radian);
	mat[2] = sinf(radian);
	mat[8] = -mat[2];
	mat[10] = mat[0];
}

void esMatrixRotateZ(ESMatrix mat, float degrees)
{
	float radian = DegreeToRadian(degrees);

	esMatrixIdentity(mat);

	mat[0] = cosf(radian);
	mat[1] = sinf(radian);
	mat[4] = -mat[1];
	mat[5] = mat[0];
}

void esMatrixMultiply(ESMatrix m1, ESMatrix m2, ESMatrix result)
{
	// Fisrt Column
	result[0] = m1[0]*m2[0] + m1[4]*m2[1] + m1[8]*m2[2] + m1[12]*m2[3];
	result[1] = m1[1]*m2[0] + m1[5]*m2[1] + m1[9]*m2[2] + m1[13]*m2[3];
	result[2] = m1[2]*m2[0] + m1[6]*m2[1] + m1[10]*m2[2] + m1[14]*m2[3];
	result[3] = m1[3]*m2[0] + m1[7]*m2[1] + m1[11]*m2[2] + m1[15]*m2[3];

	// Second Column
	result[4] = m1[0]*m2[4] + m1[4]*m2[5] + m1[8]*m2[6] + m1[12]*m2[7];
	result[5] = m1[1]*m2[4] + m1[5]*m2[5] + m1[9]*m2[6] + m1[13]*m2[7];
	result[6] = m1[2]*m2[4] + m1[6]*m2[5] + m1[10]*m2[6] + m1[14]*m2[7];
	result[7] = m1[3]*m2[4] + m1[7]*m2[5] + m1[11]*m2[6] + m1[15]*m2[7];

	// Third Column
	result[8] = m1[0]*m2[8] + m1[4]*m2[9] + m1[8]*m2[10] + m1[12]*m2[11];
	result[9] = m1[1]*m2[8] + m1[5]*m2[9] + m1[9]*m2[10] + m1[13]*m2[11];
	result[10] = m1[2]*m2[8] + m1[6]*m2[9] + m1[10]*m2[10] + m1[14]*m2[11];
	result[11] = m1[3]*m2[8] + m1[7]*m2[9] + m1[11]*m2[10] + m1[15]*m2[11];

	// Fourth Column
	result[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12]*m2[15];
	result[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14] + m1[13]*m2[15];
	result[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];
	result[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];
}

void esMatrixPerspective(ESMatrix matrix, float fovAngle, float nearPlane, float farPlane, float aspect)
{
	float size = nearPlane * tanf(DegreeToRadian(fovAngle) / 2.0);
	float left = -size, right = size, bottom = -size / aspect, top = size / aspect;

	// Unused values in perspective formula.
	matrix[1] = matrix[2] = matrix[3] = matrix[4] = 0;
	matrix[6] = matrix[7] = matrix[12] = matrix[13] = matrix[15] = 0;

	// Perspective formula.
	matrix[0] = 2 * nearPlane / (right - left);
	matrix[5] = 2 * nearPlane / (top - bottom);
	matrix[8] = (right + left) / (right - left);
	matrix[9] = (top + bottom) / (top - bottom);
	matrix[10] = -(farPlane + nearPlane) / (farPlane - nearPlane);
	matrix[11] = -1;
	matrix[14] = -(2 * farPlane * nearPlane) / (farPlane - nearPlane);
}
