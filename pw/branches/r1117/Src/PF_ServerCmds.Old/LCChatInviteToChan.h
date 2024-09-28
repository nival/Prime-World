/*
 * LCRegisterQiuckGame.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCCHATINVITETOCHAN_H_
#define LCCHATINVITETOCHAN_H_

#include "LobbyCommand.h"

class LCChatInviteToChan: public LobbyCommand
{
  OBJECT_BASIC_METHODS(LCChatInviteToChan);

  int            m_nChannelId;
  nstl::wstring  m_sChannelName;
  int            m_nSenderId;
  int            m_nRecipientId;

protected:
  //implemented by individual client: blah! Nival binary serializer is too ineffective sizewise unfortunately
   //convert command to most compact binary representation: Do not use GZIP! and store to m_requestCmd
   void serialize(void);
   
   //convert command from serialized form to normal one
   void deserialize(class ClientThread const *);
   //convert reply currently arrived from field by field form to command structure
   void deserializeReply(void) {LobbyCommand::deserializeReply();}

   // convert from normal form to SQL command! Should be colled on server envinment only
   nstl::wstring serializeSQL(void);

   virtual Priority getPriority(void) {return CP_MEDIUM;}

public:
  LCChatInviteToChan(int nChannelId = INVALID_ID_NUMBER, int nSenderId = INVALID_ID_NUMBER, int nRecipientId = INVALID_ID_NUMBER): LobbyCommand(), 
    m_nChannelId (nChannelId), m_sChannelName(L""), m_nSenderId(nSenderId), m_nRecipientId(nRecipientId) {}
  LCChatInviteToChan(nstl::wstring & sChannelName, int nSenderId, int nRecipientId): LobbyCommand(), 
    m_nChannelId (INVALID_ID_NUMBER), m_sChannelName(sChannelName), m_nSenderId(nSenderId), m_nRecipientId(nRecipientId) {}
 
protected:
  void initCommonFields() {LobbyCommand::initCommonFields();}

  REG_COMMAND_H(LCChatInviteToChan, LobbyCommand)
};

#endif /* LCCHATINVITETOCHAN_H_ */
