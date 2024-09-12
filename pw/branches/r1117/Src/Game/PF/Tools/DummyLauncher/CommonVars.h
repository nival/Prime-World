#pragma once

class CommonVars
{
public:
	const std::wstring& GetWorkDir() const { return m_workDir; }
	const std::wstring& GetExeName() const { return m_exeName; }
	const std::wstring& GetAuthServer() const { return m_authServer; }
	const std::wstring& GetProtocolVersion() const { return m_protocolVer; }
	const std::wstring& GetArguments() const { return m_arguments; }
  const std::wstring& GetUserCacheFile() const { return m_usersCacheFile; }
  const std::wstring& GetLocale() const { return m_locale; }
  const std::wstring& GetServer() const { return m_server; }
protected:
	std::wstring	m_workDir;
	std::wstring	m_exeName;
	std::wstring	m_authServer;
  std::wstring	m_server;
	std::wstring	m_protocolVer;
	std::wstring	m_arguments;
  std::wstring	m_usersCacheFile;
  std::wstring	m_locale;
};