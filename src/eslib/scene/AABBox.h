#ifndef ESL_SCENE_AABBOX_H
#define ESL_SCENE_AABBOX_H

#include "eslib/math/Vector3.h"


NS_ESLIB_BEGIN


class AABBox
{
public:
    AABBox();
    
    AABBox(const AABBox& rhs);
    
    AABBox& operator=(const AABBox& rhs);
    
    void reset(const Vector3& point);
    
    void addPoint(const Vector3& point);
    
    void addBox(const AABBox& box);
    
    void setBox(const Vector3& minPoint, const Vector3& maxPoint);
    
    Vector3 getVectorP(const Vector3& normal) const;
    
    Vector3 getVectorN(const Vector3& normal) const;
    
    bool isIntersectsWithBox(const AABBox& other) const;
    
    bool isFullInsideBox(const AABBox& other) const;
    
public:
    Vector3 MinPoint;
    Vector3 MaxPoint;

	
};



NS_ESLIB_END

#endif //ESL_SCENE_AABBOX_H
