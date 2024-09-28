/*
 * LCRegisterQiuckGame.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCCHATJOINCHANNEL_H_
#define LCCHATJOINCHANNEL_H_

#include "LobbyCommand.h"

class LCChatJoinChannel: public LobbyCommand
{
  OBJECT_BASIC_METHODS(LCChatJoinChannel);

  int            m_nChannelId;
  nstl::wstring  m_sChanName;

  //server only variable
  int            m_nClientID; 
protected:

   void serialize(void);
   //convert command from serialized form to normal one
   void deserialize(class ClientThread const *);
   //convert reply currently arrived from field by field form to command structure
   void deserializeReply(void) {LobbyCommand::deserializeReply();}

   // convert from normal form to SQL command! Should be called on server environment only
   nstl::wstring serializeSQL(void);

   virtual Priority getPriority(void) {return CP_MEDIUM;}

public:
  LCChatJoinChannel(int nChannelId = INVALID_ID_NUMBER): LobbyCommand(), m_nChannelId (nChannelId), m_sChanName(L"") {}
  LCChatJoinChannel(nstl::wstring nChannelName): LobbyCommand(), m_nChannelId (INVALID_ID_NUMBER), m_sChanName(nChannelName) {}
 
protected:
 
  bool isCanJoinChannel(class ClientThread const *);

  void initCommonFields() 
  {
    LobbyCommand::initCommonFields(); 
    m_nChannelId = INVALID_ID_NUMBER;
    m_sChanName  = L"";
    m_nClientID  = INVALID_ID_NUMBER;
  }

  REG_COMMAND_H(LCChatJoinChannel, LobbyCommand)
};

#endif /* LCCHATJOINCHANNEL_H_ */
