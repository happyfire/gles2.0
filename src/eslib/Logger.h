#ifndef ESL_LOGGER_H
#define ESL_LOGGER_H

#include "ISingleton.h"

#include <stdio.h>
#include <fstream>
#include <stdarg.h>
#include <string>
#include <map>

NS_ESLIB_BEGIN
	
class LogFile  
{
public:
	explicit LogFile(const std::string& logFileName="eslib.log");
	~LogFile();	
	void writeLine(const char* log);	
	void log(const char* log,...) ;
	void logList(const char* log, va_list va);

private:
	std::ofstream m_ostrm ;

};

class Logger: public ISingleton<Logger>
{
public:
	Logger();
	~Logger();

	void enableGroup(const char* group, bool enable);

	bool isGroupEnabled(const char* group) const;

	void logOut(const char* group, const char* fmt, ...);
	void logOutCodeLine(const char* file, int line, const char* group, const char* fmt, ...);

	void debugOut(const char* group, const char* fmt, ...);
	void debugOutCodeLine(const char* file, int line, const char* group, const char* fmt, ...);
	
private:
	LogFile* m_logFile;
	char m_buffer[4096];

	typedef std::map<const char*, bool> GroupSwitch;

	GroupSwitch m_groupSwitchs;
};
		
NS_ESLIB_END

#endif //ESL_LOGGER_H
