#include "eslib/IAppDelegate.h"

USING_NS_ESLIB;

class LessonDelegate: public IAppDelegate
{
public:
	LessonDelegate();
	virtual ~LessonDelegate();

	virtual bool appInit();

	virtual void appUpdate(float dt);

	virtual void appRender();

	virtual void appWillClose();
};