/*
 * LCRegisterQiuckGame.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCCHATKICKFROMCHAN_H_
#define LCCHATKICKFROMCHAN_H_

#include "LobbyCommand.h"

//you kick somebody from channel you are owning
class LCChatKickFromChan: public LobbyCommand
{
  OBJECT_BASIC_METHODS(LCChatKickFromChan);

  int m_nKickerId;
  int m_nVictimId;
  int m_nChannelId;

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
  LCChatKickFromChan(int nKickerId = INVALID_ID_NUMBER, int nVictimId = INVALID_ID_NUMBER, int nChannelId = INVALID_ID_NUMBER): LobbyCommand()
    , m_nKickerId (nKickerId)
    , m_nVictimId(nVictimId)
    , m_nChannelId(nChannelId) 
  {}
 
protected:
  void initCommonFields() 
  {
    LobbyCommand::initCommonFields(); 
    m_nKickerId  = INVALID_ID_NUMBER;
    m_nVictimId  = INVALID_ID_NUMBER;
    m_nChannelId = INVALID_ID_NUMBER;
  }

  REG_COMMAND_H(LCChatKickFromChan, LobbyCommand)
};

#endif /* LCCHATKICKFROMCHAN_H_ */
