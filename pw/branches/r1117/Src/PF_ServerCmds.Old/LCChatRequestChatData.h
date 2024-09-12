/*
 * LCRegisterQiuckGame.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCREQUESTCHATDATA_H_
#define LCREQUESTCHATDATA_H_

#include "LobbyCommand.h"

class LCChatRequestChatData: public LobbyCommand
{
public:
  struct ChatInfoElem
  {
    long long       nChatId;       // id of individual phrase
    int             nChannelId;    //channel it was said into
    int             nUserId;       //one who said it
    unsigned int    nTimeStamp;    //when it was said
    nstl::wstring   sText;         //text AKA payload
    ChatInfoElem(): nChatId(LobbyCommand::INVALID_ID_NUMBER), nChannelId(LobbyCommand::INVALID_ID_NUMBER),
                nUserId(LobbyCommand::INVALID_ID_NUMBER), nTimeStamp(0) 
    {} 
  };
  
  typedef nstl::vector<ChatInfoElem> ChatInfo;

  LCChatRequestChatData(long long nChatIDFrom = INVALID_ID_NUMBER): LobbyCommand()
    , m_nChatIDFrom (nChatIDFrom)
    , m_nTimeStampFrom(0)
    , m_bUseTimeStamp(false)
  {}

  LCChatRequestChatData(unsigned long nTimeStamp): LobbyCommand()
    , m_nChatIDFrom (INVALID_ID_NUMBER)
    , m_nTimeStampFrom(nTimeStamp)
    , m_bUseTimeStamp(true)
  {}


protected:
   //convert command to most compact binary representation: Do not use GZIP! and store to m_requestCmd
   void serialize(void);
   //convert command from serialized form to normal one
   void deserialize(class ClientThread const *);
   //convert reply currently arrived from field by field form to command structure
   void serializeReply(void);
   void deserializeReply(void);

   // convert from normal form to SQL command! Should be called on server environment only
   nstl::wstring serializeSQL(void);
   void deserializeSQL(SQLStream &str);

   virtual Priority getPriority(void) {return CP_MEDIUM;}

   void initCommonFields() 
   {
     LobbyCommand::initCommonFields(); 
     m_nChatIDFrom    = INVALID_ID_NUMBER;
     m_nTimeStampFrom = 0;
     m_bUseTimeStamp  = true;
     m_nUserID        = INVALID_ID_NUMBER;
   }

private:
  OBJECT_BASIC_METHODS(LCChatRequestChatData);

  //request data
  long long          m_nChatIDFrom;
  unsigned int       m_nTimeStampFrom;
  bool               m_bUseTimeStamp;

  //reply data
  ChatInfo  m_chatInfo;
  //server only var
  int       m_nUserID;

  REG_COMMAND_H(LCChatRequestChatData, LobbyCommand)
};

#endif /* LCREQUESTCHATDATA_H_ */
