/*
 * LCRegisterQiuckGame.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCCHATPOSTTOCHAN_H_
#define LCCHATPOSTTOCHAN_H_

#include "LobbyCommand.h"

class LCChatPostToChan: public LobbyCommand
{
  OBJECT_BASIC_METHODS(LCChatPostToChan);

  int            m_nChannelId;
  nstl::wstring  m_sText;

  //server only variable
  int            m_nUserId;
protected:
  //implemented by individual client: blah! Nival binary serializer is too ineffective sizewise unfortunately
   //convert command to most compact binary representation: Do not use GZIP! and store to m_requestCmd
   void serialize(void);
   //convert command from serialized form to normal one
   void deserialize(class ClientThread const *);
   //convert reply currently arrived from field by field form to command structure
   void deserializeReply(void) {LobbyCommand::deserializeReply();}

   nstl::wstring serializeSQL(void);

   virtual Priority getPriority(void) {return CP_MEDIUM;}

public:
  LCChatPostToChan(int nChannelId = INVALID_ID_NUMBER, nstl::wstring const &str = nstl::wstring(L"")): LobbyCommand(), m_nChannelId (nChannelId), m_sText(str), m_nUserId(INVALID_ID_NUMBER) {}
 
protected:
  void initCommonFields() {LobbyCommand::initCommonFields(); m_nChannelId = INVALID_ID_NUMBER; m_sText = nstl::wstring(L""); m_nUserId = INVALID_ID_NUMBER;}

  REG_COMMAND_H(LCChatPostToChan, LobbyCommand)
};

#endif /* LCCHATPOSTTOCHAN_H_ */
