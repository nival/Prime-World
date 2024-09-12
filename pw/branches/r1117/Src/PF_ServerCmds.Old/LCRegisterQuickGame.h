/*
 * LCRegisterQiuckGame.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCREGISTERQIUCKGAME_H_
#define LCREGISTERQIUCKGAME_H_

#include "LobbyCommand.h"

class LCRegisterForQuickGame: public LobbyCommand
{
  OBJECT_BASIC_METHODS(LCRegisterForQuickGame);

  int m_nAccountId;

protected:
  //implemented by individual client: blah! Nival binary serializer is too ineffective sizewise unfortunately
   //convert command to most compact binary representation: Do not use GZIP! and store to m_requestCmd
   void serialize(void) {LobbyCommand::serialize(); GetRequestStream() << m_nAccountId; }
   //convert command from serialized form to normal one
   void deserialize(class ClientThread const *);
   //convert reply currently arrived from field by field form to command structure
   void deserializeReply(void) {LobbyCommand::deserializeReply();}

   // convert from normal form to SQL command! Should be colled on server envinment only
   nstl::wstring serializeSQL(void);

   virtual Priority getPriority(void) {return CP_MEDIUM;}

public:
  LCRegisterForQuickGame(int nAccountId = INVALID_ID_NUMBER): LobbyCommand(), m_nAccountId (nAccountId) {}
 
protected:
  void initCommonFields() {LobbyCommand::initCommonFields(); m_nAccountId = INVALID_ID_NUMBER;}

  REG_COMMAND_H(LCRegisterForQuickGame, LobbyCommand)
};

#endif /* LCREGISTERQIUCKGAME_H_ */
