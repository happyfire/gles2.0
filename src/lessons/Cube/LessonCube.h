#ifndef __LESSON_CUBE__
#define __LESSON_CUBE__

#include "../LessonBase.h"

class LessonCube:public LessonBase
{
public:
	virtual int onInit(ESContext* esContext);
	virtual void draw(ESContext* esContext);
	virtual void update(ESContext* esContext, float dt);
	virtual const char* getLessonName() { return "Cube"; }
};


#endif