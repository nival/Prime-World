#pragma once

#include <map>
#include "Game/PF/Server/LobbyPvx/CommonTypes.h"

#pragma warning( disable: 4530 )
namespace NDb 
{
 struct AdvMapDescription;
}
namespace EloRating
{


typedef ni_detail::UInt64 PlayerId;

class IPartyRatingBonusCallback
{
public:
  virtual int PartyRatingBonus( float partyRating, int partySize ) = 0;
};


class Calculator
{
public:
  void Clear();
  void AddPlayer( lobby::ETeam::Enum team, PlayerId playerId, float rating, int partyId );
  bool Calculate( lobby::ETeam::Enum winnerTeam, IPartyRatingBonusCallback * partyRatingBonusCb, const NDb::AdvMapDescription * _map );
  bool GetChange( PlayerId playerId, float & ratingChange ) const;
  bool GetChange( PlayerId playerId, float & ratingChange, float & sourceRating ) const;
  size_t PlayersNumber() const { return players.size(); }

private:
  struct PlayerInfo
  {
    lobby::ETeam::Enum team;
    PlayerId playerId;
    float rating;
    float ratingChange;
    int partyId;

    PlayerInfo() :
    team( lobby::ETeam::None ),
    playerId( 0 ),
    rating( 0 ),
    ratingChange( 0 ),
    partyId( 0 )
    {}
  };

  struct Party
  {
    float rating;
    int size;
    float minPartyRating;
    Party() :
    rating( 0 ),
    size( 0 )
    {}
  };

  typedef std::map<int, Party> PartyRatings;

  struct TeamInfo
  {
    int membersCount;
    PartyRatings parties;
    int fullPartyRatingBonus;

    TeamInfo() :
    membersCount( 0 ),
    fullPartyRatingBonus( 0 )
    {}
  };

  typedef std::map<PlayerId, PlayerInfo> PlayerMap;
  typedef std::map<lobby::ETeam::Enum, TeamInfo> TeamMap;

  PlayerMap players;
  TeamMap teamsInfo;

  bool AggregateTeams(const NDb::AdvMapDescription * _map);
  void CalcFullPartyRatingBonus( IPartyRatingBonusCallback * partyRatingBonusCb, lobby::ETeam::Enum winnerTeam);
  float CalculateChange( float playerRating, float winIndex, float odds );
  friend  bool getMaxRate(const std::pair<PlayerId, PlayerInfo> &i, const std::pair<PlayerId, PlayerInfo> &j);
};

} //namespace EloRating
