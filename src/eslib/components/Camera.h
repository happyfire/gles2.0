//camera components

#ifndef ESL_COMPONENTS_CAMERA_H
#define ESL_COMPONENTS_CAMERA_H

#include "eslib/common.h"
#include "eslib/SharedPtr.h"
#include "eslib/base/Component.h"
#include "eslib/math/Matrix4.h"
#include "eslib/math/Vector3.h"

NS_ESLIB_BEGIN


class Camera: public Component
{
public:
	Camera();
	virtual ~Camera();
    
    Camera(const Camera& rhs);
    Camera& operator=(const Camera& rhs);
    
    virtual Component* clone() const;
    
    virtual const CompIDType& getFamilyID() const;
    
    virtual const CompIDType& getComponentID() const;

public:
    
    virtual void setPerspectiveProjection(float fovAngle, float nearPlane, float farPlane, float aspect);
    
    virtual const Matrix4& getProjectionMatrix() const;
    
    virtual void setTarget(const Vector3 &targetPos);
    
    virtual void setUpVector(const Vector3 &upVector);
    
    virtual const Matrix4& getViewMatrix();
    
private:
    void updateViewMatrix();
    
protected:
    Matrix4 m_matProjection;
    Matrix4 m_matView;
    
    Vector3 m_targetPos;
    Vector3 m_upVector;
    
    bool m_isMatViewDirty;
	
};


NS_ESLIB_END

#endif //ESL_COMPONENTS_CAMERA_H

