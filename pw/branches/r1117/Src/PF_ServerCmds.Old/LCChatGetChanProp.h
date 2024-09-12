/*
 * LCRegisterQiuckGame.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCCHATGETCHATPROP_H_
#define LCCHATGETCHATPROP_H_

#include "LobbyCommand.h"

class LCChatGetChanProp: public LobbyCommand
{
public:
  LCChatGetChanProp(int nChannelId = INVALID_ID_NUMBER): LobbyCommand()
    , m_nChannelId(nChannelId)
    , m_sChannelName(L"") 
    , m_nOwnerId(INVALID_ID_NUMBER)
    , m_bIsPublic(false)
    , m_bIsSecret(true)
    , m_bIsClan(false)
    , m_bIsGame(false)
    , m_bIsWhisper(false)
  {}
  LCChatGetChanProp(nstl::wstring const sChannelName): LobbyCommand()
    , m_nChannelId(INVALID_ID_NUMBER)
    , m_sChannelName(sChannelName) 
    , m_nOwnerId(INVALID_ID_NUMBER)
    , m_bIsPublic(false)
    , m_bIsSecret(true)
    , m_bIsClan(false)
    , m_bIsGame(false)
    , m_bIsWhisper(false)
  {}

  enum ChannelTypesOrder
  {
    CP_PUBLIC   = 0,
    CP_SECRET      ,
    CP_CLAN        ,
    CP_GAME        ,
    CP_WHISPER     
  };

protected:
  //implemented by individual client: blah! Nival binary serializer is too ineffective sizewise unfortunately
  //convert command to most compact binary representation: Do not use GZIP! and store to m_requestCmd
  void serialize(void);
  //convert command from serialized form to normal one
  void deserialize(class ClientThread const *);
  //convert reply currently arrived from field by field form to command structure
  void serializeReply(void);
  void deserializeReply(void);

  // convert from normal form to SQL command! Should be called on server environment only
  nstl::wstring serializeSQL(void);
  void          deserializeSQL(SQLStream &str);


  virtual Priority getPriority(void) {return CP_MEDIUM;}

  void initCommonFields() 
  {
    LobbyCommand::initCommonFields(); 
    m_nChannelId   = INVALID_ID_NUMBER; 
    m_sChannelName = L"";
    m_nOwnerId     = INVALID_ID_NUMBER;
    m_bIsPublic    = false;
    m_bIsSecret    = true;
    m_bIsClan      = false;
    m_bIsGame      = false;
    m_bIsWhisper   = false;
  }

private: 
  OBJECT_BASIC_METHODS(LCChatGetChanProp);

  //request part
  int            m_nChannelId;
  nstl::wstring  m_sChannelName;
  //replay part
  int            m_nOwnerId;
  bool           m_bIsPublic;
  bool           m_bIsSecret;
  bool           m_bIsClan;
  bool           m_bIsGame;
  bool           m_bIsWhisper;


  REG_COMMAND_H(LCChatGetChanProp, LobbyCommand)
};

#endif /* LCCHATGETCHATPROP_H_ */
