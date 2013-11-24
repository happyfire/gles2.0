#include "Application.h"
#include "IAppDelegate.h"
#include "Logger.h"

NS_ESLIB_BEGIN

AppConfig Application::s_config;
IAppDelegate* Application::s_appDelegate = null;

void Application::setConfig(const AppConfig& config)
{
	ESL_ASSERT(config.mDelegate!=null);

	s_appDelegate = config.mDelegate;
	s_config = config;
}

const AppConfig& Application::GetConfig()
{
	return s_config;
}

bool Application::init()
{
	ESL_ASSERT(s_appDelegate!=null);
	return s_appDelegate->appInit();
}

void Application::exit()
{
	ESL_ASSERT(s_appDelegate!=null);
	s_appDelegate->appWillClose();

	ESL_DBG("app", "app exit");

	Logger::deleteInstance();
}

void Application::update(float dt)
{
	ESL_ASSERT(s_appDelegate!=null);
	s_appDelegate->appUpdate(dt);
}

void Application::fixUpdate(float dt)
{
	ESL_ASSERT(s_appDelegate!=null);
	s_appDelegate->appFixUpdate(dt);
}

void Application::render()
{
	ESL_ASSERT(s_appDelegate!=null);
	s_appDelegate->appRender();
}


NS_ESLIB_END
