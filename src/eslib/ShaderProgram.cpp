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

NS_ESLIB_END