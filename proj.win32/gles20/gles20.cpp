// gles20.cpp : Defines the entry point for the console application.
//

#include <tchar.h>
#include "eslib/Application.h"
#include "eslib/win32/GLESAppFramework.h"
#include "lessons/LessonDelegate.h"

USING_NS_ESLIB;

int _tmain(int argc, _TCHAR* argv[])
{

	LessonDelegate delegate;

	AppConfig config;
	config.mDelegate = &delegate;
	config.mScreenWidth = 480;
	config.mScreenHeight = 320;
	
	Application::setConfig(config);

	esAppRunLoop();

	return 0;
}

