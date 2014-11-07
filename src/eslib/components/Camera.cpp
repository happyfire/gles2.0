#include "eslib/components/Camera.h"


NS_ESLIB_BEGIN

static CompIDType sFamilyID = "Camera";
static CompIDType sCompID = "Camera";

Camera::Camera()
{

}

Camera::~Camera()
{

}

Camera::Camera(const Camera& rhs)
:Component(rhs)
{
    m_matProjection = rhs.m_matProjection;
}

Camera& Camera::operator=(const Camera& rhs)
{
    if (&rhs==this) {
        return *this;
    }
    
    Component::operator=(rhs);
    
    m_matProjection = rhs.m_matProjection;
    
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


void Camera::setPerspectiveProjection(float fovAngle, float nearPlane, float farPlane, float aspect)
{
    m_matProjection.makePerspectiveProjectionMatrix(fovAngle, nearPlane, farPlane, aspect);
}

const Matrix4& Camera::getProjectionMatrix() const
{
    return m_matProjection;
}



NS_ESLIB_END
