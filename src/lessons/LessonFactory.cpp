#include "LessonFactory.h"
#include "./HelloTriangle/LessonHelloTriangle.h"
#include "./Cube/LessonCube.h"
#include "./MD2/LessonMD2.h"
#include "./POD/LessonPOD.h"

//#define CURRENT_LESSON_CLASS LessonHelloTriangle
//#define CURRENT_LESSON_CLASS LessonCube
#define CURRENT_LESSON_CLASS LessonMD2
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