#ifndef ESL_MATH_QUATERNION_H
#define ESL_MATH_QUATERNION_H

#include <math.h>
#include "eslib/common.h"

NS_ESLIB_BEGIN


class Quaternion
{
public:
	Quaternion();
    
public:
    f32 x, y, z, w;
};


#include "eslib/math/QuaternionImpl.h"


NS_ESLIB_END

#endif //ESL_MATH_QUATERNION_H

