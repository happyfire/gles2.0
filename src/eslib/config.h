#ifndef ESLIB_CONFIG_H
#define ESLIB_CONFIG_H

#ifdef WIN32

#define ESL_DEVICE_WIN32

#pragma warning (disable : 4996)  //_CRT_SECURE_NO_WARNINGS

#elif defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) //Note:these are defined in a header file, not by compile, so when used in a project not include header file, you should define ES_DEVICE_IOS in build setting.

#ifndef ESL_DEVICE_IOS
#define ESL_DEVICE_IOS
#endif

#else

#define ESL_DEVICE_ANDROID

#endif


#endif //ESLIB_CONFIG_H