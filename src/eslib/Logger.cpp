#include "Logger.h"
#include <stdio.h>
#include <fstream>
#include <stdarg.h>
#include <string>
#include "config.h"

#if defined(ESL_DEVICE_WIN32)
#include <windows.h>
#endif

NS_ESLIB_BEGIN

LogFile::LogFile(const std::string& logFileName)
{
	m_ostrm.open(logFileName.c_str()) ; 
}

LogFile::~LogFile()
{
	writeLine("-------------------------") ;
	writeLine("End of log.") ;
	m_ostrm.close() ;
}

void LogFile::writeLine(const char* log)
{
	m_ostrm<<log<<std::endl ;
}

void LogFile::log(const char* log,...)
{
	va_list va;
	char str[1024];

	va_start(va,log);
	vsprintf(str,log,va);
	va_end(va);

	m_ostrm<<str<<std::endl ;
}

void LogFile::logList(const char* log, va_list va)
{
	char str[1024];

	vsprintf(str,log,va);	

	m_ostrm<<str ;
};

///////////////////////////////////////////////////////////////

Logger::Logger()
	:m_logFile(0)
{	
#ifdef ESL_DEBUG
	m_logFile = new LogFile("eslib_d.log");
#else
	m_logFile = new LogFile("eslib.log");
#endif
	memset(m_buffer, 0, sizeof(m_buffer));

	m_logFile->writeLine("------------ eslib Log File ---------------");	
}

Logger::~Logger()
{
	delete m_logFile;
}

void Logger::enableGroup(const char* group, bool enable)
{
	m_groupSwitchs[group] = enable;
}

bool Logger::isGroupEnabled(const char* group) const
{
	GroupSwitch::const_iterator it = m_groupSwitchs.find(group);
	if (it != m_groupSwitchs.end()) 
	{
		return it->second;
	} 
	else 
	{
		return false;
	}
}

void Logger::logOut(const char* group, const char* fmt, ...)
{
	if(!isGroupEnabled(group))
		return;

	int index = sprintf(m_buffer, "[%s]", group);
	va_list va; 
	va_start (va, fmt); 	
	vsprintf(m_buffer+index,fmt,va);
	va_end (va);

	m_logFile->writeLine(m_buffer);	
}

void Logger::logOutCodeLine(const char* file, int line, const char* group, const char* fmt, ...)
{
	if(!isGroupEnabled(group))
		return;

	int index = sprintf(m_buffer, "%s(%d):[%s]", file, line, group);
	va_list va; 
	va_start (va, fmt); 	
	vsprintf(m_buffer+index,fmt,va);
	va_end (va); 	

	m_logFile->writeLine(m_buffer);
}

void Logger::debugOut(const char* group, const char* fmt, ...)
{
#if defined(ESL_DEBUG) 
	if(!isGroupEnabled(group))
		return;
	
	int index = sprintf(m_buffer, "[%s]", group);
	va_list va; 
	va_start (va, fmt); 	
	vsprintf(m_buffer+index,fmt,va);
	va_end (va); 	

#if defined(ESL_DEVICE_WIN32)
	OutputDebugStringA(m_buffer);
	OutputDebugStringA("\n");
#else
	printf(m_buffer);
	printf("\n");
#endif

#endif //ESL_DEBUG
}

void Logger::debugOutCodeLine(const char* file, int line, const char* group, const char* fmt, ...)
{
#if defined(ESL_DEBUG)
	if(!isGroupEnabled(group))
		return;
	
	int index = sprintf(m_buffer, "%s(%d):[%s]", file, line, group);
	va_list va; 
	va_start (va, fmt); 	
	vsprintf(m_buffer+index,fmt,va);
	va_end (va); 	

#if defined(ESL_DEVICE_WIN32)
	OutputDebugStringA(m_buffer);	
	OutputDebugStringA("\n");
#else
	printf(m_buffer);
	printf("\n");
#endif

#endif //ESL_DEBUG
}

NS_ESLIB_END