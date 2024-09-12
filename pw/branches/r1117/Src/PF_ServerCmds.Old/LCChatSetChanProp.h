/*
 * LCRegisterQiuckGame.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCCHATSETCHANPROP_H_
#define LCCHATSETCHANPROP_H_

#include "LobbyCommand.h"

class LCChatSetChanProp: public LobbyCommand
{
  OBJECT_BASIC_METHODS(LCChatSetChanProp);

  //request part
  int            m_nChannelId;
  nstl::wstring  m_sChannelName;
  int            m_nOwnerId;
  bool           m_bIsPublic;
  bool           m_bIsSecret;
  bool           m_bIsClan;
  bool           m_bIsGame;
  bool           m_bIsWhisper;

protected:
  //implemented by individual client: blah! Nival binary serializer is too ineffective sizewise unfortunately
  //convert command to most compact binary representation: Do not use GZIP! and store to m_requestCmd
  void serialize(void);
  //convert command from serialized form to normal one
  void deserialize(class ClientThread const *);

  // convert from normal form to SQL command! Should be called on server environment only
  nstl::wstring serializeSQL(void);

  virtual Priority getPriority(void) {return CP_LOW;}

public:
  LCChatSetChanProp(int nChannelId = INVALID_ID_NUMBER): LobbyCommand()
    , m_nChannelId(nChannelId)
    , m_sChannelName(L"") 
    , m_nOwnerId(INVALID_ID_NUMBER)
    , m_bIsPublic(false)
    , m_bIsSecret(true)
    , m_bIsClan(false)
    , m_bIsGame(false)
    , m_bIsWhisper(false)
  {}
  LCChatSetChanProp(int nChannelId,
                    nstl::wstring const sChannelName,
                    int            nOwnerId,
                    bool           bIsPublic,
                    bool           bIsSecret,
                    bool           bIsClan,
                    bool           bIsGame,
                    bool           bIsWhisper): LobbyCommand()
    , m_nChannelId(nChannelId)
    , m_sChannelName(sChannelName) 
    , m_nOwnerId(nOwnerId)
    , m_bIsPublic(bIsPublic)
    , m_bIsSecret(bIsSecret)
    , m_bIsClan(bIsClan)
    , m_bIsGame(bIsGame)
    , m_bIsWhisper(bIsWhisper)
  {}


protected:
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

  REG_COMMAND_H(LCChatSetChanProp, LobbyCommand)
};

#endif /* LCCHATSETCHANPROP_H_ */
