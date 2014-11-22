#include "eslib/components/Camera.h"
#include "eslib/base/GameObject.h"
#include "eslib/components/Transform.h"


NS_ESLIB_BEGIN

static CompIDType sFamilyID = "Camera";
static CompIDType sCompID = "Camera";

Camera::Camera()
    :m_isMatViewDirty(true)
{
    m_matView.makeIdentity();
    m_targetPos.zero();
    m_upVector.set(0, 1, 0);
}

Camera::~Camera()
{

}

Camera::Camera(const Camera& rhs)
:Component(rhs)
{
    m_matProjection = rhs.m_matProjection;
    m_matView = rhs.m_matView;
    m_targetPos = rhs.m_targetPos;
    m_upVector = rhs.m_upVector;
}

Camera& Camera::operator=(const Camera& rhs)
{
    if (&rhs==this) {
        return *this;
    }
    
    Component::operator=(rhs);
    
    m_matProjection = rhs.m_matProjection;
    m_matView = rhs.m_matView;
    m_targetPos = rhs.m_targetPos;
    m_upVector = rhs.m_upVector;
    
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
        m_isMatViewDirty = true;
    }
}

void Camera::setPerspectiveProjection(float fovAngle, float nearPlane, float farPlane, float aspect)
{
    m_matProjection.makePerspectiveProjectionMatrix(fovAngle, nearPlane, farPlane, aspect);
}

const Matrix4& Camera::getProjectionMatrix() const
{
    return m_matProjection;
}

void Camera::setTarget(const Vector3 &targetPos)
{
    m_targetPos = targetPos;
    m_isMatViewDirty = true;
}

void Camera::setUpVector(const Vector3 &upVector)
{
    m_upVector = upVector;
    m_upVector.normalize();
    m_isMatViewDirty = true;
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
    GameObjectPtr owner = getOwnerObject();
    const Matrix4& mat = owner->getTransform()->getAbsoluteTransform();
    Vector3 eyePos = mat.getTranslation();
    
    Vector3 n = eyePos - m_targetPos;
    n.normalize();
    
    Vector3 u = crossProduct(m_upVector, n);
    u.normalize();
    
    Vector3 v = crossProduct(n, u);
    
    m_matView.makeIdentity();
    m_matView[0] = u.x;
    m_matView[1] = v.x;
    m_matView[2] = n.x;
    m_matView[4] = u.y;
    m_matView[5] = v.y;
    m_matView[6] = n.y;
    m_matView[8] = u.z;
    m_matView[9] = v.z;
    m_matView[10] = n.z;
    m_matView[12] = -(u*eyePos);
    m_matView[13] = -(v*eyePos);
    m_matView[14] = -(n*eyePos);
}



NS_ESLIB_END
