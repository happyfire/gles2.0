#ifndef __LESSON_MD2__
#define __LESSON_MD2__

#include "LessonBase.h"

class LessonMD2:public LessonBase
{
public:
	virtual int onInit();
	virtual void draw();
	virtual void update(float dt);
	virtual const char* getLessonName() { return "MD2"; }
};


#endif