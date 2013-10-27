#include "ShaderProgram.h"
#include "Shader.h"

NS_ESLIB_BEGIN

ShaderProgram::ShaderProgram()
:m_programObject(0)
{
}

ShaderProgram::~ShaderProgram()
{
	m_vs.reset();
	m_fs.reset();

	if(m_programObject!=0)
	{
		glDeleteProgram(m_programObject);
		m_programObject = 0;
	}
}

bool ShaderProgram::create(const ShaderPtr& vs, const ShaderPtr& fs)
{
	if(!vs.isValid() || !fs.isValid())
	{
		ESL_DBG("gl","Error create shader program because shader is not valid.");
		return false;
	}

	m_vs = vs;
	m_fs = fs;

	m_programObject = glCreateProgram();

	if(m_programObject==0){
		ESL_DBG("gl","Error create shader program.");
		return false;
	}

	glAttachShader(m_programObject, m_vs->getShaderObject());
	glAttachShader(m_programObject, m_fs->getShaderObject());

	glLinkProgram(m_programObject);

#if defined (ESL_DEBUG)
	do
	{	
		GLint linked;
		GLint logLength;

		// Check the link status
		glGetProgramiv(m_programObject, GL_LINK_STATUS, &linked);

		if(linked)
			break;

		glGetProgramiv(m_programObject, GL_INFO_LOG_LENGTH, &logLength);

		if(logLength>0)
		{
			char *log = (char*)malloc(logLength);

			glGetProgramInfoLog(m_programObject, logLength, &logLength, log);

			ESL_DBG("gl","Error linking shader program:\n%s\n", log);

			free(log);
		}

		glDeleteProgram(m_programObject);
		m_programObject = 0;
		return false;
	}
	while(0);
#endif

	findOutUniforms();

	return true;

}

bool ShaderProgram::isValid()
{
	return m_programObject!=0;
}

GLuint ShaderProgram::getProgramObject()
{
	return m_programObject;
}

GLint ShaderProgram::getUniformLocation(const char* name)
{
	if(m_uniforms.find(name)!=m_uniforms.end())
		return m_uniforms[name];
	else
		return -1;
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z)
{
	GLint location = getUniformLocation(name);
	if(location>=0)
	{
		glUniform3f(location, x, y, z);
	}
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z, float w)
{
	GLint location = getUniformLocation(name);
	if(location>=0)
	{
		glUniform4f(location, x, y, z, w);
	}
}

void ShaderProgram::findOutUniforms()
{
	m_uniforms.clear();

	GLint maxUniformLen;
	GLint numUniforms;
	char *uniformName;
	GLint index;

	glGetProgramiv(m_programObject, GL_ACTIVE_UNIFORMS, &numUniforms);
	glGetProgramiv(m_programObject, GL_ACTIVE_UNIFORM_MAX_LENGTH, 
		&maxUniformLen);
	uniformName = new char[sizeof(char) * maxUniformLen];
	for(index = 0; index < numUniforms; index++)
	{
		GLint size;
		GLenum type;
		GLint location;
		// Get the Uniform Info
		glGetActiveUniform(m_programObject, index, maxUniformLen, NULL, 
			&size, &type, uniformName);
		// Get the uniform location
		location = glGetUniformLocation(m_programObject, uniformName);

		m_uniforms[uniformName] = location;

		switch(type)
		{
		case GL_FLOAT:
			// ...
			break;
		case GL_FLOAT_VEC2:
			// ...
			break;
		case GL_FLOAT_VEC3:
			// ...
			break;
		case GL_FLOAT_VEC4:
			// ...
			break;

		case GL_INT:
			// ...
			break;
			// ... Check for all the types ...

		default:
			// Unknown type
			break;
		}      
	}   

	delete[] uniformName;

}

NS_ESLIB_END