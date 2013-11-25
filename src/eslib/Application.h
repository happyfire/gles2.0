#ifndef ESL_APPLICATION_H
#define ESL_APPLICATION_H

#include "common.h"

NS_ESLIB_BEGIN

class IAppDelegate;

struct AppConfig
{
	IAppDelegate* mDelegate;

	int mScreenWidth;
	int mScreenHeight;
	stringc mWindowTitle; 

	AppConfig()
		:mDelegate(null)
		,mScreenWidth(1024)
		,mScreenHeight(768)
		,mWindowTitle("GLES App")
	{
	}
};

class Application
{
public:
	static void setConfig(const AppConfig& config);
	static bool init();
	static void exit();
	static void update(float dt);
	static void fixUpdate(float dt);
	static void render();

	static const AppConfig& GetConfig();
    static void SetScreenSize(int screenWidth, int screenHeight);
	static int GetScreenWidth() { return s_config.mScreenWidth; }
	static int GetScreenHeight() { return s_config.mScreenHeight; }

private:
	static IAppDelegate* s_appDelegate;
	static AppConfig s_config;
};



NS_ESLIB_END

#endif //ESL_APPLICATION_H
