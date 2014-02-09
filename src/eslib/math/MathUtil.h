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

NS_ESLIB_END

#endif //ESL_MATH_MATHUTIL_H

