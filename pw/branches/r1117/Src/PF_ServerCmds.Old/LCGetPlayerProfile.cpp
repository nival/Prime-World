/*
 * LCGetPlayerProfile.cpp
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */


#include "../Server/src/TypeProxy.h"
#include "../System/nlist.h"
#include "../System/nstring.h"
#include "../System/nvector.h"
using namespace nstl;
#include "../System/StrProc.h"
#include "../System/Logger.h"
#include "../System/LoggerStream.h"
#include "../System/SystemLog.h"
#include "../Scene/DiTypes.h"
#include <ctype.h>
#include <typeinfo>
#include <math.h>
#include "../System/ScopedArray.h"
#include "../System/basic.h"
#include "../System/nalgoritm.h"
#include "../Server/src/ClientThread.h"
#include "LCGetPlayerProfile.h"

REG_COMMAND_CPP(LCGetPlayerProfile);

static wchar_t const* const pCommonFields[] = {
  L"user_id",
  L"player_name"
};

static wchar_t const* const pPrivateFields[] = {
  L"login",
  L"password",
  L"money",
  L"lastip",
  L"real_name"
};
static wchar_t const* const pStatisticsFields[] = {
  L"st_enemy_killed"    ,
  L"st_assisted_killed" ,
  L"st_self_killed"     ,
  L"st_gplayed"         ,
  L"st_gcompleted"      ,
  L"st_quited"          ,
  L"st_lagkt"           ,
  L"st_glaglh_disc"     ,
  L"st_glagnlh_disc"    ,
  L"st_allgstart"
};
static wchar_t const* const pGeneralFields[] = {
  L"gender",
  L"gold",
  L"UNIX_TIMESTAMP(reg_date)",
  L"couple_id",
  L"UNIX_TIMESTAMP(wedding_date)",
  L"st_placeclan"       ,
  L"st_trueskill"       ,
  L"st_reliability"     ,
  L"UNIX_TIMESTAMP(lastseen)",
  L"online"
};

nstl::wstring LCGetPlayerProfile::serializeSQL(void)
{
  nstl::wstring sRequest(L"SELECT  ");
  sRequest.reserve(900);

  sRequest += pCommonFields[(m_nAccountId == INVALID_ID_NUMBER)?0:1];

  for( unsigned int nI = 0; nI < DIM(pGeneralFields); nI++)
  {
    sRequest += L", ";
    sRequest += pGeneralFields[nI];
  }
  if(m_bIncludeStatistics)
  {
    for( unsigned int nI = 0; nI < DIM(pStatisticsFields); nI++)
    {
      sRequest += L", ";
      sRequest += pStatisticsFields[nI];
    }
  }
  if(m_bIncludePrivateInfo)
  {
    for( unsigned int nI = 0; nI < DIM(pPrivateFields); nI++)
    {
      sRequest += L", ";
      sRequest += pPrivateFields[nI];
    }
  }
  if(m_bIncludeAvatar)
  {
    sRequest += L", `avatar`";
  }
  sRequest += L" FROM `user_accounts` WHERE ";
  if(m_nAccountId == INVALID_ID_NUMBER)
  {
    sRequest += L"`player_name` = \"";
    sRequest += m_sPlayerName;
    sRequest += L"\";";
  }
  else
  {
    ScopedArray<wchar_t> pBuf(new wchar_t[100]);
    swprintf(&pBuf[0], 99, L"`user_id` = %d", m_nAccountId);
    sRequest += &pBuf[0];
  }
  return sRequest;
}

void LCGetPlayerProfile::serialize(void)
{
  LobbyCommand::serialize();
  GetRequestStream() << m_nAccountId         ;
  GetRequestStream() << m_sPlayerName        ;
  GetRequestStream() << m_bIncludeAvatar     ;
  GetRequestStream() << m_bIncludeStatistics ;
  GetRequestStream() << m_bIncludePrivateInfo;
}

void LCGetPlayerProfile::deserialize(ClientThread const *pClient)
{
  LobbyCommand::deserialize(pClient);
  GetRequestStream() >> m_nAccountId         ;
  GetRequestStream() >> m_sPlayerName        ;
  GetRequestStream() >> m_bIncludeAvatar     ;
  GetRequestStream() >> m_bIncludeStatistics ;
  GetRequestStream() >> m_bIncludePrivateInfo;

  if(m_bIncludePrivateInfo && ((m_nAccountId != INVALID_ID_NUMBER && pClient->GetAccoundId() != m_nAccountId) ||
    (m_nAccountId == INVALID_ID_NUMBER)))
  {
    NI_SERVER_LOG(("%d requested private info. Denied.", pClient->GetAccoundId()));
    m_bIncludePrivateInfo = false;
  }
}

void LCGetPlayerProfile::serializeReply(void)
{
  LobbyCommand::serializeReply();

  GetReplyStream() << m_nAccountId         ;
  GetReplyStream() << m_sPlayerName        ;
  GetReplyStream() << m_bIncludePrivateInfo;

  if(m_bIncludePrivateInfo)
  {
    GetReplyStream() << m_sLogin          ;
    GetReplyStream() << m_sPassword       ;
    GetReplyStream() << m_nMoneyAdded     ;
    GetReplyStream() << m_nLastIP         ;
    GetReplyStream() << m_sRealName       ;
  }

  GetReplyStream() << m_nGender         ;
  GetReplyStream() << m_nGold           ;
  GetReplyStream() << m_nRegDate        ;
  GetReplyStream() << m_nCoupleID       ;
  GetReplyStream() << m_nWeddingDate    ;
  GetReplyStream() << m_nLadderPlace    ;
  GetReplyStream() << m_rTrueSkill      ;
  GetReplyStream() << m_rReliability    ;
  GetReplyStream() << m_nLastOnline     ;
  GetReplyStream() << m_isOnlineNow     ;

  if(m_bIncludeStatistics)
  {
    m_sStatistics.serializeReply(GetReplyStream())        ;
  }

  if(m_bIncludeAvatar)
  {
    m_avatar.serialize(GetReplyStream());
  }
}

void LCGetPlayerProfile::deserializeReply()
{
  LobbyCommand::deserializeReply();

  GetReplyStream() >> m_nAccountId         ;
  GetReplyStream() >> m_sPlayerName        ;
  GetReplyStream() >> m_bIncludePrivateInfo;

  if(m_bIncludePrivateInfo)
  {
    GetReplyStream() >> m_sLogin          ;
    GetReplyStream() >> m_sPassword       ;
    GetReplyStream() >> m_nMoneyAdded     ;
    GetReplyStream() >> m_nLastIP         ;
    GetReplyStream() >> m_sRealName       ;
  }

  GetReplyStream() >> m_nGender         ;
  GetReplyStream() >> m_nGold           ;
  GetReplyStream() >> m_nRegDate        ;
  GetReplyStream() >> m_nCoupleID       ;
  GetReplyStream() >> m_nWeddingDate    ;
  GetReplyStream() >> m_nLadderPlace    ;
  GetReplyStream() >> m_rTrueSkill      ;
  GetReplyStream() >> m_rReliability    ;
  GetReplyStream() >> m_nLastOnline     ;
  GetReplyStream() >> m_isOnlineNow     ;

  if(m_bIncludeStatistics)
  {
    m_sStatistics.deserializeReply(GetReplyStream())        ;
  }

  if(m_bIncludeAvatar)
  {
    m_avatar.deserialize(GetReplyStream());
    //FILE *fh;  fopen_s(&fh, "c:\\tt.jpg", "wb");   fwrite(&m_pAvatar[0], m_nAvatarSize, 1, fh);  fclose(fh);
  }
}

void LCGetPlayerProfile::deserializeSQL(SQLStream &str)
{
  LobbyCommand::deserializeSQL(str);

  //check for result
  if(str.GetSize() == 0)
    return;
  //we expect one one value
  unsigned int nVal;
  //rows
  str >> nVal;
  NI_ASSERT(nVal <= 1, "Investigate if not so.");
  if(nVal != 1)
    return;
  //cols
  str >> nVal;
  unsigned int nExpectedFieldsNum = 1 + DIM(pGeneralFields);
  if(m_bIncludeAvatar     ) nExpectedFieldsNum += 1;
  if(m_bIncludePrivateInfo) nExpectedFieldsNum += DIM(pPrivateFields);
  if(m_bIncludeStatistics ) nExpectedFieldsNum += DIM(pStatisticsFields);
  if(nVal != nExpectedFieldsNum)
    return;
  if(m_nAccountId == INVALID_ID_NUMBER)
  {
    str >> m_nAccountId;
  }
  else
  {
    str >> m_sPlayerName;
  }
  //general fields
  m_nGender       = (SQLStream::ReadWStrFromStream(str) == L"M")? PG_MALE: PG_FEMALE;
  str >> m_nGold         ;
  str >> m_nRegDate      ;
  str >> m_nCoupleID     ;
  str >> m_nWeddingDate  ;
  str >> m_nLadderPlace  ;
  str >> m_rTrueSkill    ;
  str >> m_rReliability  ;
  str >> m_nLastOnline   ;
  str >> m_isOnlineNow   ;

  //statistics
  if(m_bIncludeStatistics)
    m_sStatistics.deserializeSQL(str);

  //private
  if(m_bIncludePrivateInfo)
  {
    str >> m_sLogin       ;
    str >> m_sPassword    ;
    str >> m_nMoneyAdded  ;
    str >> m_nLastIP      ;
    str >> m_sRealName    ;
  }
  if(m_bIncludeAvatar)
  {
    str >> m_avatar;
  }
}

void LCGetPlayerProfile::PlayerStatistics::serializeReply(MemoryStream &str)
{
  str << nEnemyHeroesKilled      ;
  str << nKillAssists            ;
  str << nVictimKills            ;
  str << nGamesPlayedNum         ;
  str << nGamesCompleted         ;
  str << nGamesQuit              ;
  str << nGamesLaggedKillTask    ;
  str << nGamesLaggedLastHop     ;
  str << nGamesLaggedNotLastHop  ;
  str << nGamesParticipated      ;
}

void LCGetPlayerProfile::PlayerStatistics::deserializeReply(MemoryStream &str)
{
  str >> nEnemyHeroesKilled      ;
  str >> nKillAssists            ;
  str >> nVictimKills            ;
  str >> nGamesPlayedNum         ;
  str >> nGamesCompleted         ;
  str >> nGamesQuit              ;
  str >> nGamesLaggedKillTask    ;
  str >> nGamesLaggedLastHop     ;
  str >> nGamesLaggedNotLastHop  ;
  str >> nGamesParticipated      ;
}

void LCGetPlayerProfile::PlayerStatistics::deserializeSQL(SQLStream &str)
{
  str >> nEnemyHeroesKilled      ;
  str >> nKillAssists            ;
  str >> nVictimKills            ;
  str >> nGamesPlayedNum         ;
  str >> nGamesCompleted         ;
  str >> nGamesQuit              ;
  str >> nGamesLaggedKillTask    ;
  str >> nGamesLaggedLastHop     ;
  str >> nGamesLaggedNotLastHop  ;
  str >> nGamesParticipated      ;
}

