#include "eslib/components/IRenderer.h"

NS_ESLIB_BEGIN

static CompIDType sFamilyID = "IRenderer";

IRenderer::IRenderer()
{

}

IRenderer::~IRenderer()
{

}

const CompIDType& IRenderer::getFamilyID() const
{
	return sFamilyID;
}



NS_ESLIB_END