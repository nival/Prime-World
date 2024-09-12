/*
 * LCStartQiuckGame.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCSTARTQIUCKGAME_H_
#define LCSTARTQIUCKGAME_H_

#include "LobbyCommand.h"

class LCStartQuickGame: public LobbyCommand
{
public:
  enum ClientTeam
  {
    CT_NA = -1,
    CT_FIRST = 0, 
    CT_SECOND   ,
    CT_WATCHER  ,
    CT_JUDGE    ,
    CT_LAST    
  };
  struct ClientInfo 
  {
    ClientTeam    team;
    unsigned long clientIP;
    unsigned int  accountID;
    unsigned int  gameID;
    ClientInfo(): team(CT_NA), clientIP(0), accountID(0), gameID(0) {}
    ClientInfo(ClientTeam ct, long ci, int ai, int gi): team(ct), clientIP(ci), accountID(ai), gameID(gi) {}
  };
  typedef nstl::vector<ClientInfo> ClientInfoList;
  LCStartQuickGame(): LobbyCommand(){}

  ClientInfoList clients;

OBJECT_BASIC_METHODS(LCStartQuickGame);

protected:
  //implemented by individual client: blah! Nival binary serializer is too ineffective sizewise unfortunately
  //convert command to most compact binary representation: Do not use GZIP! and store to m_requestCmd
  void serialize(void) {NI_ALWAYS_ASSERT("Server command!");}
  //convert command from serialized form to normal one
  void deserialize(class ClientThread const *) {NI_ALWAYS_ASSERT("Server command!");}
  
  // reply serialization
  void serializeReply(void);
  //convert reply currently arrived from field by field form to command structure
  void deserializeReply(void);

  // convert from normal form to SQL command! Should be called on server environment only
  nstl::wstring serializeSQL(void) {NI_ALWAYS_ASSERT("Not needed!") return nstl::wstring(L"");}
  //parse SQL server reply
  void deserializeSQL(SQLStream &)        {NI_ALWAYS_ASSERT("Not needed!");}

  virtual Priority getPriority(void) {return CP_MEDIUM;}
   
  virtual bool     isPartialDecodeSupported(void) {return false;}

  void initCommonFields() 
  {
    LobbyCommand::initCommonFields(); 
    clients.clear();
  }

  REG_COMMAND_H(LCStartQuickGame, LobbyCommand)
};

#endif /* LCSTARTQIUCKGAME_H_ */
