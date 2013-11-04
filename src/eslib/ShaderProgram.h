#ifndef ESL_SHADERPROGRAM_H
#define ESL_SHADERPROGRAM_H

#include "BaseObject.h"
#include "sharedPtr.h"
#include "glcommon.h"
#include <map>

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

	GLint getUniformLocation(const char* name);

	void setUniform(const char* name, int x);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, float x, float y, float z, float w);
	void setUniformMatrix4fv(const char* name, const float* data);

protected:
	void findOutUniforms();

private:
	GLuint m_programObject;
	ShaderPtr m_vs;
	ShaderPtr m_fs;

	std::map<std::string, GLint> m_uniforms;
};



NS_ESLIB_END

#endif //ESL_SHADERPROGRAM_H