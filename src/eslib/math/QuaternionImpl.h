
#include "MathUtil.h"

inline Quaternion::Quaternion()
{
    x = 0.f;
    y = 0.f;
    z = 0.f;
    w = 1.f;
}

inline Quaternion::Quaternion(const Quaternion& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
}

inline Quaternion& Quaternion::set(f32 x2, f32 y2, f32 z2, f32 w2)
{
	x = x2;
	y = y2;
	z = z2;
	w = w2;
	return *this;
}

inline Quaternion& Quaternion::normalize()
{
    f32 n = x*x + y*y + z*z + w*w;
    if(n==1 || n==0)
        return *this;
    
    f32 s = 1.f / sqrtf(n);
    
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
}

inline Quaternion& Quaternion::makeIdentity()
{
    x = 0.f;
    y = 0.f;
    z = 0.f;
    w = 1.f;
    return *this;
}

inline bool Quaternion::operator==(const Quaternion& rhs) const
{
    return equalsF(x, rhs.x) && equalsF(y, rhs.y) && equalsF(z, rhs.z) && equalsF(w, rhs.w);
}

inline Quaternion& Quaternion::operator=(const Quaternion& rhs)
{
    if(this==&rhs)
        return *this;
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
}

inline Quaternion Quaternion::operator+(const Quaternion& rhs) const
{
    return Quaternion(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
}

inline Quaternion Quaternion::operator*(f32 s) const
{
    Quaternion result;
    result.set(x*s, y*s, z*s, w*s);
    return result;
}

inline Quaternion& Quaternion::operator*=(f32 s)
{
	x*=s;
	y*=s;
	z*=s;
	w*=s;
	return *this;
}

inline Quaternion Quaternion::operator*(const Quaternion& rhs) const
{
    Quaternion result;
    
    result.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    result.y = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
    result.z = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;
    result.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    
    return result;
}

inline Vector3 Quaternion::operator*(const Vector3& v) const
{
    // nVidia SDK implementation
    
	Vector3 uv, uuv;
	Vector3 qvec(x, y, z);
	uv = crossProduct(qvec, v);
	uuv = crossProduct(qvec, uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;
    
	return v + uv + uuv;
}

inline Quaternion& Quaternion::fromAxisAngle(const Vector3& axis, f32 angle)
{
    f32 half_rad = degreeToRadian(angle*0.5f);
    f32 sine = sinf(half_rad);
    
    x = axis.x * sine;
    y = axis.y * sine;
    z = axis.z * sine;
    w = cosf(half_rad);
    
    return *this;
}

inline Quaternion& Quaternion::fromEulerAngle(f32 yaw, f32 pitch, f32 roll)
{
    f64 angle;
    
    angle = roll * 0.5;
    const f64 sr = sin(angle);
    const f64 cr = cos(angle);
    
    angle = pitch * 0.5;
    const f64 sp = sin(angle);
    const f64 cp = cos(angle);
    
    angle = yaw * 0.5;
    const f64 sy = sin(angle);
    const f64 cy = cos(angle);
    
    const f64 cpcy = cp * cy;
    const f64 spcy = sp * cy;
    const f64 cpsy = cp * sy;
    const f64 spsy = sp * sy;
    
    x = (f32)(sr * cpcy - cr * spsy);
    y = (f32)(cr * spcy + sr * cpsy);
    z = (f32)(cr * cpsy - sr * spcy);
    w = (f32)(cr * cpcy + sr * spsy);
    
    return normalize();
}

inline void Quaternion::toEulerAngle(Vector3& euler) const
{
    const f64 sqw = w*w;
    const f64 sqx = x*x;
    const f64 sqy = y*y;
    const f64 sqz = z*z;
    
    // heading = rotation about z-axis
    euler.z = (f32) (atan2(2.0 * (x*y +z*w),(sqx - sqy - sqz + sqw)));
    
    // bank = rotation about x-axis
    euler.x = (f32) (atan2(2.0 * (y*z +x*w),(-sqx - sqy + sqz + sqw)));
    
    // attitude = rotation about y-axis
    euler.y = asinf( clamp(-2.0f * (x*z - y*w), -1.0f, 1.0f) );
}

inline Quaternion& Quaternion::rotationFromTo(const Vector3& from, const Vector3& to)
{
    // Based on Stan Melax's article in Game Programming Gems
	// Copy, since cannot modify local
	Vector3 v0 = from;
	Vector3 v1 = to;
	v0.normalize();
	v1.normalize();
    
	const f32 d = v0 * v1;
	if (d >= 1.0f) // If dot == 1, vectors are the same
	{
		return makeIdentity();
	}
    
	const f32 s = sqrtf( (1+d)*2 ); // optimize inv_sqrt
	const f32 invs = 1.f / s;
	const Vector3 c = crossProduct(v0, v1)*invs;
	x = c.x;
	y = c.y;
	z = c.z;
	w = s * 0.5f;
    
	return *this;
}

inline Quaternion Quaternion::getConjugate()
{
    Quaternion result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = w;
    return result;
}

inline Quaternion Quaternion::getInverse()
{
    Quaternion result;
    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = w;
    return result;
}

inline f32 Quaternion::dotProduct(const Quaternion& q2) const
{
	return (x * q2.x) + (y * q2.y) + (z * q2.z) + (w * q2.w);
}

inline Quaternion& Quaternion::slerp(const Quaternion& _q1, const Quaternion& _q2, f32 interpolate)
{
    Quaternion q1(_q1);
    Quaternion q2(_q2);
    
    f32 angle = q1.dotProduct(q2);
    
	if (angle < 0.0f)
	{
		q1 *= -1.0f;
		angle *= -1.0f;
	}
    
	f32 scale;
	f32 invscale;
    
	if ((angle + 1.0f) > 0.05f)
	{
		if ((1.0f - angle) >= 0.05f) // spherical interpolation
		{
			const f32 theta = acosf(angle);
			const f32 invsintheta = 1.f/sinf(theta);
			scale = sinf(theta * (1.0f-interpolate)) * invsintheta;
			invscale = sinf(theta * interpolate) * invsintheta;
		}
		else // linear interploation
		{
			scale = 1.0f - interpolate;
			invscale = interpolate;
		}
	}
	else
	{
		q2.set(-q1.y, q1.x, -q1.w, q1.z);
		scale = sinf(kPi * (0.5f - interpolate));
		invscale = sinf(kPi * interpolate);
	}
    
	return (*this = (q1*scale) + (q2*invscale));
}

inline void Quaternion::getRotationMatrix(Matrix4& mat) const
{    
    // First row
    mat.m[0] = 1.0f - 2.0f * (y * y + z * z );
    mat.m[1] = 2.0f * (x * y + z * w);
    mat.m[2] = 2.0f * (x * z - y * w);
    mat.m[3] = 0.0f;
    
    // Second row
    mat.m[4] = 2.0f * ( x * y - z * w );
    mat.m[5] = 1.0f - 2.0f * ( x * x + z * z );
    mat.m[6] = 2.0f * (z * y + x * w );
    mat.m[7] = 0.0f;
    
    // Third row
    mat.m[8] = 2.0f * ( x * z + y * w );
    mat.m[9] = 2.0f * ( y * z - x * w );
    mat.m[10] = 1.0f - 2.0f * ( x * x + y * y );
    mat.m[11] = 0.0f;
    
    // Fourth row
    mat.m[12] = 0.0f;
    mat.m[13] = 0.0f;
    mat.m[14] = 0.0f;
    mat.m[15] = 1.0f;
}

