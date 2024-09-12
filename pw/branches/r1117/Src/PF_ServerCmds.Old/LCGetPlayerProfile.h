/*
 * LCGetPlayerProfile.h
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */

#ifndef LCGETPLAYERPROFILE_H_
#define LCGETPLAYERPROFILE_H_

#include "LobbyCommand.h"
#include "../System/ScopedArray.h"

class LCGetPlayerProfile: public LobbyCommand
{
public:

  LCGetPlayerProfile(int nAccountID = INVALID_ID_NUMBER, bool bIncludeStatistics = true, bool bIncludeAvatar = true, bool bIncludePrivateInfo = false): LobbyCommand()
  {
    initCommonFields();
    m_nAccountId          = nAccountID;
    m_bIncludeStatistics  = bIncludeStatistics;
    m_bIncludeAvatar      = bIncludeAvatar; 
    m_bIncludePrivateInfo = bIncludePrivateInfo;
  }
  LCGetPlayerProfile(nstl::wstring const sPlayerName, bool bIncludeStatistics = true, bool bIncludeAvatar = true, bool bIncludePrivateInfo = false): LobbyCommand()
  {
    initCommonFields();
    m_sPlayerName         = sPlayerName;  
    m_bIncludeStatistics  = bIncludeStatistics;
    m_bIncludeAvatar      = bIncludeAvatar; 
    m_bIncludePrivateInfo = bIncludePrivateInfo;
  }

  enum PlayerGender
  {
    PG_MALE   = 0,
    PG_FEMALE
  };
  struct PlayerStatistics
  {
    int nEnemyHeroesKilled     ; //lifetime
    int nKillAssists           ; //lifetime
    int nVictimKills           ; //lifetime of being killed
    int nGamesPlayedNum        ; //total games player took part in
    int nGamesCompleted        ; //player stayed to the end      
    int nGamesQuit             ; //player left because of quit
    int nGamesLaggedKillTask   ; //player left killing the game
    int nGamesLaggedLastHop    ; //player left removing network cable or BSOD or whatever
    int nGamesLaggedNotLastHop ; //any other reason of disconnect
    int nGamesParticipated     ; //took part in game after first wave of creep was born or whatever
    PlayerStatistics()
    {
      initCommonFields();
    }
    void initCommonFields()
    {
      nEnemyHeroesKilled     = 0; 
      nKillAssists           = 0; 
      nVictimKills           = 0; 
      nGamesPlayedNum        = 0; 
      nGamesCompleted        = 0; 
      nGamesQuit             = 0; 
      nGamesLaggedKillTask   = 0; 
      nGamesLaggedLastHop    = 0; 
      nGamesLaggedNotLastHop = 0; 
      nGamesParticipated     = 0; 
    }
    void serializeReply(MemoryStream &str);
    void deserializeReply(MemoryStream &str);
    void deserializeSQL(SQLStream &str);
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


  virtual Priority getPriority(void) {return (m_bIncludeAvatar || m_bIncludeStatistics)? CP_LOW: CP_MEDIUM;}

  void initCommonFields() 
  {
    LobbyCommand::initCommonFields(); 
    m_nAccountId         = INVALID_ID_NUMBER;
    m_sPlayerName        = L"";
    m_bIncludeAvatar     = true;
    m_bIncludeStatistics = true;

    m_sLogin       = L"";
    m_sPassword    = L"";
    m_nMoneyAdded  = 0; 
    m_nLastIP      = 0;
    m_sRealName    = L"";

    m_nGender      = PG_MALE;
    m_nGold        = 0; 
    m_nRegDate     = 0; 
    m_nCoupleID    = 0; 
    m_nWeddingDate = 0; 
    m_nLadderPlace = 0;
    m_rTrueSkill   = 0.0;
    m_rReliability = 0.0;
    m_nLastOnline  = 0;
    m_isOnlineNow  = false;

    m_sStatistics.initCommonFields() ;

    m_avatar.init(); 
  }

private: 
  OBJECT_BASIC_METHODS(LCGetPlayerProfile);

  //request part
  int            m_nAccountId         ;
  nstl::wstring  m_sPlayerName        ;
  bool           m_bIncludeAvatar     ;
  bool           m_bIncludeStatistics ;
  bool           m_bIncludePrivateInfo;

  //replay part
  //private part
  nstl::wstring              m_sLogin      ;
  nstl::wstring              m_sPassword   ;
  int                        m_nMoneyAdded ; //real money added to the game                  
  unsigned int               m_nLastIP     ;
  nstl::wstring              m_sRealName   ;

  //public part
  PlayerGender               m_nGender     ;
  int                        m_nGold       ;                   
  time_t                     m_nRegDate    ;               
  unsigned int               m_nCoupleID   ; //account id of husband or wife              
  time_t                     m_nWeddingDate; 
  int                        m_nLadderPlace;
  double                     m_rTrueSkill  ;
  double                     m_rReliability;
  time_t                     m_nLastOnline ;
  bool                       m_isOnlineNow ;

  PlayerStatistics           m_sStatistics ;

  BLOBField                  m_avatar      ;
                                          
  REG_COMMAND_H(LCGetPlayerProfile, LobbyCommand)
};

#endif /* LCGETPLAYERPROFILE_H_ */
