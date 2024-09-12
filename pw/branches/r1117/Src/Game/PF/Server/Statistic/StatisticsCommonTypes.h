#pragma once
#include "Server/RPC/Base.h"
#include "SessionPlayerScoring.h"
#include "SessionPlayerExtra.h"

//
// ATTENTION!
// AHTUNG!
// ” этих структур есть двойники в коде статистики, C#
// ѕеред любыми изменени€ми посоветоватьс€ с програмистами сервиса статистики
//

namespace StatisticService
{
  namespace RPC
  {
    struct SessionClientResultsPlayer : rpc::Data
    {
      SERIALIZE_ID();
      ZDATA
        int userid;
      SessionPlayerScoring scoring;
      SessionPlayerExtra extra;
      ZEND int operator&( IBinSaver &f ) { f.Add(2,&userid); f.Add(3,&scoring); f.Add(4,&extra); return 0; }

      explicit SessionClientResultsPlayer( int _userId = 0 ) :
      userid( _userId )
      {}

      bool operator == ( const SessionClientResultsPlayer & other ) const {
        return 
          ( userid == other.userid ) && 
          ( scoring == other.scoring ) &&
          ( extra == other.extra );
      }
    };



    //
    //Ёта структура заполн€етс€ на клиентах, проходит верификацию на game server,
    //попадает на лобби и отправл€етс€ в статистику
    // роме статистики, данные из нее используютс€ в lobby и roll service
    //
    struct SessionClientResults : rpc::Data
    {
      SERIALIZE_ID();
      ZDATA
        int sideWon; //lobby::ETeam::Enum
      int surrenderVote;
      vector<SessionClientResultsPlayer> players;
      ZEND int operator&( IBinSaver &f ) { f.Add(2,&sideWon); f.Add(3,&surrenderVote); f.Add(4,&players); return 0; }

      SessionClientResults() :
      sideWon( -1 ), surrenderVote( 0 )
      {}

      bool operator == ( const SessionClientResults & other ) const {
        return 
          ( sideWon == other.sideWon ) &&
          ( surrenderVote == other.surrenderVote ) &&
          ( players == other.players );
      }
    };

  } //namespace RPC

} //namespace StatisticService
