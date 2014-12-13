#ifndef ESL_MATH_PLANE3D_H
#define ESL_MATH_PLANE3D_H

#include <math.h>
#include "eslib/common.h"
#include "eslib/math/Vector3.h"


NS_ESLIB_BEGIN

class Plane3D
{
public:
    Plane3D()
    :m_normal(0,1,0)
    ,m_distance(.0f)
    {
    }
    
    void setPlane(const Vector3& normal, f32 distance)
    {
        m_normal = normal;
        m_distance = distance;
    }

	void setPlane(const Vector3& point, const Vector3& normal)
    {
        m_normal = normal;
        recalculateDistance(point);
    }
    
	Plane3D(const Plane3D &rhs)
    :m_normal(rhs.m_normal)
    ,m_distance(rhs.m_distance)
    {
    }

	Plane3D& operator=(const Plane3D &rhs)
	{
        m_normal = rhs.m_normal;
        m_distance = rhs.m_distance;
		return *this;
	}
    
    void recalculateDistance(const Vector3& pointOnPlane)
    {
        m_distance = -pointOnPlane*m_normal;
    }
    
    f32 getDistanceTo(const Vector3& point)
    {
        return point*m_normal + m_distance;
    }

	
public:
    Vector3 m_normal;
    f32 m_distance;
};


NS_ESLIB_END

#endif //ESL_MATH_PLANE3D_H

