#ifndef ESL_RENDERER_H
#define ESL_RENDERER_H

#include "glcommon.h"
#include "ISingleton.h"

NS_ESLIB_BEGIN

ESL_FORWARD_PTR(Shader)


class Renderer: public ISingleton<Renderer>
{
public:
	Renderer();
	virtual ~Renderer();

	void drawMesh();
};



NS_ESLIB_END

#endif //ESL_RENDERER_H