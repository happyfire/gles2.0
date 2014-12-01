#ifndef ESL_MATH_MATHUTIL_H
#define ESL_MATH_MATHUTIL_H

#include <math.h>
#include "eslib/common.h"


NS_ESLIB_BEGIN

const f32 kPi = 3.14159265f;
const f32 k2Pi = kPi * 2.0f;
const f32 kPiOver2 = kPi / 2.0f;
const f32 k1OverPi = 1.0f / kPi;
const f32 k1Over2Pi = 1.0f / k2Pi;
const f32 kPiOver180 = kPi / 180.0f;
const f32 k180OverPi = 180.0f / kPi;

// Convert between degrees and radians

inline f32 degreeToRadian(float degree) { return degree * kPiOver180; }
inline f32 radianToDegree(float radian) { return radian * k180OverPi; }

const f32 ROUNDING_ERROR_f32 = 0.000001f;
const f64 ROUNDING_ERROR_f64 = 0.00000001;

//! returns if a equals b, taking possible rounding errors into account
inline bool equalsF(const f64 a, const f64 b, const f64 tolerance = ROUNDING_ERROR_f64)
{
    return (a + tolerance >= b) && (a - tolerance <= b);
}

//! returns if a equals b, taking possible rounding errors into account
inline bool equalsF(const f32 a, const f32 b, const f32 tolerance = ROUNDING_ERROR_f32)
{
    return (a + tolerance >= b) && (a - tolerance <= b);
}

//! returns if a equals zero, taking rounding errors into account
inline bool isZeroF(const f64 a, const f64 tolerance = ROUNDING_ERROR_f64)
{
    return fabs(a) <= tolerance;
}

//! returns if a equals zero, taking rounding errors into account
inline bool isZeroF(const f32 a, const f32 tolerance = ROUNDING_ERROR_f32)
{
    return fabsf(a) <= tolerance;
}

//! returns minimum of two values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& min_(const T& a, const T& b)
{
    return a < b ? a : b;
}

//! returns minimum of three values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& min_(const T& a, const T& b, const T& c)
{
    return a < b ? min_(a, c) : min_(b, c);
}

//! returns maximum of two values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& max_(const T& a, const T& b)
{
    return a < b ? b : a;
}

//! returns maximum of three values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& max_(const T& a, const T& b, const T& c)
{
    return a < b ? max_(b, c) : max_(a, c);
}

//! returns abs of two values. Own implementation to get rid of STL (VS6 problems)
template<class T>
inline T abs_(const T& a)
{
    return a < (T)0 ? -a : a;
}

//! clamps a value between low and high
template <class T>
inline const T clamp (const T& value, const T& low, const T& high)
{
    return min_ (max_(value,low), high);
}

NS_ESLIB_END

#endif //ESL_MATH_MATHUTIL_H

