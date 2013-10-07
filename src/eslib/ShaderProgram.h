#ifndef ESL_SHADERPROGRAM_H
#define ESL_SHADERPROGRAM_H

#include "BaseObject.h"
#include "sharedPtr.h"
#include "glcommon.h"


NS_ESLIB_BEGIN

ESL_FORWARD_PTR(ShaderProgram)
ESL_FORWARD_PTR(Shader)

//Shader Program class

class ShaderProgram: public BaseObject
{
public:
	ShaderProgram();
	virtual ~ShaderProgram();

	bool create(const ShaderPtr& vs, const ShaderPtr& fs);
	bool isValid();
	GLuint getProgramObject();

private:
	GLuint m_programObject;
	ShaderPtr m_vs;
	ShaderPtr m_fs;
};



NS_ESLIB_END

#endif //ESL_SHADERPROGRAM_H