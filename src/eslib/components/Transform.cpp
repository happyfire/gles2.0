#include "eslib/components/Transform.h"
#include "eslib/base/GameObject.h"

NS_ESLIB_BEGIN

Transform::Transform()
    :m_flag(ETransformAllDirty)
    ,m_translation(0.0f,0.0f,0.0f)
    ,m_scale(1.0f,1.0f,1.0f)
    ,m_rotation()
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
    m_rotation = rhs.m_rotation;
    m_flag = rhs.m_flag;
    m_relativeTransform = rhs.m_relativeTransform;
    m_absoluteTransform = rhs.m_absoluteTransform;
    
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
    m_rotation = rhs.m_rotation;
    m_flag = rhs.m_flag;
    m_relativeTransform = rhs.m_relativeTransform;
    m_absoluteTransform = rhs.m_absoluteTransform;
    
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

const Quaternion& Transform::getRotation() const
{
    return m_rotation;
}

void Transform::setRotation(Quaternion& rot)
{
    m_rotation = rot;
    m_flag |= ETransformRotationChanged;
}

void Transform::setRotation(const Vector3& axis, f32 degree)
{
    m_rotation.fromAxisAngle(axis, degree);
    m_rotation.normalize();
    m_flag |= ETransformRotationChanged;
}

const Matrix4& Transform::getRelativeTransform()
{
    if(m_flag & ERelativeTransformChanged){
        updateRelativeTransform();
        m_flag &= ERelativeTransformChanged;
        m_flag |= EAbsoluteTransformChanged;
    }
    
    return m_relativeTransform;
}

const Matrix4& Transform::getAbsoluteTransform()
{
    updateAbsoluteTransform(false);
    
    return m_absoluteTransform;
}

void Transform::updateRelativeTransform()
{
    if(m_flag & (ETransformRotationChanged | ETransformScaleChanged))
    {
        m_rotation.getRotationMatrix(m_relativeTransform);
        m_relativeTransform.postScale(m_scale);
        m_relativeTransform.setTranslation(m_translation);
    }
    else
    {
        m_relativeTransform.setTranslation(m_translation);
    }
    
}

void Transform::updateAbsoluteTransform(bool updateChildren)
{
    const Matrix4& relativeTransform = getRelativeTransform();
    
    if(m_flag & EAbsoluteTransformChanged)
    {
        const GameObjectPtr& parentObj = m_ownerObj->getParent();
        if (parentObj.isValid())
        {
            Transform* parentTransform = parentObj->getTransform();
            multiplyMatrix(parentTransform->getAbsoluteTransform(), relativeTransform, m_absoluteTransform);
        }
        else
        {
            m_absoluteTransform = relativeTransform;
        }
        
        m_flag &= ~EAbsoluteTransformChanged;
    }
    
    if (updateChildren)
    {
        GameObjectList& children = m_ownerObj->getChildren();
        GameObjectIter iter = children.begin();
        for (GameObjectIter iterEnd=children.end(); iter!=iterEnd; ++iter)
        {
            GameObjectPtr& obj = *iter;
            obj->getTransform()->updateAbsoluteTransform(true);
        }
    }
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
