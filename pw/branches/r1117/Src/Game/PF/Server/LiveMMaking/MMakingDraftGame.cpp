#include "stdafx.h"
#include "MMakingDraftGame.h"
#include "Db/DBServer.auto.h"
#include "System/InlineProfiler.h"

namespace mmaking
{

void MMakingDraftGame::ClearTeam( lobby::ETeam::Enum _team )
{
  int idx = lobby::ETeam::Index( _team );

  humans[idx].clear();
  bots[idx].clear();

  ResetTeamStatistics( _team );
}



void MMakingDraftGame::Clear()
{
  teamSize = 0;
  ClearTeam( lobby::ETeam::Team1 );
  ClearTeam( lobby::ETeam::Team2 );
}



void MMakingDraftGame::Init( int _teamSize, EBasket::Enum _basket, IHeroesTable * _heroes )
{
  NI_PROFILE_HEAVY_FUNCTION;

  Clear();

  teamSize = _teamSize;
  basket = _basket;
  //manoeuvresFaction = _manoeuvresFaction;
  heroes = _heroes;

  for ( int t = 0; t < 2; ++t )
    humans[t].reserve( _teamSize );

  heroUsage.clear();
  heroUsage.resize( _heroes->MaxShortId() );
  for ( THeroShortId i = 1; i <= _heroes->MaxShortId(); ++i ) {
    const mmaking::SHeroDescription * descr = _heroes->FindDescr( i );
    NI_ASSERT( descr, "" );
    heroUsage[i - 1].descr = *descr;
    heroUsage[i - 1].shortId = i;
  }
}



void MMakingDraftGame::ResetTeamStatistics( lobby::ETeam::Enum _team )
{
  int idx = lobby::ETeam::Index( _team );

  gentlemen[idx] = 0;
  ladies[idx] = 0;
  total[idx] = 0;

  for ( int i = 0; i < heroUsage.size(); ++i )
    heroUsage[i].usedInTeam[idx] = 0;
}



void MMakingDraftGame::ResetStatistics()
{
  ResetTeamStatistics( lobby::ETeam::Team1 );
  ResetTeamStatistics( lobby::ETeam::Team2 );
}



void MMakingDraftGame::UpdateMemberStatistics( lobby::ETeam::Enum _team, lobby::ESex::Enum _sex, THeroShortId _heroId )
{
  int teamIndex = lobby::ETeam::Index( _team );
  ++total[teamIndex];

  if ( _heroId )
    UpdateHeroUsage( _heroId, _team );

  if ( _sex == lobby::ESex::Male )
    ++gentlemen[teamIndex];
  else if ( _sex == lobby::ESex::Female )
    ++ladies[teamIndex];
  else
    NI_ALWAYS_ASSERT( "Invalid hero sex" );
}



bool MMakingDraftGame::CanGoToTeam( lobby::ETeam::Enum _team, int _playersCount )
{
  if ( _team == lobby::ETeam::Team1 )
    return ( total[0] + _playersCount <= teamSize );

  if ( _team == lobby::ETeam::Team2 )
    return ( total[1] + _playersCount <= teamSize );

  return false;
}



int MMakingDraftGame::CountHeroesOfType( lobby::ETeam::Enum _team, THeroShortId _heroId ) const
{
  if ( !_heroId )
    return 0;

  int idx = lobby::ETeam::Index( _team );

  int count = 0;
  for ( int i = 0; i < humans[idx].size(); ++i )
  {
    const MmRequest * req = humans[idx][i];
    for ( int j = 0; j < req->Size(); ++j )
    {
      const SRequestMemberEx & memb = req->Member( j );
      //NI_ASSERT( ( manoeuvresFaction != lobby::ETeam::None ) || ( req->CommonData().team == _team ), "" );
      if ( memb.shortHeroId == _heroId )
        ++count;
    }
  }

  return count;
}



bool MMakingDraftGame::IsHeroUsable( int idx, lobby::ETeam::Enum _faction, lobby::ESex::Enum _sex, EFindHeroMode _findMode, EHeroRestriction::Enum _restriction ) const
{
  const SHeroUsageInfo & info = heroUsage[idx];

  if ( ( _faction != lobby::ETeam::None ) && ( info.descr.faction != lobby::ETeam::None ) )
    if ( info.descr.faction != _faction )
      return false;

  switch ( _findMode ) {
    case eFindHeroForPlayer:
      break;

    case eFindHeroForBot:
      if ( !info.descr.botCanBe )
        return false;
      break;

    case eFindHeroForFoeBot:
      if ( !info.descr.botCanBeAnEnemy )
        if ( _restriction <= EHeroRestriction::Softened )
          return false;
      break;
  }

  if ( _sex != lobby::ESex::Undefined )
    if ( info.descr.sex != _sex )
      if ( _restriction <= EHeroRestriction::Softened )
        return false;

  int teamIndex = lobby::ETeam::Index( _faction );
  if ( info.usedInTeam[teamIndex] )
    if ( _restriction == EHeroRestriction::Strict )
      return false;

  return true;
}



THeroShortId MMakingDraftGame::RollHeroForPlayer( lobby::ESex::Enum * _heroSex, lobby::ETeam::Enum _faction, lobby::ESex::Enum _sex, EFindHeroMode _findMode ) const
{
  const static EHeroRestriction::Enum restrictions[] = { EHeroRestriction::Strict, EHeroRestriction::Softened, EHeroRestriction::AnySuitable };
  const static int restrictionsCount = sizeof( restrictions ) / sizeof( EHeroRestriction::Enum );

  for ( int r = 0; r < restrictionsCount; ++r )
  {
    heroRollBuffer.clear();
    heroRollBuffer.reserve( heroUsage.size() );

    for ( int i = 0; i < heroUsage.size(); ++i )
      if ( IsHeroUsable( i, _faction, _sex, _findMode, restrictions[r] ) )
        heroRollBuffer.push_back( i );
    if ( !heroRollBuffer.empty() )
      break;
  }

  NI_VERIFY( !heroRollBuffer.empty(), "There is no ANY available hero!", return 0 );

  int die = rand() % heroRollBuffer.size();
  int index = heroRollBuffer[die];
  const SHeroUsageInfo & info = heroUsage[index];

  heroRollBuffer.clear(); //clean up 

  if ( _heroSex )
    *_heroSex = info.descr.sex;
  return info.shortId;
}



void MMakingDraftGame::AddMembers( MmRequest * _req, lobby::ETeam::Enum _factionOverride )
{
  NI_PROFILE_HEAVY_FUNCTION;
  /*
  if ( _factionOverride != lobby::ETeam::None ) {
    NI_ASSERT( manoeuvresFaction != lobby::ETeam::None, "" );
  }
 */

  lobby::ETeam::Enum faction = ( _factionOverride == lobby::ETeam::None ) ? _req->CommonData().team : _factionOverride;
  NI_ASSERT( TeamSize( faction ) <= teamSize, "" );

  for ( int j = 0; j < _req->Size(); ++j )
  {
    const SRequestMemberEx & memb = _req->Member( j );
    
    UpdateMemberStatistics( faction, memb.sex, memb.shortHeroId );
  }

  int idx = lobby::ETeam::Index( faction );
  humans[idx].push_back( _req );
}



void MMakingDraftGame::UpdateHeroUsage( THeroShortId _shortHeroId, lobby::ETeam::Enum _team )
{
  int teamIndex = ( _team == lobby::ETeam::Team1 ) ? 0 : 1;

  bool updated = false;
  for ( int i = 0; i < heroUsage.size(); ++i )
    if ( heroUsage[i].shortId == _shortHeroId )
    {
      updated = true;
      ++heroUsage[i].usedInTeam[teamIndex];
      break;
    }
  NI_ASSERT( updated, "" );
}



void MMakingDraftGame::AssignAutoHeroes()
{
  for ( int t = 0; t < 2; ++t )
    for ( int i = 0; i < humans[t].size(); ++i )
    {
      MmRequest * req = humans[t][i];
      for ( int j = 0; j < req->Size(); ++j )
      {
        SRequestMemberEx & memb = req->Member( j );

        if ( memb.shortHeroId )
          continue;

        memb.shortHeroId = RollHeroForPlayer( 0, req->CommonData().team, memb.sex, eFindHeroForPlayer );
        NI_VERIFY( memb.shortHeroId, "", return );

        UpdateHeroUsage( memb.shortHeroId, req->CommonData().team );
      }
    }
}



void MMakingDraftGame::AddBots( int ladiesCount )
{
  const int size = GameSize();
  if ( size >= teamSize * 2 )
    return;

  for ( int t = 0; t < 2; ++t )
  {
    lobby::ETeam::Enum team = lobby::ETeam::Index( t );

    EFindHeroMode findMode = eFindHeroForBot;
    if ( !humans[t ? 0 : 1].empty() )
      findMode = eFindHeroForFoeBot;

    bots[t].resize( teamSize - total[t] );
    for ( int i = 0; i < bots[t].size(); ++i )
    {
      lobby::ESex::Enum requiredSex = lobby::ESex::Undefined;
      if ( ladiesCount >= 0 )
        requiredSex = ( ladies[t] < ladiesCount ) ? lobby::ESex::Female : lobby::ESex::Male;

      lobby::ESex::Enum botSex = lobby::ESex::Undefined;
      THeroShortId hero = RollHeroForPlayer( &botSex, team, requiredSex, findMode );
      NI_VERIFY( hero, "", continue );
      NI_VERIFY( botSex != lobby::ESex::Undefined, "", continue );

      bots[t][i].hero = hero;

      UpdateMemberStatistics( team, botSex, hero );
    }
  }
}



void MMakingDraftGame::AddBot( lobby::ETeam::Enum _team, const string & _heroId )
{
  NI_VERIFY( GameSize() < teamSize * 2, "", return );

  const mmaking::SHeroDescription * descr = heroes->FindDescr( _heroId );
  NI_VERIFY( descr, "", return );
  NI_ASSERT( ( descr->faction == lobby::ETeam::None ) || ( descr->faction == _team ), "" );

  int tidx = lobby::ETeam::Index( _team );
  bots[tidx].push_back( SBotMember( descr->shortId ) );

  UpdateMemberStatistics( _team, descr->sex, descr->shortId );
}



MmRequest * MMakingDraftGame::GetRequest( lobby::ETeam::Enum _team, int _idx )
{
  const THumans & h = humans[lobby::ETeam::Index( _team )];
  NI_VERIFY( _idx >= 0 && _idx < h.size(), "", return 0 );
  return h[_idx];
}



void MMakingDraftGame::Check( NDb::EMapType _mapType ) const
{
  const bool pve = ( _mapType == NDb::MAPTYPE_COOPERATIVE );
  NI_ASSERT( GameSize() == ( pve ? teamSize : teamSize * 2 ), "" );
  if ( pve )
  {
    int t0 = total[0] ? 0 : 1, t1 = total[0] ? 1 : 0;
    NI_ASSERT( ( total[t0] == teamSize ) && ( total[t1] == 0 ), "" );
    NI_ASSERT( gentlemen[t0] + ladies[t0] == teamSize, "" );
    NI_ASSERT( gentlemen[t1] + ladies[t1] == 0, "" );
  }
  else
  {
    NI_ASSERT( ( total[0] == teamSize ) && ( total[1] == teamSize ), "" );
    NI_ASSERT( gentlemen[0] + ladies[0] == teamSize, "" );
    NI_ASSERT( gentlemen[1] + ladies[1] == teamSize, "" );
  }
}



EBasket::Enum MMakingDraftGame::DetermineBasket( NDb::EMapType _mapType ) const
{
  int boobs = 0, leaves = 0;
  for ( int t = 0; t < 2; ++t )
    for ( int i = 0; i < humans[t].size(); ++i )
      switch ( humans[t][i]->Basket() )
      {
        case EBasket::Newbie:
          ++boobs;
          break;
          
        case EBasket::Leaver:
          ++leaves;
          break;

        case EBasket::Normal:
        default:
          break;
      }

  if ( boobs > 0 )
    return EBasket::Newbie;

  if ( leaves > 0 )
    return EBasket::Leaver;

  return EBasket::Normal;
}



void MMakingDraftGame::ProduceResult( SGame & _game, NDb::EMapType _mapType, const string & _mapId, timer::Time _now ) const
{
  const bool pve = ( _mapType == NDb::MAPTYPE_COOPERATIVE );

  _game.mapType = _mapType;
  _game.mapId = _mapId;
//  _game.manoeuvresFaction = manoeuvresFaction;
  _game.basket = ( basket != EBasket::Undefined ) ? basket : DetermineBasket( _mapType );

  int humansCount = 0;
  for ( int t = 0; t < 2; ++t )
    for ( int i = 0; i < humans[t].size(); ++i )
      humansCount += humans[t][i]->Size();

  _game.humans.reserve( humansCount );

  if ( !pve )
    _game.bots.reserve( bots[0].size() + bots[1].size() );

  for ( int t = 0; t < 2; ++t )
  {
    lobby::ETeam::Enum faction = lobby::ETeam::Index( t );
    for ( int i = 0; i < humans[t].size(); ++i )
    {
      const MmRequest * req = humans[t][i];
//      NI_ASSERT( ( manoeuvresFaction != lobby::ETeam::None ) || ( req->CommonData().team == faction ), "" );

      _game.humans.push_back( SGameParty() );
      SGameParty & party = _game.humans.back();
      party.common = req->CommonData();
      party.common.team = faction;
      party.waitTime = _now - req->StartTime();
      party.requestUId = req->RequestId();

      party.members.reserve( req->Size() );

      for ( int j = 0; j < req->Size(); ++j )
      {
        const SRequestMemberEx & memb = req->Member( j );
        party.members.push_back( memb );
        party.members[j].heroId = heroes->Find( memb.shortHeroId );
      }
    }

    if ( !pve )
      for ( int i = 0; i < bots[t].size(); ++i )
      {
        const SBotMember & src = bots[t][i];

        const SHeroDescription * heroDescr = heroes->FindDescr( src.hero );
        NI_VERIFY( heroDescr, "", continue );

        _game.bots.push_back( SBotGameMember() );
        SBotGameMember & dest = _game.bots.back();

        dest.team = lobby::ETeam::Index( t );
        dest.heroId = heroDescr->id;

        RollBotSkin( heroDescr, dest );
      }
  }
}



void MMakingDraftGame::RollBotSkin( const SHeroDescription * heroDescr, SBotGameMember & bot ) const
{
  int skinsAvail = 0;
  for ( int j = 0; j < heroDescr->botSkins.size(); ++j )
  {
    if ( heroDescr->botSkins[j].faction != lobby::ETeam::None )
      if ( heroDescr->botSkins[j].faction != bot.team )
        continue;
    ++skinsAvail;
  }

  int die = rand() % ( skinsAvail + 1 ); //Give defauklt skin a fair chance
  if ( die == skinsAvail )
    return;

  for ( int j = 0; j < heroDescr->botSkins.size(); ++j )
  {
    if ( heroDescr->botSkins[j].faction != lobby::ETeam::None )
      if ( heroDescr->botSkins[j].faction != bot.team )
        continue;
    if ( !die )
    {
      bot.heroSkin = heroDescr->botSkins[j].id;
      break;
    }
    --die;
  }
}

} //namespace mmaking
