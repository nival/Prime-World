#ifndef SOCIALLOBBYGUILDFIGHTCALC_H_INCLUDED
#define SOCIALLOBBYGUILDFIGHTCALC_H_INCLUDED

#include "SocialLobbyTypes.h"
//#include "SocialLobbyUserContext.h"
//#include "SocialLobbyParty.h"
//#include "SocialLobbyCtrl.h"
#include "SocialLobbyConfig.h"
//#include "ISocialLobbyPvxSvc.h"
//#include "SocialLobbyLog.h"
//#include "SocialLobbyStatistics.h"
//#include "Db/DBServer.auto.h"
#include <map>
//#include "System/InlineProfiler.h"


namespace socialLobby
{

class GuildFightCalculator : public NonCopyable
{
public:
  GuildFightCalculator( const mmaking::SGame & _mmData ) :
  mmData( _mmData )
  {
  }


  void Add( TUserIdPvX pvxUserId, NCore::TGuildAuid id )
  {
    if ( !id )
      return;

    for ( int ti = 0; ti < mmData.humans.size(); ++ti )
      for ( int mi = 0; mi < mmData.humans[ti].members.size(); ++mi )
        if ( mmData.humans[ti].members[mi].mmId == pvxUserId )
        {
          lobby::ETeam::Enum faction = mmData.humans[ti].common.team;
          int tidx = lobby::ETeam::Index( faction );
          int & pop = guildPop[tidx][id];
          ++pop;
          return;
        }
    NI_ALWAYS_ASSERT( "" );
  }


  void PrepareGuildData(lobby::GameGuildData& guildData)
  {
    for ( int tidx = 0; tidx < 2; ++tidx )
      for ( std::map<lobby::TGuildAuid, int>::const_iterator it = guildPop[tidx].begin(); it != guildPop[tidx].end(); ++it )
      {
        lobby::TGuildAuid gid = it->first;
        lobby::ETeam::Enum teamId = (lobby::ETeam::Enum)tidx;
        if (guildData.guilds.find(teamId) == guildData.guilds.end())
          guildData.guilds[teamId] = vector<lobby::TGuildAuid>(gid);
        else if (guildData.guilds[teamId].find(gid) == guildData.guilds[teamId].end())
          guildData.guilds[teamId].push_back(gid);
      }
  }


  bool IsGuildFight( int minGuildSize )
  {
    int biggest[2] = {0, 0};
    lobby::TGuildAuid biggestGuilds[2] = {0, 0};
    for ( int tidx = 0; tidx < 2; ++tidx )
      for ( std::map<lobby::TGuildAuid, int>::const_iterator it = guildPop[tidx].begin(); it != guildPop[tidx].end(); ++it )
      {
        lobby::TGuildAuid gid = it->first;

        if ( it->second > biggest[tidx] )
        {
          biggest[tidx] = it->second;
          biggestGuilds[tidx] = gid;
        }
      }

    if (biggestGuilds[0] == 0 || biggestGuilds[1] == 0)
      return false;

    return (biggest[0] >= minGuildSize || biggest[1] >= minGuildSize) && biggestGuilds[0] != biggestGuilds[1];
  }


private:
  const mmaking::SGame & mmData;
  std::map<lobby::TGuildAuid, int> guildPop[2];
};

} //namespace socialLobby

#endif //SOCIALLOBBYGUILDFIGHTCALC_H_INCLUDED
