#include "eslib/components/Camera.h"
#include "eslib/base/GameObject.h"
#include "eslib/components/Transform.h"


NS_ESLIB_BEGIN

static CompIDType sFamilyID = "Camera";
static CompIDType sCompID = "Camera";

Camera::Camera()
    :m_isMatViewDirty(true)
    ,m_fov(45)
    ,m_near(1)
    ,m_far(1000)
    ,m_aspect(1.5)
{
    m_matView.makeIdentity();
    m_targetPos.zero();
    m_u.set(1, 0, 0);
    m_v.set(0, 1, 0);
    m_n.set(0, 0, 1);
}

Camera::~Camera()
{

}

Camera::Camera(const Camera& rhs)
:Component(rhs)
{
    m_matProjection = rhs.m_matProjection;
    m_matView = rhs.m_matView;
    m_isMatViewDirty = rhs.m_isMatViewDirty;
    m_fov = rhs.m_fov;
    m_near = rhs.m_near;
    m_far = rhs.m_far;
    m_aspect = rhs.m_aspect;
    m_targetPos = rhs.m_targetPos;
    m_u = rhs.m_u;
    m_v = rhs.m_v;
    m_n = rhs.m_n;
}

Camera& Camera::operator=(const Camera& rhs)
{
    if (&rhs==this) {
        return *this;
    }
    
    Component::operator=(rhs);
    
    m_matProjection = rhs.m_matProjection;
    m_matView = rhs.m_matView;
    m_isMatViewDirty = rhs.m_isMatViewDirty;
    m_fov = rhs.m_fov;
    m_near = rhs.m_near;
    m_far = rhs.m_far;
    m_aspect = rhs.m_aspect;
    m_targetPos = rhs.m_targetPos;
    m_u = rhs.m_u;
    m_v = rhs.m_v;
    m_n = rhs.m_n;
    
    return *this;
}

Component* Camera::clone() const
{
    Camera* newComp = new Camera(*this);
    return newComp;
}



const CompIDType& Camera::getFamilyID() const
{
    return sFamilyID;
}

const CompIDType& Camera::getComponentID() const
{
    return sCompID;
}

void Camera::receiveMessage(Component *sender, int messageId, void *payload)
{
    if (messageId==ComponentMessage::Message_TransformPositionChanged
        || messageId==ComponentMessage::Message_TransformRotationChanged)
    {
        if(messageId==ComponentMessage::Message_TransformRotationChanged)
        {
            Transform* transform = m_ownerObj->getTransform();
            const Quaternion& rot = transform->getRotation();
        
            Matrix4 matRot;
            rot.getRotationMatrix(matRot);
            
            m_u.set(matRot[0], matRot[1], matRot[2]);
            m_v.set(matRot[4], matRot[5], matRot[6]);
            m_n.set(matRot[8], matRot[9], matRot[10]);
            
            m_targetPos = m_eyePos - Vector3(matRot[8], matRot[9], matRot[10]);
        }
        
        m_isMatViewDirty = true;
    }
}

void Camera::setPerspectiveProjection(float fovAngle, float nearPlane, float farPlane, float aspect)
{
    m_fov = fovAngle;
    m_near = nearPlane;
    m_far = farPlane;
    m_aspect = aspect;
    
    m_matProjection.makePerspectiveProjectionMatrix(m_fov, m_near, m_far, m_aspect);
}

void Camera::setFOV(float fovAngle)
{
    m_fov = fovAngle;
    m_matProjection.makePerspectiveProjectionMatrix(m_fov, m_near, m_far, m_aspect);
}

void Camera::setTarget(const Vector3 &targetPos)
{
    m_targetPos = targetPos;
    m_isMatViewDirty = true;
}

void Camera::setUpVector(const Vector3 &upVector)
{
    m_v = upVector;
    m_v.normalize();
    m_isMatViewDirty = true;
}

void Camera::yaw(float angle)
{
    Quaternion qYaw;
    qYaw.fromAxisAngle(m_v, angle);
    
    Transform* transform = m_ownerObj->getTransform();
    const Quaternion& rot = transform->getRotation();
    transform->setRotation(qYaw*rot);
}

void Camera::pitch(float angle)
{
    Quaternion qPitch;
    qPitch.fromAxisAngle(m_u, angle);
    
    Transform* transform = m_ownerObj->getTransform();
    const Quaternion& rot = transform->getRotation();
    transform->setRotation(qPitch*rot);
}

void Camera::roll(float angle)
{
    Quaternion qRoll;
    qRoll.fromAxisAngle(m_n, angle);
    
    Transform* transform = m_ownerObj->getTransform();
    const Quaternion& rot = transform->getRotation();
    transform->setRotation(qRoll*rot);
}

const Matrix4& Camera::getProjectionMatrix() const
{
    return m_matProjection;
}

const Matrix4& Camera::getViewMatrix()
{
    if (m_isMatViewDirty) {
        updateViewMatrix();
        m_isMatViewDirty = false;
    }
    
    return m_matView;
}

void Camera::updateViewMatrix()
{
    m_eyePos = m_ownerObj->getTransform()->getAbsolutePosition();
    
    m_n = m_eyePos - m_targetPos;
    m_n.normalize();
    
    m_u = crossProduct(m_v, m_n);
    m_u.normalize();
    
    m_v = crossProduct(m_n, m_u);
    
    computeViewMatrixByUVN();
}

void Camera::computeViewMatrixByUVN()
{
    m_matView.makeIdentity();
    m_matView[0] = m_u.x;
    m_matView[1] = m_v.x;
    m_matView[2] = m_n.x;
    m_matView[4] = m_u.y;
    m_matView[5] = m_v.y;
    m_matView[6] = m_n.y;
    m_matView[8] = m_u.z;
    m_matView[9] = m_v.z;
    m_matView[10] = m_n.z;
    m_matView[12] = -(m_u*m_eyePos);
    m_matView[13] = -(m_v*m_eyePos);
    m_matView[14] = -(m_n*m_eyePos);
}



NS_ESLIB_END
