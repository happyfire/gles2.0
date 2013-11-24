#ifndef __LESSON_CUBE__
#define __LESSON_CUBE__

#include "../LessonBase.h"

class LessonCube:public LessonBase
{
public:
	virtual int onInit();
	virtual void draw();
	virtual void update(float dt);
	virtual const char* getLessonName() { return "Cube"; }
};


#endif