#include "Shader.h"

NS_ESLIB_BEGIN

Shader::Shader()
:m_shaderObject(0)
{
}

Shader::~Shader()
{
	if(m_shaderObject!=0)
	{
		glDeleteShader(m_shaderObject);
		m_shaderObject = 0;
	}
}

bool Shader::create(GLenum type, const char *shaderSrc)
{
	GLint compiled;

	//Create the shader object
	m_type = type;
	m_shaderObject = glCreateShader(type);

	if(m_shaderObject==0){
		ESL_DBG("gl","Error create shader for type %d", type);
		return false;
	}

	//Load the shader source
	glShaderSource(m_shaderObject, 1, &shaderSrc, NULL);

	//Compile the shader
	glCompileShader(m_shaderObject);

	//Check the compile status
	glGetShaderiv(m_shaderObject, GL_COMPILE_STATUS, &compiled);

	if(!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(m_shaderObject, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen>1)
		{
			char *infoLog = (char*)malloc(sizeof(char)*infoLen);

			glGetShaderInfoLog(m_shaderObject, infoLen, NULL, infoLog);
			
			ESL_DBG("gl","Error compiling shader:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteShader(m_shaderObject);
		m_shaderObject = 0;
		return false;
	}

	return true;
}

bool Shader::isValid()
{
	return m_shaderObject!=0;
}

GLuint Shader::getShaderObject()
{
	return m_shaderObject;
}

GLenum Shader::getType()
{
	return m_type;
}

NS_ESLIB_END