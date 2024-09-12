#pragma once

#include "CommonVars.h"

class Config : public CommonVars
{
public:
	Config();
	~Config();

	bool Load( const std::wstring& cfgFilePath );
//	bool Save();

	bool ParseLine(char* line, std::string& curSN);

  const char* GetValue(const std::string& name) const;
private:
	_com_error m_lastError;
	std::wstring m_fileName;

  typedef std::map<std::string, std::string> ValuesMap;
  ValuesMap m_values;
};
