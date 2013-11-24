#ifndef _LESSON_BASE__
#define _LESSON_BASE__

#include <stdlib.h>

class LessonBase
{
public:
	virtual ~LessonBase(){}
	virtual int onInit(){ return 0; }
	virtual void draw(){}
	virtual void update(float dt){}
	virtual const char* getLessonName() { return "OpenGL ES2.0"; }
};


#endif //_LESSON_BASE__
