// gles20.cpp : Defines the entry point for the console application.
//

#include "app.h"
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[])
{
	if(appInit())
	{
		appRun();
		appEnd();
	}
	return 0;
}

