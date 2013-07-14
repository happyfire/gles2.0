#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "esUtil.h"
#include "./platform/win32/esUtil_win.h"

///
// CreateEGLContext()
//
//    Creates an EGL rendering context and all associated elements
//
EGLBoolean CreateEGLContext ( EGLNativeWindowType hWnd, EGLDisplay* eglDisplay,
                              EGLContext* eglContext, EGLSurface* eglSurface,
                              EGLint attribList[])
{
	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLDisplay display;
	EGLContext context;
	EGLSurface surface;
	EGLConfig config;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

	// get display
	display = eglGetDisplay(GetDC(hWnd));
	if(display==EGL_NO_DISPLAY)
	{
		return EGL_FALSE;
	}

	//Initialize EGL
	if(!eglInitialize(display, &majorVersion, &minorVersion))
	{
		return EGL_FALSE;
	}

	//Get configs num
	if(!eglGetConfigs(display, NULL, 0, &numConfigs))
	{
		return EGL_FALSE;
	}

	//Choose config
	if(!eglChooseConfig(display, attribList, &config, 1, &numConfigs))
	{
		return EGL_FALSE;
	}

	//Create a surface
	surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
	if(surface==EGL_NO_SURFACE)
	{
		return EGL_FALSE;
	}

	//Create a GL context
	context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
	if(context==EGL_NO_CONTEXT)
	{
		return EGL_FALSE;
	}

	//Make the context current
	if(!eglMakeCurrent(display, surface, surface, context))
	{
		return EGL_FALSE;
	}

	*eglDisplay = display;
	*eglSurface = surface;
	*eglContext = context;

	return EGL_TRUE;
}

// Public functions

void ESUTIL_API esInitContext(ESContext *esContext)
{
	if(esContext!=NULL)
	{
		memset(esContext, 0, sizeof(ESContext));
	}
}

GLboolean ESUTIL_API esCreateWindow(ESContext *esContext, const char* title, GLint width, GLint height, GLuint flags)
{
	EGLint attribList[] =
	{
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE, (flags & ES_WINDOW_ALPHA)?8:EGL_DONT_CARE,
		EGL_DEPTH_SIZE, (flags & ES_WINDOW_DEPTH)?8:EGL_DONT_CARE,
		EGL_STENCIL_SIZE, (flags & ES_WINDOW_STENCIL)?8:EGL_DONT_CARE,
		EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE)?1:0,
		EGL_NONE
	};	

	if(esContext==NULL)
	{
		return GL_FALSE;
	}	

	esContext->width = width;
	esContext->height = height;

	if(!WinCreate(esContext, title))
	{
		return GL_FALSE;
	}

	

	if(!CreateEGLContext(esContext->hWnd,
						&esContext->eglDisplay,
						&esContext->eglContext,
						&esContext->eglSurface,
						attribList))
	{
		return GL_FALSE;
	}	

	return GL_TRUE;
}

void ESUTIL_API esMainLoop(ESContext *esContext)
{
	WinLoop(esContext);
}

void ESUTIL_API esRegisterDrawFunc(ESContext *esContext, void (ESCALLBACK *drawFunc)(ESContext *))
{
	esContext->drawFunc = drawFunc;
}

void ESUTIL_API esRegisterUpdateFunc(ESContext *esContext, void(ESCALLBACK *updateFunc)(ESContext*, float))
{
	esContext->updateFunc = updateFunc;
}

void ESUTIL_API esRegisterKeyFunc ( ESContext *esContext,
                                    void (ESCALLBACK *keyFunc) (ESContext*, unsigned char, int, int ) )
{
   esContext->keyFunc = keyFunc;
}

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