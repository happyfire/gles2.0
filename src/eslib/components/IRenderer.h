//Interface of renderer components

#ifndef ESL_COMPONENTS_IRENDERER_H
#define ESL_COMPONENTS_IRENDERER_H

#include "eslib/common.h"
#include "eslib/SharedPtr.h"
#include "eslib/base/Component.h"
#include "esUtil/esUtil.h"

NS_ESLIB_BEGIN


class IRenderer: public Component
{
public:
	IRenderer();
	virtual ~IRenderer();

	virtual const CompIDType& getFamilyID() const;

public:
	virtual void setTransform(const ESMatrix &transform) = 0;
	
	virtual void render() = 0;
};


NS_ESLIB_END

#endif //ESL_COMPONENTS_IRENDERER_H
