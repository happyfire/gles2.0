#ifndef ESL_I_APPDELEGATE_H
#define ESL_I_APPDELEGATE_H

#include "common.h"

NS_ESLIB_BEGIN

class IAppDelegate
{	
public:		
	virtual ~IAppDelegate(){}

	virtual bool appInit() = 0;
	
	virtual void appUpdate(float dt) = 0;

	virtual void appFixUpdate(float dt){}

	virtual void appRender() = 0;

	virtual void appWillClose() = 0;
};


NS_ESLIB_END

#endif //ESL_I_APPDELEGATE_H

