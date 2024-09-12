#pragma once

#include "SocialNetInfo.h"
#include "CommandLine.h"

class UsersInfo
{
public:
  UsersInfo();
  ~UsersInfo();

  bool LoadCache();
  bool SaveCache();
  void Clear();

  template<typename T>
  RefCountPtr<T> CreateSocialNet()
  {
    SocialNetInfoPtr sn = CreateSocialNet(T::GetNameStatic());
    if(sn)
      return sn->Cast<T>();
    return NULL;
  }

  SocialNetInfoPtr CreateSocialNet(const std::string& name) const;
  SocialNetInfoPtr CreateSocialNet(const std::string& name, const std::string& snuid) const;
  void StoreSocialNet(SocialNetInfoPtr sn);

  SocialNetInfoPtr Find(const std::string& snid, const std::string& snuid);
  SocialNetInfoPtr FindByName(const std::string& snid, const std::string& name);

  void Logout();
  bool OnAuthorized(SocialNetInfoPtr socNet);

  bool IsLoggedIn() const { return !m_auid.empty(); }
  bool IsAllLoggedIn() const;

  SocialNetInfoPtr GetFromSns(const std::string& name) const;

  typedef std::vector<SocialNetInfoPtr> SocialNetInfosVector;

  const SocialNetInfosVector& GetUsersCache() const { return m_socNets; }

  const std::string& GetAUID() const { return m_auid; }
  const std::string& GetToken() const { return m_token; }
  const std::string& GetHostId() const { return m_hostId; }
  SocialNetInfoPtr GetFirstLoggedSNS() const { return m_firstLoggedSnS; }  
  std::wstring GetServer() const;


  std::wstring GenerateUniqueMachineId();

  bool LoginOnServer();

  std::string MakeCmdLine() const;
protected:
  bool AuthOnServer(SocialNetInfoPtr socNet);

  SocialNetInfosVector m_socNets;

//  std::string m_server;

  std::string m_auid;
  std::string m_token;
  std::string m_nickName;
  std::string m_hostId;
  typedef std::map<std::string, SocialNetInfoPtr> StringSocialNetsMap;
  StringSocialNetsMap m_sns;
  SocialNetInfoPtr m_firstLoggedSnS;
};
