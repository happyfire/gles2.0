#ifndef ESL_COMPONENTS_TRANSFORM_H
#define ESL_COMPONENTS_TRANSFORM_H

#include "eslib/common.h"
#include "eslib/SharedPtr.h"
#include "eslib/base/Component.h"
#include "eslib/math/Matrix4.h"
#include "eslib/math/Vector3.h"
#include "eslib/math/Quaternion.h"

NS_ESLIB_BEGIN

class Transform: public Component
{
public:
    Transform();
	virtual ~Transform();
    
    Transform(const Transform& rhs);
    Transform& operator=(const Transform& rhs);
    
    virtual Component* clone() const;
    
    virtual const CompIDType& getFamilyID() const;
    
	virtual const CompIDType& getComponentID() const;
    
public:
    const Vector3& getPosition() const;
    void setPosition(const Vector3 &pos);
    void setPosition(f32 x, f32 y, f32 z);
    
    const Vector3& getScale() const;
    void setScale(const Vector3 &scale);
    void setScale(f32 scale);
    
    const Quaternion& getRotation() const;
    void setRotation(const Quaternion& rot);
    void setRotation(const Vector3& axis, f32 degree);
    
    const Matrix4& getRelativeTransform();
    
    void updateAbsoluteTransform(bool updateChildren);
    
    const Matrix4& getAbsoluteTransform();
    
    
    void setMVPMatrix(const Matrix4& mvp);
	Matrix4& getMVPMatrix();
    
private:    
    Vector3 m_translation;
    Vector3 m_scale;
    Quaternion m_rotation;
    
    Matrix4 m_relativeTransform;
    
    Matrix4 m_absoluteTransform;

    Matrix4 m_matMVP;
    
    enum ETransformFlag
    {
        ETransformTranslationChanged = 1,
        ETransformRotationChanged = ETransformTranslationChanged<<1,
        ETransformScaleChanged = ETransformRotationChanged<<1,
        ERelativeTransformChanged = ETransformTranslationChanged | ETransformRotationChanged | ETransformScaleChanged,
        EAbsoluteTransformChanged = ETransformScaleChanged<<1,
        ETransformAllDirty = ERelativeTransformChanged | EAbsoluteTransformChanged,
    };
    
    int m_flag;
    
    void updateRelativeTransform();
};


NS_ESLIB_END

#endif //ESL_COMPONENTS_TRANSFORM_H

