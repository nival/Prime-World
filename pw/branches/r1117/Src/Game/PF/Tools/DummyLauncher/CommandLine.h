#pragma once

#include "CommonVars.h"

class CommandLine : public CommonVars
{ 
public:
	enum Params
	{
		PRM_WORK_DIR          = 0x001,
		PRM_EXE_NAME          = 0x002,
		PRM_AUTH_SERVER       = 0x004,
    PRM_PROTOCOL_VER      = 0x008,
		PRM_ARGUMENTS         = 0x010,
		PRM_UIDS              = 0x020,
		PRM_CONFIG_FILE			  = 0x040,
		PRM_USERS_CACHE_FILE	= 0x080,
    PRM_LOCALE		        = 0x100,
    PRM_SERVER		        = 0x200,
	};

	struct SnUserID
	{
		std::string snid;
		std::string snuid;
	};
	typedef std::vector<SnUserID> SnUserIDsVector;

	CommandLine();
	bool GetHasParam(Params prmMask) const { return (m_prmsFlags & prmMask) == (unsigned int)prmMask; }

	bool HasWorkDir() const { return GetHasParam(PRM_WORK_DIR); }
	bool HasExeName() const { return GetHasParam(PRM_EXE_NAME); }
	bool HasAuthServer() const { return GetHasParam(PRM_AUTH_SERVER); }
  bool HasLocale() const { return GetHasParam(PRM_LOCALE); }
  bool HasProtocolVer() const { return GetHasParam(PRM_PROTOCOL_VER); }
	bool HasArguments() const { return GetHasParam(PRM_ARGUMENTS); }
	bool HasUIDS() const { return GetHasParam(PRM_UIDS); }
	bool HasConfigFile() const { return GetHasParam(PRM_CONFIG_FILE); }
	bool HasUserCacheFile() const { return GetHasParam(PRM_USERS_CACHE_FILE); }
  bool HasServer() const { return GetHasParam(PRM_SERVER); }

	bool GetForceShowUI() const { return m_forceShowUI; }
	bool GetSilent() const { return m_silent; }
	const std::wstring& GetConfigFile() const { return m_configFile; }

	const SnUserIDsVector& GetUIDs() const { return m_uids; }
	const SnUserID* GetUID(const std::string& snid) const;

private:
  std::wstring GetStringPart(const std::wstring& prmString, size_t& position) const;

	unsigned int	m_prmsFlags;
	bool			m_forceShowUI;
	bool			m_silent;
	std::wstring	m_configFile;

	SnUserIDsVector	m_uids;
};
