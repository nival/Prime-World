#include "stdafx.h"
#include <algorithm>
#include "EloRating.h"
#include "Server/LiveMMaking/RankTable.h"
#include "Db/DBServer.auto.h"
//#include <set>


#pragma warning( disable: 4530 )




namespace EloRating
{

    bool getMaxRate(const std::pair<PlayerId, Calculator::PlayerInfo> &i, const std::pair<PlayerId, Calculator::PlayerInfo> &j) { 
    Calculator::PlayerInfo  pi = i.second;
    Calculator::PlayerInfo  pj = j.second;
    return pi.rating < pj.rating; 
}

void Calculator::Clear()
{
  players.clear();
  teamsInfo.clear();
}



void Calculator::AddPlayer( lobby::ETeam::Enum team, PlayerId playerId, float rating, int partyId )
{
  PlayerInfo & info = players[playerId];
  info.team = team;
  info.playerId = playerId;
  info.rating = rating;
  info.partyId = partyId;
  info.ratingChange = 0;
}



bool Calculator::AggregateTeams(const NDb::AdvMapDescription * _map)
{
  teamsInfo.clear();
  set<int> teams;
  mmaking::RankTable tbl;
  int MIN_RATING = 0;
  map<int,int> partyRatings;
  if (_map && _map->matchmakingSettings)
  {
      tbl.Init(_map->matchmakingSettings);
      MIN_RATING = tbl.FindRankByIndex(0)->to;
  }

  for ( PlayerMap::const_iterator it = players.begin();it != players.end(); ++it )
  {
    const PlayerInfo & pi = it->second;

    teams.insert( (int)pi.team );

    TeamInfo & ti = teamsInfo[pi.team];
    ++ti.membersCount;
    
    if ( pi.partyId > 0 )
    {
      map<int,int>::const_iterator cit= partyRatings.find(pi.partyId);
      if (cit == partyRatings.end())
        partyRatings[pi.partyId] = MIN_RATING;
      Party & party = ti.parties[pi.partyId];
      party.rating = max( party.rating, pi.rating );
      ++party.size;
      if (_map && _map->matchmakingSettings)
      {
        const mmaking::RankDescription* maxRankDescr = tbl.FindRank(party.rating);
        const mmaking::RankDescription* mergeRankDescr = tbl.FindRankByIndex(maxRankDescr->mergedIndex);
        if (mergeRankDescr)
        {
          
          if (mergeRankDescr->from > partyRatings[pi.partyId])
          {
            party.minPartyRating = mergeRankDescr->from;
            partyRatings[pi.partyId] = party.minPartyRating;
          }
          else
            party.minPartyRating = partyRatings[pi.partyId];
        }
        else
        {
          const mmaking::RankDescription* prevRankDescr = tbl.FindRankByIndex(maxRankDescr->index -1 == -1 ? 0 : maxRankDescr->index -1);
          party.minPartyRating = prevRankDescr->from; // получаем минимально допустимый рейтинг для фулки 
                                                      // а он равен рейтингу партии на звание ниже (NUM_TASK). 
        }
      }
    }
  }
  if ( ( teamsInfo.size() != 2 ) || ( teams.size() != 2 ) )
  {
    ErrorTrace( "Team count should be 2" );
    return false;
  }

  return true;
}



void Calculator::CalcFullPartyRatingBonus( IPartyRatingBonusCallback * partyRatingBonusCb, lobby::ETeam::Enum winnerTeam )
{

  for ( PlayerMap::iterator it = players.begin(); it != players.end(); ++it )
  {
    PlayerInfo & pi = it->second;

    if ( !pi.partyId )
      continue;
    
    TeamMap::iterator itti = teamsInfo.find( pi.team );

    NI_VERIFY( itti != teamsInfo.end(), "", continue );

    TeamInfo & ti = itti->second;

    const Party & playerParty = ti.parties[pi.partyId];
    int bonus = partyRatingBonusCb->PartyRatingBonus( playerParty.rating, playerParty.size );
    NI_ASSERT( !ti.fullPartyRatingBonus || ( ti.fullPartyRatingBonus == bonus ), "" );
    ti.fullPartyRatingBonus = bonus;
  }
}



bool Calculator::Calculate( lobby::ETeam::Enum winnerTeam, IPartyRatingBonusCallback * partyRatingBonusCb, const NDb::AdvMapDescription * _map)
{
  if ( !AggregateTeams(_map) )
    return false; 

  if ( partyRatingBonusCb )
    CalcFullPartyRatingBonus( partyRatingBonusCb, winnerTeam);

  for ( PlayerMap::iterator it = players.begin(); it != players.end(); ++it )
  {
    PlayerInfo & pi = it->second;

    TeamMap::iterator mit0 = teamsInfo.find(pi.team);
    NI_VERIFY( mit0 != teamsInfo.end(), "", continue );

    TeamInfo & ti0 = mit0->second;

    TeamMap::iterator mit1 = mit0;
    if (mit0 == teamsInfo.begin())
      mit1++;
    else
      mit1--;
    
    TeamInfo & ti1 = mit1->second;
    float playerRating = 0.0;
    bool isRandomA = true;
    
    if (pi.partyId)
    {   
        const Party & party = ti0.parties[pi.partyId];
        if(party.size >= _map->matchmakingSettings->fullPartySize)
          isRandomA = false;

        if (party.minPartyRating> pi.rating)
          playerRating = party.minPartyRating;
        else
          playerRating = pi.rating;
    }
    else 
    {
       playerRating = pi.rating;
    }

    float odds = 0;
    for ( PlayerMap::const_iterator itOther = players.begin(); itOther != players.end(); ++itOther )
    {
      const PlayerInfo & otherPi = itOther->second;
      if ( otherPi.team == pi.team )
        continue;
      
      bool isRandomB = true;
      float otherRating = otherPi.rating;
      
      if ( otherPi.partyId ) {
          const Party & party1 = ti1.parties[otherPi.partyId];
          if (party1.minPartyRating > otherPi.rating)  
            otherRating = party1.minPartyRating;
          
          if(party1.size >= _map->matchmakingSettings->fullPartySize)
            isRandomB = false;
      }
      if (isRandomA && !isRandomB)
        otherRating += ti1.fullPartyRatingBonus;

      float ratingDiff = otherRating - playerRating;
      float exp = ratingDiff / 400.f;
      odds += 1.f / ( 1.f + pow( 10.0f, exp ) );
    }

    odds /= ti1.membersCount;
    pi.ratingChange = CalculateChange( playerRating, ( pi.team == winnerTeam ) ? 1.f : 0.f, odds );
  } 
  return true;
}



bool Calculator::GetChange( PlayerId playerId, float & ratingChange ) const
{
  float dummy;
  return GetChange( playerId, ratingChange, dummy );
}



bool Calculator::GetChange( PlayerId playerId, float & ratingChange, float & sourceRating ) const
{
  PlayerMap::const_iterator it = players.find(playerId);
  if (it != players.end())
  {
    ratingChange = it->second.ratingChange;
    sourceRating = it->second.rating;
    return true;
  }
  return false;
}



float Calculator::CalculateChange( float playerRating, float winIndex, float odds )
{
  int k;
  if ( playerRating < 2100.0f )
  {
    k = 32.0f;
  }
  else 
  if ( playerRating >= 2100.0f && playerRating < 2400.0f )
  {
    k = 24.0f;
  }
  else
  {
    k = 16.0f;
  }
  return k * ( winIndex - odds );
}

}