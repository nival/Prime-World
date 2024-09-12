#pragma once

#include "System/BinSaver.h"
#include "RPC/Interfaces.h"
#include "RPC/RpcDataFactory.h"

namespace Login
{

struct LoginResultData : public rpc::Data
{
  SERIALIZE_ID();
  ZDATA
  ZNOPARENT(rpc::Data)

  int       nErrorCode;
  int64     nUserID;
  wstring   username;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&nErrorCode); f.Add(3,&nUserID); f.Add(4,&username); return 0; }

  LoginResultData() :
  nErrorCode( 0 ),
  nUserID( -1 )
  {}
};

_interface IUserDatabase
{
  virtual Login::LoginResultData const *GetUserLoginInfo(int nAccountID) const=0;
};

} // Login