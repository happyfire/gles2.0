#ifndef __LESSON_HELLO_TRIANGLE__
#define __LESSON_HELLO_TRIANGLE__

#include "../LessonBase.h"

class LessonHelloTriangle:public LessonBase
{
public:
	virtual int onInit();
	virtual void draw();	
	virtual void update(float dt);
	virtual const char* getLessonName() { return "Hello Triangle"; }
};

#endif