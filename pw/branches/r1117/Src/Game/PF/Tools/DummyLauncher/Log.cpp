#include "stdafx.h"
#include "Log.h"
#include "Application.h"
#include "Convert.h"

Log	gs_Log;
Log* g_Log = &gs_Log;

//const wchar_t* logFileName = L"dummyLauncher.log";

void Log::LogEntry::Put(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	g_Log->Add(m_lineNum, m_fileName.c_str(), m_type, fmt, args);
	va_end(args);
}

Log::Log() : m_curEntry(0, "", LOG_ENTRY_NOTIFY)
{
}

Log::~Log()
{
}

Log::LogEntry& Log::GetEntry(int lineNum, const char* fileName, EntryTypes type)
{
	m_curEntry = LogEntry(lineNum, fileName, type);
	return m_curEntry;
}

void Log::Init(const char* appName, const char* logFileName)
{
	m_logFileName = logFileName;
	HANDLE h = CreateFile(Convert::FromUTF8(logFileName).c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(h);
	_timeb tm;
	_ftime64_s(&tm);
	char buff[100];
	ctime_s(buff, 100, &tm.time);
	int len = strlen(buff);
	if(len > 0 && (buff[len-1]=='\r' || buff[len-1]=='\n'))
		buff[len-1] = 0;
	LOG("--- Application %s inits log at %s ---", appName, buff);
}

void Log::Done()
{
	_timeb tm;
	_ftime64_s(&tm);
	char buff[100];
	ctime_s(buff, 100, &tm.time);
	int len = strlen(buff);
	if(len > 0 && (buff[len-1]=='\r' || buff[len-1]=='\n'))
		buff[len-1] = 0;
	LOG("--- Log finished at %s ---", buff);
}

void Log::Add(int lineNum, const char* fileName, EntryTypes type, const char* fmt, const va_list& args)
{
	FILE* logF = NULL;
	fopen_s( &logF, m_logFileName.c_str(), "a+" );
	_timeb tim;
	_ftime64_s(&tim);
	tm tmConv;
	_gmtime64_s(&tmConv, &tim.time);
//	char buff[100];
	const char* prefix = " ";
	switch(type)
	{
	case LOG_ENTRY_NOTIFY:
		prefix = "N";
		break;
	case LOG_ENTRY_WARNING:
		prefix = "W";
		break;
	case LOG_ENTRY_ERROR:
		prefix = "E";
		break;
	case LOG_ENTRY_FATAL:
		prefix = "F";
		break;
	}
	std::string normalizedFileName = fileName;
	int len = normalizedFileName.length();
	if(len > 20)
		normalizedFileName = normalizedFileName.substr(len - 20);
	else
		normalizedFileName = std::string((size_t)(20 - len), (char)' ') + normalizedFileName;
	fprintf(logF, "%s[%02d:%02d:%02d.%03d] %s:%04d ", prefix, tmConv.tm_hour, tmConv.tm_min, tmConv.tm_sec, tim.millitm, normalizedFileName.c_str(), lineNum);

//	fwrite(buff, 1, strlen(buff), logF);
//  ("%s", buff);

	vfprintf( logF, fmt, args );

	fwrite("\n", 1, 1, logF);
	fflush(logF);
	fclose(logF);
}
