#ifndef ESLIB_ESGL_H
#define ESLIB_ESGL_H

#include "common.h"

#if defined (ESL_DEVICE_WIN32)

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#elif defined (ESL_DEVICE_IOS)

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#endif

#endif //ESLIB_ESGL_H