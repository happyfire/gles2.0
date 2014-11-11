#ifndef ESL_MATH_VECTOR3_H
#define ESL_MATH_VECTOR3_H

#include <math.h>
#include "eslib/common.h"


NS_ESLIB_BEGIN


class Vector3
{
public:
	Vector3(){}

	Vector3(f32 nx, f32 ny, f32 nz): x(nx), y(ny), z(nz){}

	Vector3(const Vector3 &rhs): x(rhs.x), y(rhs.y), z(rhs.z){}

	Vector3& operator=(const Vector3 &rhs)
	{
		x = rhs.x;
		y = rhs.y; 
		z = rhs.z;
		return *this;
	}

	bool operator ==(const Vector3 &rhs) const
	{
		return x==rhs.x && y==rhs.y && z==rhs.z;
	}

	bool operator !=(const Vector3 &rhs) const
	{
		return x!=rhs.x || y!=rhs.y || z!=rhs.z;
	}

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
    
    void set(f32 nx, f32 ny, f32 nz)
    {
        x = nx;
        y = ny;
        z = nz;
    }

	Vector3 operator -() const
	{
		return Vector3(-x,-y,-z);
	}

	Vector3 operator +(const Vector3 &rhs) const
	{
		return Vector3(x+rhs.x, y+rhs.y, z+rhs.z);
	}

	Vector3 operator -(const Vector3 &rhs) const
	{
		return Vector3(x-rhs.x, y-rhs.y, z-rhs.z);
	}

	Vector3 operator *(f32 a) const
	{
		return Vector3(x*a, y*a, z*a);
	}

	Vector3 operator /(f32 a) const
	{
		ESL_ASSERT((int)a!=0);
		f32 oneOverA = 1.0f/a;
		return Vector3(x*oneOverA, y*oneOverA, z*oneOverA);
	}

	Vector3& operator +=(const Vector3 &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3& operator -=(const Vector3 &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vector3& operator *=(f32 a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	Vector3& operator /=(f32 a)
	{
		ESL_ASSERT((int)a!=0);
		float oneOverA = 1.0f/a;
		x *= oneOverA;
		y *= oneOverA;
		z *= oneOverA;
		return *this;
	}

	Vector3& normalize()
	{
		f32 magSq = x*x + y*y + z*z;
		if (magSq>0.0f)
		{
			float oneOverMag = 1.0f/sqrt(magSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
		return *this;
	}

	f32 operator *(const Vector3 &rhs) const
	{
		return x*rhs.x + y*rhs.y + z*rhs.z;
	}

	f32 length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

public:
	f32 x, y, z;
};

inline Vector3 crossProduct(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

inline Vector3 operator*(f32 k, const Vector3 &v)
{
	return Vector3(k*v.x, k*v.y, k*v.z);
}

inline f32 getDistance(const Vector3 &a, const Vector3 &b)
{
	f32 dx = a.x - b.x;
	f32 dy = a.y - b.y;
	f32 dz = a.z - b.z;
	return sqrt(dx*dx+dy*dy+dz*dz);
}

extern const Vector3 kVectorZero;


NS_ESLIB_END

#endif //ESL_MATH_VECTOR3_H

