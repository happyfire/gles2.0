#ifndef ESL_SCENE_VIEWFRUSTUM_H
#define ESL_SCENE_VIEWFRUSTUM_H

#include "eslib/common.h"
#include "eslib/math/Plane3D.h"


NS_ESLIB_BEGIN

class AABBox;

class ViewFrustum
{
public:
    enum{
        OUTSIDE,
        INTERSECT,
        INSIDE
    };
    
    ViewFrustum();
    
    ViewFrustum(const ViewFrustum& rhs);
    
    ViewFrustum& operator=(const ViewFrustum& rhs);
    
    void setFromCamera(f32 fovHor, f32 near, f32 far, f32 aspect, const Vector3& position, const Vector3& lookDir, const Vector3& upDir, const Vector3& rightDir);
    
    int isAABBInFrustum(const AABBox& box);
    
private:
    enum{
        PLANE_TOP = 0,
        PLANE_BOTTOM,
        PLANE_LEFT,
        PLANE_RIGHT,
        PLANE_NEAR,
        PLANE_FAR,
        PLANE_COUNT
    };
    
    Plane3D m_planes[PLANE_COUNT];
};



NS_ESLIB_END

#endif //ESL_SCENE_VIEWFRUSTUM_H
