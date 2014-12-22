#ifndef ESL_MATH_MATRIX4_H
#define ESL_MATH_MATRIX4_H

#include <math.h>
#include "eslib/common.h"
#include "eslib/math/Vector3.h"
#include "eslib/math/MathUtil.h"

NS_ESLIB_BEGIN


class Matrix4
{
public:
	Matrix4(bool isIdentity=false);

	Matrix4(f32 data[]);

	Matrix4(const Matrix4 &rhs);

	Matrix4& operator=(const Matrix4 &rhs);

	f32& operator[](int index);

	const f32& operator[](int index) const;

	bool operator ==(const Matrix4 &rhs) const;

	bool operator !=(const Matrix4 &rhs) const;

	Matrix4 operator +(const Matrix4 &rhs) const;

	Matrix4& operator +=(const Matrix4 &rhs);

	Matrix4 operator -(const Matrix4 &rhs) const;

	Matrix4& operator -=(const Matrix4 &rhs);

	Matrix4 operator *(f32 a) const;

	Matrix4& operator *=(f32 a);

	Matrix4& makeByMultiply(const Matrix4 &mat1, const Matrix4 &mat2);

	Matrix4 operator *(const Matrix4 &rhs) const;

	Matrix4& operator *=(const Matrix4 &rhs);

	Matrix4& makeIdentity();

	Matrix4& makeTranslationMatrix(f32 x, f32 y, f32 z);

    Matrix4& setTranslation(const Vector3 &translation);
    
	Matrix4& setTranslation(f32 x, f32 y, f32 z);

	Vector3 getTranslation() const;
    
    Matrix4& postScale(const Vector3 &scale);

	Matrix4& makeScaleMatrix(f32 sx, f32 sy, f32 sz);

	Matrix4& makeRotateXMatrix(f32 rotDegree);

	Matrix4& makeRotateYMatrix(f32 rotDegree);

	Matrix4& makeRotateZMatrix(f32 rotDegree);

    //fovAngleHor: 水平方向视角，单位：度
    //aspect: 视口宽/高
	Matrix4& makePerspectiveProjectionMatrix(f32 fovAngleHor, f32 nearPlane, f32 farPlane, f32 aspect);

	const f32* getData() const;

	f32* getData();

public:
	f32 m[16];
};

Matrix4 operator*(f32 a, const Matrix4 &m);

void multiplyMatrix(const Matrix4& mat1, const Matrix4& mat2, Matrix4& matOut);

#include "eslib/math/Matrix4Impl.h"

extern const Matrix4 kMatrixIdentity;

NS_ESLIB_END

#endif //ESL_MATH_MATRIX4_H

