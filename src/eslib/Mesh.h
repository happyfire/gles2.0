#ifndef ESL_MESH_H
#define ESL_MESH_H

#include "BaseObject.h"
#include "sharedPtr.h"
#include "glcommon.h"


NS_ESLIB_BEGIN

ESL_FORWARD_PTR(Mesh)

class Mesh: public BaseObject
{
public:
	Mesh();
	virtual ~Mesh();



	

protected:
	GLfloat* m_vertexData;
	GLushort* m_indexData;
};



NS_ESLIB_END

#endif //ESL_SHADER_H