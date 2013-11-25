#include <stdio.h>
#include <stdlib.h>
#include "esUtil.h"

GLuint esLoadShader(GLenum type, const char *shaderSrc)
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

			free(infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint esCreateProgram(GLuint vs, GLuint fs)
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

			free(log);
		}

		glDeleteProgram(name);
		return 0;
	}
	while(0);
#endif

	return name;
}

GLuint esCreateBufferObject(GLenum type, GLsizeiptr size, const GLvoid *data)
{
	GLuint buffer;

	glGenBuffers(1, &buffer);

	glBindBuffer(type, buffer);
	glBufferData(type, size, data, GL_STATIC_DRAW);

	return buffer;
}
