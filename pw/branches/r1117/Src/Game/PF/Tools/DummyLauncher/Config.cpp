#include "stdafx.h"
#include "Config.h"
#include "Convert.h"
#include "Application.h"

Config::Config() 
	: m_lastError(S_OK)
{
	m_usersCacheFile = L"DummyLauncher.cache";
}

Config::~Config()
{
}

bool Config::Load( const std::wstring& cfgFilePath )
{
	m_fileName = cfgFilePath;
	HANDLE file = CreateFile(cfgFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (file == INVALID_HANDLE_VALUE)
	{
		m_lastError = _com_error(HRESULT_FROM_WIN32(GetLastError()));
		return false;
	}

	DWORD size = GetFileSize(file, NULL);
	std::string fileBuffer(size + 1, 0);

	ReadFile(file, (void*)fileBuffer.data(), size, &size, NULL);
	CloseHandle(file);

	char* nextToken = NULL;
	char* curLine = strtok_s((char*)fileBuffer.c_str(), "\r\n", &nextToken);
	std::string curSN;
	while(curLine)
	{
		ParseLine(curLine, curSN);
		curLine = strtok_s(NULL, "\r\n", &nextToken);
	}
	return true;
}

//bool Config::Save()
//{
//	std::vector<std::wstring> lines;
//	lines.push_back( L"// Dummy launcher config file" );
//	lines.push_back( L"" );
//	lines.push_back( L"WorkDir = " + m_workDir );
//	lines.push_back( L"ExeName = " + m_exeName );
//	lines.push_back( L"AuthServer = " + m_authServer );
//	lines.push_back( L"ProtocolVersion = " + m_protocolVer );
//	lines.push_back( L"UsersCacheFile = " + m_usersCacheFile );
//	lines.push_back( L"Arguments = " + m_arguments );
//
//	return true;
//}

bool Config::ParseLine(char* line, std::string& curSN)
{
	std::string trimedLine = Convert::Trim(line);
	if (trimedLine[0]==L'[')
	{
		int pos = trimedLine.find_last_of(L']');
		if (pos == std::wstring::npos)
			pos = trimedLine.length();
		curSN = std::string(trimedLine.c_str() + 1, pos - 1);
	}
	else if(trimedLine[0]==L'/' && trimedLine[1]==L'/')
	{
		return true;
	}
	else
	{
		std::string name;
		std::string value;
		int pos = trimedLine.find('=');
		if (pos == std::wstring::npos)
		{
			name = trimedLine;
		}
		else
		{
			trimedLine[pos] = 0;
			name = Convert::Trim((char*)trimedLine.c_str());
			value = Convert::Trim((char*)trimedLine.c_str() + pos + 1);
		}

		if (curSN.empty())
		{
			if( name == "WorkDir" )
        m_workDir = Convert::FromUTF8(value);
			else if( name == "ExeName" )
				m_exeName = Convert::FromUTF8(value);
			else if( name == "Arguments" )
				m_arguments = Convert::FromUTF8(value);
			else if( name == "AuthServer" )
				m_authServer = Convert::FromUTF8(value);
			else if( name == "ProtocolVersion" )
				m_protocolVer = Convert::FromUTF8(value);
			else if( name == "UsersCacheFile" )
				m_usersCacheFile = Convert::FromUTF8(value);
      else if( name == "Locale" )
        m_locale = Convert::FromUTF8(value);
		}
    else
    {
      name = curSN + "." + name;
    }
    m_values[name] = value;
	}

	if(!m_authServer.empty() && m_authServer[m_authServer.length() - 1] != L'/')
		m_authServer += L"/";

	return true;
}

const char* Config::GetValue(const std::string& name) const
{
  ValuesMap::const_iterator iter = m_values.find(name);
  if(iter == m_values.end())
    return NULL;
  return iter->second.c_str();
}
