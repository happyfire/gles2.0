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

void AABBox::clear()
{
    MinPoint.set(-1, -1, -1);
    MaxPoint.set(1, 1, 1);
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

void AABBox::transform(const Matrix4 &transform)
{
    const f32 Amin[3] = {MinPoint.x, MinPoint.y, MinPoint.z};
    const f32 Amax[3] = {MaxPoint.x, MaxPoint.y, MaxPoint.z};
    
    f32 Bmin[3];
    f32 Bmax[3];
    
    Bmin[0] = Bmax[0] = transform[12];
    Bmin[1] = Bmax[1] = transform[13];
    Bmin[2] = Bmax[2] = transform[14];
    
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            f32 a = transform(i,j) * Amin[j];
            f32 b = transform(i,j) * Amax[j];
            if (a<b)
            {
                Bmin[i] += a;
                Bmax[i] += b;
            }
            else
            {
                Bmin[i] += b;
                Bmax[i] += a;
            }
        }
    }
    
    MinPoint.x = Bmin[0];
    MinPoint.y = Bmin[1];
    MinPoint.z = Bmin[2];
    MaxPoint.x = Bmax[0];
    MaxPoint.y = Bmax[1];
    MaxPoint.z = Bmax[2];
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
