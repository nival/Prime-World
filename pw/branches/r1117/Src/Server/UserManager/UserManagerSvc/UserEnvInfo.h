#pragma once
#include <RPC/RPC.h>
#include <Network/TransportTypes.h>
#include <ClusterTypes/ClusterTypes.h>

namespace UserManager
{

  struct UserEnvInfo : public rpc::Data
  {
    SERIALIZE_ID();

    ZDATA
    ZNOPARENT(rpc::Data)
    Cluster::TUserId userid_;
    string sessionKey_;
    Transport::TServiceId sessionPath_;
    wstring username_;
    bool partialReconnect_;
    Cluster::TGameId gameid_;

    ZEND int operator&( IBinSaver &f ) { f.Add(2,&userid_); f.Add(3,&sessionKey_); f.Add(4,&sessionPath_); f.Add(5,&username_); f.Add(6, &partialReconnect_); f.Add(7, &gameid_); return 0; }

    UserEnvInfo() : userid_(Cluster::INVALID_USER_ID) {}
    UserEnvInfo(Cluster::TUserId const & _userid, string const & _sessionKey, Transport::TServiceId const & _sessionPath, wstring const & _username, bool _partialReconnect, Cluster::TGameId const & _gameid)
      :userid_(_userid), sessionKey_(_sessionKey), sessionPath_(_sessionPath), username_(_username), partialReconnect_(_partialReconnect), gameid_(_gameid)
    {}
  };

}
