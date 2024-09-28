/*
 * LCAuthenticateSimple.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCAUTHENTICATESIMPLE_H_
#define LCAUTHENTICATESIMPLE_H_

#include "LobbyCommand.h"

class LCAuthenticateSimple: public LobbyCommand
{
  OBJECT_BASIC_METHODS(LCAuthenticateSimple);

  //reply part
  unsigned int  m_nAccountId;
  nstl::wstring m_sLogin;
  nstl::wstring m_sPassword;
  nstl::wstring m_sPasswordHash;
  unsigned int  m_nPacketSize;

protected:
  //implemented by individual client: blah! Nival binary serializer is too ineffective sizewise unfortunately
   //convert command to most compact binary representation: Do not use GZIP! and store to m_requestCmd
   void serialize(void);
   //convert command from serialized form to normal one
   void deserialize(class ClientThread const *);

   // reply serialization
   void serializeReply(void);
   //convert reply currently arrived from field by field form to command structure
   void deserializeReply(void);

   // convert from normal form to SQL command! Should be called on server environment only
   nstl::wstring serializeSQL(void);
   //parse SQL server reply
   void deserializeSQL(SQLStream &str);

   virtual Priority getPriority(void) {return CP_MEDIUM;}

public:
  int GetAccountId()   {return m_nAccountId;}
  LCAuthenticateSimple(nstl::wstring const &sLogin = nstl::wstring(L""), nstl::wstring const &sPassword = nstl::wstring(L""), int nPacketSize = 1024): 
  LobbyCommand(), m_nAccountId (0), m_sLogin(sLogin), m_sPassword(sPassword), m_nPacketSize(min(nPacketSize, 10*1024)) 
  {}
  unsigned int GetPacketSize() {return m_nPacketSize;}

protected:
  void initCommonFields() {LobbyCommand::initCommonFields(); m_nAccountId = 0;}

  REG_COMMAND_H(LCAuthenticateSimple, LobbyCommand)
};

#endif /* LCAUTHENTICATESIMPLE_H_ */
