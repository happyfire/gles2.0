#ifndef __LESSON_POD__
#define __LESSON_POD__

#include "../LessonBase.h"

class LessonPOD:public LessonBase
{
public:
	virtual int onInit(ESContext* esContext);
	virtual void draw(ESContext* esContext);
	virtual void update(ESContext* esContext, float dt);
	virtual const char* getLessonName() { return "POD Test"; }
};


#endif