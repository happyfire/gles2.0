//Interface of renderer components

#ifndef ESL_COMPONENTS_IRENDERER_H
#define ESL_COMPONENTS_IRENDERER_H

#include "eslib/common.h"
#include "eslib/SharedPtr.h"
#include "eslib/base/Component.h"
#include "eslib/math/Matrix4.h"

NS_ESLIB_BEGIN

class AABBox;

class IRenderer: public Component
{
public:
	IRenderer();
	virtual ~IRenderer();

	virtual const CompIDType& getFamilyID() const;

public:
	virtual void setTransform(const Matrix4 &transform) = 0;
	
	virtual void render() = 0;
    
    virtual const AABBox& getTransformedAABB() = 0;
};


NS_ESLIB_END

#endif //ESL_COMPONENTS_IRENDERER_H

