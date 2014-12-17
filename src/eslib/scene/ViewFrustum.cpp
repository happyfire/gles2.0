#include "eslib/scene/ViewFrustum.h"

NS_ESLIB_BEGIN

ViewFrustum::ViewFrustum()
{

}

ViewFrustum::ViewFrustum(const ViewFrustum& rhs)
{
    for (int i=0; i<PLANE_COUNT; i++) {
        m_planes[i] = rhs.m_planes[i];
    }
}

ViewFrustum& ViewFrustum::operator=(const ViewFrustum& rhs)
{
    if (this==&rhs) {
        return *this;
    }
    
    for (int i=0; i<PLANE_COUNT; i++) {
        m_planes[i] = rhs.m_planes[i];
    }

    return *this;
}

void ViewFrustum::setFromCamera(f32 fov, f32 near, f32 far, f32 aspect, const Vector3& position, const Vector3& lookDir, const Vector3& upDir, const Vector3& rightDir)
{
    f32 tang = tanf(degreeToRadian(fov) * 0.5f);
    f32 nearH = near * tang;
}

NS_ESLIB_END
