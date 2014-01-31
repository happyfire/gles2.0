#include "eslib/components/Transform.h"

NS_ESLIB_BEGIN

Transform::Transform()
{
}

Transform::~Transform()
{
    
}

Transform::Transform(const Transform& rhs)
	:Component(rhs)
{
    memcpy(m_matMVP, rhs.m_matMVP, sizeof(rhs.m_matMVP));
}

Transform& Transform::operator=(const Transform& rhs)
{
    if (&rhs==this) {
        return *this;
    }

	Component::operator=(rhs);
    
    memcpy(m_matMVP, rhs.m_matMVP, sizeof(rhs.m_matMVP));
    
    return *this;
}

Component* Transform::clone() const
{
    Transform* newComp = new Transform(*this);
    return newComp;
}

static CompIDType sFamilyID = "Transform";
static CompIDType sCompID = "Transform";

const CompIDType& Transform::getFamilyID() const
{
    return sFamilyID;
}

const CompIDType& Transform::getComponentID() const
{
    return sCompID;
}


void Transform::update()
{
    
}

void Transform::setMVPMatrix(const ESMatrix& mvp)
{
	memcpy(m_matMVP, mvp, sizeof(mvp));
}

ESMatrix& Transform::getMVPMatrix()
{
	return m_matMVP;
}

NS_ESLIB_END