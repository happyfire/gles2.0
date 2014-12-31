#ifndef ESL_SCENE_AABBOX_H
#define ESL_SCENE_AABBOX_H

#include "eslib/math/Vector3.h"
#include "eslib/math/Matrix4.h"


NS_ESLIB_BEGIN


class AABBox
{
public:
    AABBox();
    
    AABBox(const AABBox& rhs);
    
    AABBox& operator=(const AABBox& rhs);
    
    void clear();
        
    void reset(const Vector3& point);
    
    void addPoint(const Vector3& point);
    
    void addBox(const AABBox& box);
    
    void setBox(const Vector3& minPoint, const Vector3& maxPoint);
    
    void transform(const Matrix4 &transform);
    
    Vector3 getVectorP(const Vector3& normal) const;
    
    Vector3 getVectorN(const Vector3& normal) const;
    
    bool isIntersectsWithBox(const AABBox& other) const;
    
    bool isFullInsideBox(const AABBox& other) const;
    
    Vector3 getCenter() const;
    
    void getEdges(Vector3 *edges) const;
    
public:
    Vector3 MinPoint;
    Vector3 MaxPoint;

	
};



NS_ESLIB_END

#endif //ESL_SCENE_AABBOX_H
