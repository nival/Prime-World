#pragma once

class EnvironmentVars
{
public:
	EnvironmentVars();
	~EnvironmentVars();

  const std::wstring& GetProtocolVersion() const;
  const std::wstring& GetLocale() const;
	const std::wstring& GetAuthServer() const;
	const std::wstring& GetExeArguments() const;
	const std::wstring& GetUsersCacheFile() const;
	const std::wstring& GetWorkDir() const;

  const std::wstring& GetVar(const std::string& name) const;
private:
  std::wstring m_workDirectory;
};
