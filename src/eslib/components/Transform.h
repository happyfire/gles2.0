#ifndef ESL_COMPONENTS_TRANSFORM_H
#define ESL_COMPONENTS_TRANSFORM_H

#include "eslib/common.h"
#include "eslib/SharedPtr.h"
#include "eslib/base/Component.h"
#include "esUtil/esUtil.h"

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
    void setMVPMatrix(const ESMatrix& mvp);
	ESMatrix& getMVPMatrix();
    
private:
    ESMatrix m_matMVP;
};


NS_ESLIB_END

#endif //ESL_COMPONENTS_TRANSFORM_H
