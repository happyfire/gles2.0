#ifndef _LESSON_BASE__
#define _LESSON_BASE__

#include "esUtil.h"
#include <stdlib.h>

class LessonBase
{
public:
	virtual int onInit(ESContext *esContext){ return 0; }
	virtual void draw(ESContext *esContext){}
	virtual void update(ESContext *esContext, float dt){}
	virtual const char* getLessonName() { return "OpenGL ES2.0"; }
};

typedef struct
{
	GLuint programObject;
} UserData;

#endif //_LESSON_BASE__
