#ifndef ESL_COMPONENTS_TRANSFORM_H
#define ESL_COMPONENTS_TRANSFORM_H

#include "eslib/common.h"
#include "eslib/SharedPtr.h"
#include "eslib/base/Component.h"
#include "eslib/math/Matrix4.h"

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
	
	virtual void update();
    
public:
    void setMVPMatrix(const Matrix4& mvp);
	Matrix4& getMVPMatrix();
    
private:
	Transform* m_parent;

    Matrix4 m_matMVP;
};


NS_ESLIB_END

#endif //ESL_COMPONENTS_TRANSFORM_H

