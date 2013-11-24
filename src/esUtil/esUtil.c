#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "esUtil.h"

void ESUTIL_API esLogMessage(const char* formatStr, ...)
{
	va_list params;
	char buf[BUFSIZ];

	va_start(params, formatStr);
	vsprintf_s(buf, sizeof(buf), formatStr, params);

	printf("%s", buf);

	va_end(params);
}

GLuint ESUTIL_API esLoadShader(GLenum type, const char *shaderSrc)
{
	GLuint shader;
	GLint compiled;

	//Create the shader object
	shader = glCreateShader(type);

	if(shader==0)
		return 0;

	//Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	//Compile the shader
	glCompileShader(shader);

	//Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if(!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen>1)
		{
			char *infoLog = (char*)malloc(sizeof(char)*infoLen);

			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			esLogMessage("Error compiling shader:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint ESUTIL_API esCreateProgram(GLuint vs, GLuint fs)
{
	GLuint name;

	name = glCreateProgram();

	glAttachShader(name, vs);
	glAttachShader(name, fs);

	glLinkProgram(name);

#if defined (_DEBUG)
	do
	{        
		GLint linked;
		GLint logLength;

		// Check the link status
		glGetProgramiv(name, GL_LINK_STATUS, &linked);

		if(linked)
			break;

		glGetProgramiv(name, GL_INFO_LOG_LENGTH, &logLength);

		if(logLength>0)
		{
			char *log = (char*)malloc(logLength);

			glGetProgramInfoLog(name, logLength, &logLength, log);

			esLogMessage(log);

			free(log);
		}

		glDeleteProgram(name);
		return 0;
	}
	while(0);
#endif

	return name;
}

GLuint ESUTIL_API esCreateBufferObject(GLenum type, GLsizeiptr size, const GLvoid *data)
{
	GLuint buffer;

	glGenBuffers(1, &buffer);

	glBindBuffer(type, buffer);
	glBufferData(type, size, data, GL_STATIC_DRAW);

	return buffer;
}
