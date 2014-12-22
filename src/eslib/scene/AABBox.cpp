#include "eslib/scene/AABBox.h"

NS_ESLIB_BEGIN

AABBox::AABBox()
{
    MinPoint.set(-1, -1, -1);
    MaxPoint.set(1, 1, 1);
}

AABBox::AABBox(const AABBox& rhs)
{
    MinPoint = rhs.MinPoint;
    MaxPoint = rhs.MaxPoint;
}

AABBox& AABBox::operator=(const AABBox& rhs)
{
    if (this==&rhs) {
        return *this;
    }
    
    MinPoint = rhs.MinPoint;
    MaxPoint = rhs.MaxPoint;
    return *this;
}

void AABBox::reset(const Vector3& point)
{
    MinPoint = point;
    MaxPoint = point;
}

void AABBox::addPoint(const Vector3& point)
{
    if (point.x>MaxPoint.x) {
        MaxPoint.x = point.x;
    }
    if (point.y>MaxPoint.y) {
        MaxPoint.y = point.y;
    }
    if (point.z>MaxPoint.z) {
        MaxPoint.z = point.z;
    }
    
    if (point.x<MinPoint.x) {
        MinPoint.x = point.x;
    }
    if (point.y<MinPoint.y) {
        MinPoint.y = point.y;
    }
    if (point.z<MinPoint.z) {
        MinPoint.z = point.z;
    }
}

void AABBox::addBox(const AABBox& box)
{
    addPoint(box.MaxPoint);
    addPoint(box.MinPoint);
}

void AABBox::setBox(const Vector3& minPoint, const Vector3& maxPoint)
{
    MinPoint = MinPoint;
    MaxPoint = MaxPoint;
}

Vector3 AABBox::getVectorP(const Vector3& normal) const
{
    Vector3 p = MinPoint;
    
    if (normal.x>=0) {
        p.x = MaxPoint.x;
    }
    if (normal.y>=0) {
        p.y = MaxPoint.y;
    }
    if (normal.z>=0) {
        p.z = MaxPoint.z;
    }
    
    return p;
}

Vector3 AABBox::getVectorN(const Vector3& normal) const
{
    Vector3 p = MaxPoint;
    
    if (normal.x>=0) {
        p.x = MinPoint.x;
    }
    if (normal.y>=0) {
        p.y = MinPoint.y;
    }
    if (normal.z>=0) {
        p.z = MinPoint.z;
    }
    
    return p;
}

bool AABBox::isIntersectsWithBox(const AABBox& other) const
{
    return MinPoint<=other.MaxPoint && MaxPoint>=other.MinPoint;
}

bool AABBox::isFullInsideBox(const AABBox& other) const
{
    return MinPoint>=other.MinPoint && MaxPoint<=other.MaxPoint;
}

NS_ESLIB_END
