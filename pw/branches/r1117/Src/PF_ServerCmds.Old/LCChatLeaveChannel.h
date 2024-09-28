/*
 * LCRegisterQiuckGame.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCLEAVECHANNEL_H_
#define LCLEAVECHANNEL_H_

#include "LobbyCommand.h"

class LCChatLeaveChannel: public LobbyCommand
{
public:
  enum LeaveReason
  {
    LR_UNKNOWN,
    LR_NORMAL,
    LR_KICK,
    LR_TIMEOUT
  };

  LCChatLeaveChannel(int nChannelId = INVALID_ID_NUMBER, LeaveReason lr = LR_UNKNOWN): LobbyCommand(), m_nChannelId (nChannelId), m_nLeaveReason(lr) {}

protected:
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

  virtual Priority getPriority(void) {return CP_LOW;}


protected:
  void initCommonFields() {LobbyCommand::initCommonFields(); m_nChannelId = INVALID_ID_NUMBER; m_nLeaveReason = LR_UNKNOWN;}

private:
  OBJECT_BASIC_METHODS(LCChatLeaveChannel);

  int         m_nChannelId;
  LeaveReason m_nLeaveReason;


  REG_COMMAND_H(LCChatLeaveChannel, LobbyCommand)
};

#endif /* LCLEAVECHANNEL_H_ */
