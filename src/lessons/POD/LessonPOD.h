#ifndef __LESSON_POD__
#define __LESSON_POD__

#include "LessonBase.h"

class LessonPOD:public LessonBase
{
public:
	virtual int onInit();
	virtual void draw();
	virtual void update(float dt);
	virtual const char* getLessonName() { return "POD Test"; }
};


#endif