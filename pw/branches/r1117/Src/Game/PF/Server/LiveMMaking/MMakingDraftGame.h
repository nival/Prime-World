#ifndef DISCRETEMMDRAFTGAME_H_INCLUDED
#define DISCRETEMMDRAFTGAME_H_INCLUDED

#include "MMakingRequest.h"


namespace NDb
{
  enum EMapType;
}


namespace mmaking
{

class MMakingDraftGame
{
public:
  MMakingDraftGame()
  {
    Clear();
  }

  void ClearTeam( lobby::ETeam::Enum _team );
  void Clear();
  void Init( int _teamSize, EBasket::Enum _basket, IHeroesTable * _heroes );

  int Gentlemen( lobby::ETeam::Enum team ) const { return gentlemen[lobby::ETeam::Index( team )]; }
  int Ladies( lobby::ETeam::Enum team ) const { return ladies[lobby::ETeam::Index( team )]; }
  int TeamSize( lobby::ETeam::Enum team ) const { return total[lobby::ETeam::Index( team )]; }
  int RequestsCount( lobby::ETeam::Enum _team ) const { return humans[lobby::ETeam::Index( _team )].size(); }
  int GameSize() const { return total[0] + total[1]; }

  bool CanGoToTeam( lobby::ETeam::Enum _team, int _playersCount );
  int CountHeroesOfType( lobby::ETeam::Enum _team, THeroShortId _heroId ) const;
  void AddMembers( MmRequest * _req, lobby::ETeam::Enum _factionOverride = lobby::ETeam::None );
  void AssignAutoHeroes();
  void AddBots( int ladiesCount = -1 );
  void AddBot( lobby::ETeam::Enum _team, const string & _heroId );

  MmRequest * GetRequest( lobby::ETeam::Enum _team, int _idx );
  void Check( NDb::EMapType _mapType ) const;

  void ProduceResult( SGame & _game, NDb::EMapType _mapType, const string & _mapId, timer::Time _now ) const;

private:
  struct SBotMember
  {
    THeroShortId         hero;

    SBotMember() : hero( 0 ) {}
    explicit SBotMember( THeroShortId _hero ) : hero( _hero ) {}
  };

  struct SHeroUsageInfo
  {
    int                       usedInTeam[2];
    THeroShortId              shortId;
    mmaking::SHeroDescription descr;
    SHeroUsageInfo() : shortId( 0 ) { usedInTeam[0] = usedInTeam[1] = 0; }
  };

  enum EFindHeroMode { eFindHeroForPlayer, eFindHeroForBot, eFindHeroForFoeBot };

  typedef vector<SHeroUsageInfo> THeroUsage;
  typedef vector<StrongMT<MmRequest> > THumans;
  typedef vector<SBotMember> TBots;

  int           teamSize;
  EBasket::Enum basket;
  //lobby::ETeam::Enum manoeuvresFaction;
  THumans       humans[2];
  TBots         bots[2];
  int           gentlemen[2], ladies[2], total[2];
  THeroUsage    heroUsage;
  StrongMT<IHeroesTable> heroes;

  mutable vector<int>   heroRollBuffer;

  void ResetTeamStatistics( lobby::ETeam::Enum _team );
  void ResetStatistics();
  void UpdateMemberStatistics( lobby::ETeam::Enum _team, lobby::ESex::Enum _sex, THeroShortId _heroId );
  void UpdateHeroUsage( THeroShortId _shortHeroId, lobby::ETeam::Enum _team );

  struct EHeroRestriction {
    enum Enum { Strict, Softened, AnySuitable };
  };
  bool IsHeroUsable( int idx, lobby::ETeam::Enum _team, lobby::ESex::Enum _sex, EFindHeroMode _findMode, EHeroRestriction::Enum _restriction ) const;
  THeroShortId RollHeroForPlayer( lobby::ESex::Enum * _heroSex, lobby::ETeam::Enum _team, lobby::ESex::Enum _sex, EFindHeroMode _findMode ) const;
  EBasket::Enum DetermineBasket( NDb::EMapType _mapType ) const;
  void RollBotSkin( const SHeroDescription * heroDescr, SBotGameMember & bot ) const;
};

} //namespace mmaking

#endif //DISCRETEMMDRAFTGAME_H_INCLUDED
