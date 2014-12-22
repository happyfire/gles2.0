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

void ViewFrustum::setFromCamera(f32 fovHor, f32 near, f32 far, f32 aspect, const Vector3& position, const Vector3& lookDir, const Vector3& upDir, const Vector3& rightDir)
{
    f32 tang = tanf(degreeToRadian(fovHor) * 0.5f);
    f32 nearHalfW = near * tang;
    f32 nearHalfH = nearHalfW / aspect;
    
    Vector3 nc = position + lookDir*near;
    Vector3 fc = position + lookDir*far;
    
    m_planes[PLANE_NEAR].setPlane(nc, lookDir);
    m_planes[PLANE_FAR].setPlane(fc, -lookDir);
    
    Vector3 a = nc + rightDir*nearHalfW - position;
    a.normalize();
    Vector3 faceNormal = crossProduct(upDir, a);
    faceNormal.normalize();
    m_planes[PLANE_RIGHT].setPlane(position, faceNormal);
    
    a = nc - rightDir*nearHalfW - position;
    a.normalize();
    faceNormal = crossProduct(a, upDir);
    faceNormal.normalize();
    m_planes[PLANE_LEFT].setPlane(position, faceNormal);
    
    a = nc + upDir*nearHalfH - position;
    a.normalize();
    faceNormal = crossProduct(a, rightDir);
    faceNormal.normalize();
    m_planes[PLANE_TOP].setPlane(position, faceNormal);
    
    a = nc - upDir*nearHalfH - position;
    a.normalize();
    faceNormal = crossProduct(rightDir, a);
    faceNormal.normalize();
    m_planes[PLANE_BOTTOM].setPlane(position, faceNormal);
}

NS_ESLIB_END
