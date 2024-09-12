#include "stdafx.h"
#include "CommandLine.h"
#include "Convert.h"

CommandLine::CommandLine()
	: m_forceShowUI(false)
	, m_silent(false)
	, m_prmsFlags(0)
{
	std::wstring cmdLine = GetCommandLine();
	size_t pos = 0;
	while(cmdLine[pos])
	{
		std::wstring part = GetStringPart(cmdLine, pos);
		if(part == L"-ui" || part == L"--show-ui" || part == L"--showUI")
		{
			m_forceShowUI = true;
		}
		else if(part == L"-s" || part == L"--silent")
		{
			m_silent = true;
		}
		else if(part == L"-wd" || part == L"--work-dir" || part == L"--WorkDir")
		{
			m_prmsFlags |= PRM_WORK_DIR;
			m_workDir = GetStringPart(cmdLine, pos);
		}
		else if(part == L"-en" || part == L"--exe-name" || part == L"--ExeName")
		{
			m_prmsFlags |= PRM_EXE_NAME;
			m_exeName = GetStringPart(cmdLine, pos);
		}
		else if(part == L"-as" || part == L"--auth-server" || part == L"--AuthServer")
		{
			m_prmsFlags |= PRM_AUTH_SERVER;
			m_authServer = GetStringPart(cmdLine, pos);
		}
    else if(part == L"-srv" || part == L"--server")
    {
      m_prmsFlags |= PRM_SERVER;
      m_server = GetStringPart(cmdLine, pos);
    }
		else if(part == L"-pv" || part == L"--protocol-version" || part == L"--ProtocolVersion")
		{
			m_prmsFlags |= PRM_PROTOCOL_VER;
			m_protocolVer = GetStringPart(cmdLine, pos);
		}
		else if(part == L"-cf" || part == L"--config")
		{
			m_prmsFlags |= PRM_CONFIG_FILE;
			m_configFile = GetStringPart(cmdLine, pos);
		}
		else if(part == L"-uc" || part == L"--users-cache" || part == L"--UsersCacheFile")
		{
			m_prmsFlags |= PRM_USERS_CACHE_FILE;
			m_usersCacheFile = GetStringPart(cmdLine, pos);
		}
    else if(part == L"-loc" || part == L"--locale" || part == L"--Locale")
    {
      m_prmsFlags |= PRM_LOCALE;
      m_locale = GetStringPart(cmdLine, pos);
    }
		else if(part == L"-a" || part == L"--aruments" || part == L"--Arguments")
		{
			m_prmsFlags |= PRM_ARGUMENTS;
			m_arguments = cmdLine.substr(pos);
			break;
		}
		else if(wcsncmp(part.c_str(), L"--uid", 5) == 0)
		{
			SnUserID newUID;
      std::wstring uidStr = GetStringPart(cmdLine, pos);
      size_t colonPos = uidStr.find(L':');
      if(colonPos != std::wstring::npos)
      {
        newUID.snid = Convert::ToUTF8(uidStr.substr(0, colonPos));
        uidStr = uidStr.substr(colonPos + 1);
        if(uidStr[0] == '\"')
        {
          colonPos = 0;
          uidStr = GetStringPart(uidStr, colonPos);
        }
        newUID.snuid = Convert::ToUTF8(uidStr);
        m_uids.push_back(newUID);
      }
		}
	}

  if(!m_uids.empty())
		m_prmsFlags |= PRM_UIDS;
}

std::wstring CommandLine::GetStringPart(const std::wstring& prmString, size_t& position) const
{
	while(prmString[position] == L' ')
		position++;
	size_t start = position;
  size_t spacePos = prmString.find(' ', start);
  size_t quotPos = prmString.find('\"', start);
  std::wstring result;
  if(spacePos == std::wstring::npos)
  {
    result = prmString.substr(position);
    position = prmString.length();
  }
  else
  {
    if(quotPos < spacePos)
    {
      // отрабатываем кавычки
      result = prmString.substr(position, quotPos - position);
      bool needQuot = (quotPos != position);
      if(needQuot)
        result += '\"';
      while(true)
      {
        position = prmString.find('\"', quotPos + 1);
        if(position == std::wstring::npos)
        {
          result += prmString.substr(quotPos + 1);
          position = prmString.length();
          needQuot = false;
          break;
        }
        else
        {
          if(prmString[position + 1] == '\"')
          {
            result += '\"';
            quotPos = position + 1;
          }
          else
          {
            result += prmString.substr(quotPos + 1, position - quotPos - 1);
            position++;
            break;
          }
        }
      }
      if(needQuot)
        result += '\"';
    }
    else
    {
      // режем по пробелу
      result = prmString.substr(position, spacePos - position);
      position = spacePos + 1;
    }
  }
	while(prmString[position] == L' ')
		position++;
	return result;
}

const CommandLine::SnUserID* CommandLine::GetUID(const std::string& snid) const
{
	for(size_t i = 0; i < m_uids.size(); i++)
	{
		if(m_uids[i].snid == snid)
			return &m_uids[i];
	}
	return NULL;
}
