#include "LessonDelegate.h"
#include "LessonFactory.h"

LessonDelegate::LessonDelegate()
{

}

LessonDelegate::~LessonDelegate()
{

}

bool LessonDelegate::appInit()
{
	return GetLesson()->onInit();
}

void LessonDelegate::appUpdate(float dt)
{
	GetLesson()->update(dt);
}

void LessonDelegate::appRender()
{
	GetLesson()->draw();
}

void LessonDelegate::appWillClose()
{
	delete GetLesson();
}