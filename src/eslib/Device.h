#ifndef ESL_IDEVICE_H
#define ESL_IDEVICE_H

#include "common.h"
#include "ISingleton.h"

NS_ESLIB_BEGIN


class Device: public ISingleton<Device>
{
public:
	Device();
	virtual ~Device();
    
	virtual stringc getReadFilePath();
};

NS_ESLIB_END

#endif //ESL_IDEVICE_H
