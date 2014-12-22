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
    
    virtual void receiveMessage(Component *sender, int messageId, void *payload);

public:
    
    //fovAngleHor: 水平方向视角，单位：度
    //aspect: 视口宽/高
    void setPerspectiveProjection(float fovAngleHor, float nearPlane, float farPlane, float aspect);
    
    void setFOV(float fovAngle);
    
    void setTarget(const Vector3 &targetPos);
    
    void setUpVector(const Vector3 &upVector);
    
    void yaw(float angle);
    
    void pitch(float angle);
    
    void roll(float angle);
    
    const Matrix4& getProjectionMatrix() const;
    
    const Matrix4& getViewMatrix();
    
    float getFov() const { return m_fov; }
    
    const Vector3& getRightVector() const { return m_u; }
    
    const Vector3& getUpVector() const { return m_v; }
    
    const Vector3& getLookatVector() const { return m_n; }
    
    const Vector3& getEyePos() const { return m_eyePos; }
    
private:
    void updateViewMatrix();
    
    void computeViewMatrixByUVN();
    
protected:
    Matrix4 m_matProjection;
    Matrix4 m_matView;
    
    float m_fov; //水平方向视角，单位：度
    float m_near;
    float m_far;
    float m_aspect; //视口宽高比
    
    Vector3 m_targetPos;
    
    Vector3 m_u, m_v, m_n;
    Vector3 m_eyePos;
    
    bool m_isMatViewDirty;
	
};


NS_ESLIB_END

#endif //ESL_COMPONENTS_CAMERA_H

