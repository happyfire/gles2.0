#ifndef ESL_SHADER_H
#define ESL_SHADER_H

#include "BaseObject.h"
#include "sharedPtr.h"
#include "glcommon.h"


NS_ESLIB_BEGIN

ESL_FORWARD_PTR(Shader)

//Shader class, vertex or fragment shader

class Shader: public BaseObject
{
public:
	Shader();
	virtual ~Shader();

	bool create(GLenum type, const char *shaderSrc);
	bool isValid();
	GLuint getShaderObject();
	GLenum getType();
	
private:
	GLenum m_type;
	GLuint m_shaderObject;
};

		

NS_ESLIB_END

#endif //ESL_SHADER_H