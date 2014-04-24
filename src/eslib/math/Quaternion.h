#ifndef ESL_MATH_QUATERNION_H
#define ESL_MATH_QUATERNION_H

#include <math.h>
#include "eslib/common.h"
#include "eslib/math/Vector3.h"
#include "eslib/math/Matrix4.h"
#include "eslib/math/MathUtil.h"

NS_ESLIB_BEGIN


class Quaternion
{
public:
	Quaternion();
    
    Quaternion(const Quaternion& rhs);
    
    Quaternion(f32 x2, f32 y2, f32 z2, f32 w2) : x(x2), y(y2), z(z2), w(w2) {}
    
    Quaternion& set(f32 x2, f32 y2, f32 z2, f32 w2);
    
    //! Normalizes the quaternion
    Quaternion& normalize();
    
    //! Set quaternion to identity
    Quaternion& makeIdentity();
    
    //! Equal operator
    bool operator==(const Quaternion& rhs) const;
    
    //! Assignment operator
    Quaternion& operator=(const Quaternion& rhs);
    
    //! Add operator
    Quaternion operator+(const Quaternion& rhs) const;
    
    //! Multiplication operator with scalar
    Quaternion operator*(f32 s) const;
    
    //! Multiplication operator with scalar
    Quaternion& operator*=(f32 s);
    
    //! Multiplication operator
    Quaternion operator*(const Quaternion& rhs) const;
    
    //! Transform vector
    Vector3 operator*(const Vector3& v) const;
    
    //! Create quaternion from rotation angle and rotation axis.
    /** Axis must be unit length.
     The quaternion representing the rotation is
     q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k).
     \param angle Rotation Angle in degree.
     \param axis Rotation axis. */
    Quaternion& fromAxisAngle(const Vector3& axis, f32 angle);
    
    //! Set quaternion to represent a rotation from one vector to another.
    Quaternion& rotationFromTo(const Vector3& from, const Vector3& to);
    
    //! Get the conjugate quaternion
    Quaternion getConjugate();
    
    //! Get the inverse quaternion
    Quaternion getInverse();
    
    //! Calculates the dot product
    f32 dotProduct(const Quaternion& q2) const;
    
    //! Set this quaternion to the result of the interpolation between two quaternions
    Quaternion& slerp(const Quaternion& q1, const Quaternion& q2, f32 interpolate);
    
    //! Converts a quaternion to a rotation matrix
    void getRotationMatrix(Matrix4& mat) const;
    
public:
    f32 x, y, z, w;
};


#include "eslib/math/QuaternionImpl.h"


NS_ESLIB_END

#endif //ESL_MATH_QUATERNION_H

