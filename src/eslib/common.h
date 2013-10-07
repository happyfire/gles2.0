#ifndef ESLIB_COMMON_H
#define ESLIB_COMMON_H

#include "config.h"

//sys includes
#include <string>
#include <vector>
#include <list>
#include <map>
#include <cassert>

#define NS_ESLIB eslib
#define NS_ESLIB_BEGIN namespace NS_ESLIB {
#define NS_ESLIB_END }
#define USING_NS_ESLIB using namespace NS_ESLIB;

NS_ESLIB_BEGIN

	//basic types
#if defined (ESL_DEVICE_WIN32)

	typedef char				c8;
	typedef unsigned char		u8;
	typedef signed char			s8;
	typedef unsigned short		u16;
	typedef signed short		s16;
	typedef unsigned int		u32;
	typedef signed int			s32;
	typedef unsigned __int64	u64;
	typedef signed __int64		s64;
	typedef float				f32;
	typedef double				f64;	

#elif defined (ESL_DEVICE_IOS) || defined (ESL_DEVICE_ANDROID)

	typedef char				c8;
	typedef unsigned char		u8;
	typedef signed char			s8;
	typedef unsigned short		u16;
	typedef signed short		s16;
	typedef unsigned int		u32;
	typedef signed int			s32;
	typedef unsigned long long	u64;
	typedef signed long long	s64;
	typedef float				f32;
	typedef double				f64;

#endif

	//string types
	typedef std::string stringc;
	typedef std::wstring stringw;

	//container types
#define array_t		std::vector
#define list_t		std::list
#define map_t		std::map

NS_ESLIB_END

#define null 0

#define ForEach(_type, _container, _it) for (_type::iterator _it = _container.begin(), _end = _container.end(); _it != _end; ++_it)
#define ForEachC(_type, _container, _it) for (_type::const_iterator _it = _container.begin(), _end = _container.end(); _it != _end; ++_it)

//debug mode define
#if defined (ESL_DEVICE_WIN32) && defined(_DEBUG)
#define ESL_DEBUG
#endif

#ifdef ESL_DEBUG
#define ESL_DEBUG_BREAK_IF(condition) assert(!(condition))
#define ESL_ASSERT(condition) assert(condition)
#else
#define ESL_DEBUG_BREAK_IF(condition)
#define ESL_ASSERT(condition)
#endif

#define ESL_SAFE_DEL(p)					do{ if (p) { delete (p); p = NULL; } }while(false)
#define ESL_SAFE_DEL_ARRAY(p)			do{ if (p) { delete[] (p); p = NULL; } }while(false)


/// Use this define to forward declare a class and its smart pointer.
#define ESL_FORWARD_PTR(className)                        \
class className;                                      \
	typedef SharedPtr< className > className##Ptr;              \
	typedef SharedPtr< const className > className##ConstPtr;

#include "Logger.h"

#if defined (ESL_DEVICE_WIN32)
#define ESL_DBG(group, fmt, ...) NS_ESLIB::Logger::getInstance().debugOut(group, fmt, __VA_ARGS__);
#define ESL_DBGL(group, fmt, ...) NS_ESLIB::Logger::getInstance().debugOutCodeLine(__FILE__, __LINE__, group, fmt, __VA_ARGS__);
#define ESL_LOG(group, fmt, ...) NS_ESLIB::Logger::getInstance().logOut(group, fmt, __VA_ARGS__);
#define ESL_LOGL(group, fmt, ...) NS_ESLIB::Logger::getInstance().logOutCodeLine(__FILE__, __LINE__, group, fmt, __VA_ARGS__);
#else
#define ESL_DBG(group, fmt, args...) NS_ESLIB::Logger::getInstance().debugOut(group, fmt, ##args);
#define ESL_DBGL(group, fmt, args...) NS_ESLIB::Logger::getInstance().debugOutCodeLine(__FILE__, __LINE__, group, fmt, ##args);
#define ESL_LOG(group, fmt, args...) NS_ESLIB::Logger::getInstance().logOut(group, fmt, ##args);
#define ESL_LOGL(group, fmt, args...) NS_ESLIB::Logger::getInstance().logOutCodeLine(__FILE__, __LINE__, group, fmt, ##args);
#endif



#endif //ESLIB_COMMON_H
