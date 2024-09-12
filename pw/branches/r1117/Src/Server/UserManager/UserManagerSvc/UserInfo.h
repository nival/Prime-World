#pragma once
#include <RPC/RPC.h>
#include <ClusterTypes/ClusterTypes.h>

namespace UserManager
{
  struct UserInfo : public rpc::Data
  {
    SERIALIZE_ID();

    ZDATA
    ZNOPARENT(rpc::Data)

    Cluster::TUserId userid_;
    nstl::wstring username_;

    ZEND int operator&( IBinSaver &f ) { f.Add(2,&userid_); f.Add(3,&username_); return 0; }

    UserInfo() : userid_(Cluster::INVALID_USER_ID) {}
    UserInfo(Cluster::TUserId const & _userid, nstl::wstring const & _username)
      :userid_(_userid), username_(_username)
    {}
  };
}
