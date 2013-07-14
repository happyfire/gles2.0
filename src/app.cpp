

#include "lessons/LessonFactory.h"


LessonBase* g_lesson = NULL;

void DrawFunc(ESContext *esContext)
{
	if(g_lesson)
		g_lesson->draw(esContext);
}

void UpdateFunc(ESContext* esContext, float dt)
{
	if(g_lesson)
		g_lesson->update(esContext, dt);
}

UserData* gUserData;
ESContext* gEsContext;

bool appInit()
{
	gUserData = new UserData;
	gEsContext = new ESContext;

	esInitContext(gEsContext);
	gEsContext->userData = gUserData;

	g_lesson = GetLesson();

	esCreateWindow(gEsContext, g_lesson->getLessonName(), 480, 320, ES_WINDOW_RGB|ES_WINDOW_ALPHA);	


	if(!g_lesson->onInit(gEsContext))
	{
		delete g_lesson;
		return false;
	}

	esRegisterDrawFunc(gEsContext, DrawFunc);
	esRegisterUpdateFunc(gEsContext, UpdateFunc);

	return true;
}

void appRun()
{
	esMainLoop(gEsContext);
}

void appEnd()
{
	delete gUserData;
	delete gEsContext;
	delete g_lesson;
}

