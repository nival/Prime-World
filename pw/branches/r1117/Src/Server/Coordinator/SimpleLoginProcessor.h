#ifndef SIMPLELOGINPROCESSOR_H_20750BA5
#define SIMPLELOGINPROCESSOR_H_20750BA5
#include "stdafx.h"

#include "LoginProcessorBase.h"
#include "Network/LoginData.h"

struct SimpleLoginProcessor : public Login::ServerLoginProcessorBase
{
  SimpleLoginProcessor( unsigned int firstUserId, unsigned int maskUserId );

protected:
  virtual bool PerformLoginCheck( const string & login, const string & password, Network::IConnection *connection, Login::LoginResultData * result );
  virtual bool ClientStep( StrongMT<Login::SLoginContext> & context );

  unsigned int nextId;
  unsigned int maskUserId;
  Login::ESessionLoginMode sessionLoginMode_;

  typedef hash_map<string, unsigned int> LoggedUsersT;
  LoggedUsersT loggedUsers;
};

#endif //#define SIMPLELOGINPROCESSOR_H_20750BA5
