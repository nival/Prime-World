#pragma once


class Log
{
public:
	enum EntryTypes
	{
		LOG_ENTRY_NOTIFY,
		LOG_ENTRY_WARNING,
		LOG_ENTRY_ERROR,
		LOG_ENTRY_FATAL,
	};

	class LogEntry
	{
	public:
		void Put(const char* fmt, ...);
	private:
		LogEntry(int lineNum, const char* fileName, EntryTypes type) :
		   m_lineNum(lineNum), m_fileName(fileName), m_type(type)
		   {
		   }
		int m_lineNum;
		EntryTypes m_type;
		std::string m_fileName;
		friend class Log;
	};

	Log();
	~Log();

	void Init(const char* appName, const char* logFileName);
	void Done();

	LogEntry& GetEntry(int lineNum, const char* fileName, EntryTypes type);
private:
	typedef std::vector<_variant_t> VariantsVector;
	void Add(int lineNum, const char* fileName, EntryTypes type, const char* fmt, const va_list& args);
//	void AddInternal(const std::string& txt, const VariantsVector& args);
	LogEntry m_curEntry;
	std::string m_logFileName;
};

extern Log* g_Log;

#define LOG g_Log->GetEntry(__LINE__, __FILE__, Log::LOG_ENTRY_NOTIFY).Put
#define LOG_WARNING g_Log->GetEntry(__LINE__, __FILE__, Log::LOG_ENTRY_WARNING).Put
#define LOG_ERROR g_Log->GetEntry(__LINE__, __FILE__, Log::LOG_ENTRY_ERROR).Put
