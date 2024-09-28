#include "stdafx.h"
#include "EnvironmentVars.h"
#include "Application.h"

static std::wstring emptyString;

EnvironmentVars::EnvironmentVars()
{
  wchar_t buffer[MAX_PATH];
  GetCurrentDirectory(MAX_PATH, buffer);
  m_workDirectory = buffer;
}

EnvironmentVars::~EnvironmentVars()
{
}

const std::wstring& EnvironmentVars::GetLocale() const
{
  if(g_App->GetCommandLine().HasLocale())
    return g_App->GetCommandLine().GetLocale();
  return g_App->GetConfig().GetLocale();
}

const std::wstring& EnvironmentVars::GetProtocolVersion() const
{
	if(g_App->GetCommandLine().HasProtocolVer())
		return g_App->GetCommandLine().GetProtocolVersion();
	return g_App->GetConfig().GetProtocolVersion();
}

const std::wstring& EnvironmentVars::GetAuthServer() const
{
	if(g_App->GetCommandLine().HasAuthServer())
		return g_App->GetCommandLine().GetAuthServer();
	return g_App->GetConfig().GetAuthServer();
}

const std::wstring& EnvironmentVars::GetExeArguments() const
{
	if(g_App->GetCommandLine().HasArguments())
		return g_App->GetCommandLine().GetArguments();
	return g_App->GetConfig().GetArguments();
}

const std::wstring& EnvironmentVars::GetUsersCacheFile() const
{
	if(g_App->GetCommandLine().HasUserCacheFile())
		return g_App->GetCommandLine().GetUserCacheFile();
	return g_App->GetConfig().GetUserCacheFile();
}

const std::wstring& EnvironmentVars::GetWorkDir() const
{
	if(g_App->GetCommandLine().HasWorkDir())
		return g_App->GetCommandLine().GetWorkDir();
  if(!g_App->GetConfig().GetWorkDir().empty())
    return g_App->GetConfig().GetWorkDir();
  return m_workDirectory;
}

const std::wstring& EnvironmentVars::GetVar(const std::string& name) const
{
  return emptyString;
}
