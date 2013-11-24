#include "LessonFactory.h"
#include "./HelloTriangle/LessonHelloTriangle.h"
#include "./Cube/LessonCube.h"
#include "./POD/LessonPOD.h"

#define CURRENT_LESSON_CLASS LessonHelloTriangle
//#define CURRENT_LESSON_CLASS LessonCube
//#define CURRENT_LESSON_CLASS LessonPOD

static LessonBase* gLesson = NULL;

LessonBase* GetLesson()
{
	if(gLesson==NULL)
	{
		gLesson = new CURRENT_LESSON_CLASS();
	}

	return gLesson;
}