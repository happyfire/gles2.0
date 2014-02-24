#include "eslib/components/Transform.h"

NS_ESLIB_BEGIN

Transform::Transform()
    :m_flag(0)
    ,m_translation(0.0f,0.0f,0.0f)
    ,m_scale(1.0f,1.0f,1.0f)
{
}

Transform::~Transform()
{
    
}

Transform::Transform(const Transform& rhs)
	:Component(rhs)
{
    m_translation = rhs.m_translation;
    m_scale = rhs.m_scale;
    m_flag = rhs.m_flag;
    m_relativeTransform = rhs.m_relativeTransform;
    m_absoulteTransform = rhs.m_absoulteTransform;
    
	m_matMVP = rhs.m_matMVP;
}

Transform& Transform::operator=(const Transform& rhs)
{
    if (&rhs==this) {
        return *this;
    }

	Component::operator=(rhs);
    
    m_translation = rhs.m_translation;
    m_scale = rhs.m_scale;
    m_flag = rhs.m_flag;
    m_relativeTransform = rhs.m_relativeTransform;
    m_absoulteTransform = rhs.m_absoulteTransform;
    
    m_matMVP = rhs.m_matMVP;
    
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

const Vector3& Transform::getPosition() const
{
    return m_translation;
}

void Transform::setPosition(const Vector3 &pos)
{
    m_translation = pos;
    m_flag |= ETransformTranslationChanged;
}

void Transform::setPosition(f32 x, f32 y, f32 z)
{
    m_translation.x = x;
    m_translation.y = y;
    m_translation.z = z;
    m_flag |= ETransformTranslationChanged;
}

const Vector3& Transform::getScale() const
{
    return m_scale;
}

void Transform::setScale(const Vector3 &scale)
{
    m_scale = scale;
    m_flag |= ETransformScaleChanged;
}

void Transform::setScale(f32 scale)
{
    m_scale.x = scale;
    m_scale.y = scale;
    m_scale.z = scale;
    m_flag |= ETransformScaleChanged;
}

const Matrix4& Transform::getRelativeTransform() const
{
    if(m_flag & ERelativeTransformChanged){
        
    }
    
    return m_relativeTransform;
}

const Matrix4& Transform::getAbsoluteTransform() const
{
    if(m_flag & EAbsoluteTransformChanged){
        
    }
    
    return m_absoulteTransform;
}

void Transform::setMVPMatrix(const Matrix4& mvp)
{
	m_matMVP = mvp;
}

Matrix4& Transform::getMVPMatrix()
{
	return m_matMVP;
}

NS_ESLIB_END