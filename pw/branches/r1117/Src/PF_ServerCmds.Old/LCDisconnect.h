/*
 * LCDisconnnect.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCDISCONNECT_H_
#define LCDISCONNECT_H_

#include "LobbyCommand.h"

class LCDisconnect: public LobbyCommand
{
  OBJECT_BASIC_METHODS(LCDisconnect);
public:
  enum DisconnectReason
  {
    DR_UNSPECIFIED, //means you was disconnected by server for whatever reason. Just suck it up.
    DR_OTHER_USER_LOGGED, //other user logged with the same credentials
    DR_INVALID_LOGIN //credentials supplied are invalid. Handshake failed.
  };

  LCDisconnect(DisconnectReason nReason = DR_UNSPECIFIED): 
    LobbyCommand(), m_nReason (nReason) 
    {}

protected:
  void serialize(void) {NI_ALWAYS_ASSERT("should not be called");}
  //convert command from serialized form to normal one
  void deserialize(class ClientThread const *) {NI_ALWAYS_ASSERT("should not be called");}

  // reply serialization
  void serializeReply(void);
  //convert reply currently arrived from field by field form to command structure
  void deserializeReply(void);

  // convert from normal form to SQL command! Should be called on server environment only
  nstl::wstring serializeSQL(void) {NI_ALWAYS_ASSERT("should not be called"); return LobbyCommand::serializeSQL();}
  //parse SQL server reply
  void deserializeSQL(SQLStream &) {NI_ALWAYS_ASSERT("should not be called");}

  virtual Priority getPriority(void) {return CP_LOW;}
  void initCommonFields() {LobbyCommand::initCommonFields(); m_nReason = DR_UNSPECIFIED; m_data.init();}

private:
  //reply part
  DisconnectReason  m_nReason;
  BLOBField         m_data;

  REG_COMMAND_H(LCDisconnect, LobbyCommand)
};

#endif /* LCDISCONNECT_H_ */
