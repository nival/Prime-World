#ifndef IMMAKINGLOGIC_H_INCLUDED
#define IMMAKINGLOGIC_H_INCLUDED

#include "LiveMMakingTypes.h"
#include <string>


namespace mmaking
{

class IMMakingLogicCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IMMakingLogicCallback, IBaseInterfaceMT );

public:
  virtual void MmResultAddRequest( TRequestUId _requestUId, bool _ok ) = 0;
  virtual void MmResultRemoveRequest( TRequestUId _requestUId, bool _ok ) = 0;
  virtual void MmResultAddReconnectGame( lobby::TGameId _gameId, bool _ok ) = 0;
  virtual void MmResultRemoveReconnectGame( lobby::TGameId _gameId, bool _ok ) = 0;
  //TODO: Replace IMMakingLogic::PopGame() with this call-back??
};


class IHeroesTable;
class MMConfig;

class IMMakingLogic : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IMMakingLogic, IBaseInterfaceMT );

public:
  virtual void SetTime( timer::Time _simulationTime ) = 0;
  virtual void Poll() = 0; //Some may require to be polled
  virtual void OnConfigReload( MMConfig * _cfg, IHeroesTable * _heroes ) = 0;

  virtual void AddGroupRequest( TRequestUId _requestUId, const SRequestCommonData & _commonData, const vector<SRequestMember> & _members, timer::Time _waitTime, IMMakingLogicCallback * _callback ) = 0;
  virtual void RemoveRequest( TRequestUId _requestUId, IMMakingLogicCallback * _callback ) = 0;
  virtual bool PopGame( SGame & _result ) = 0;

  virtual void AddGameForReconnect( lobby::TGameId _gameId, const SGame & _gameData, IMMakingLogicCallback * _callback ) = 0;
  virtual void RemoveGame( lobby::TGameId _gameId, IMMakingLogicCallback * _callback ) = 0;

  virtual bool PopReconnectSlot( SReconnectSlot & _slot ) = 0;

  virtual string GetDebugStatus() = 0;
  virtual void GetLineStatistics( unsigned & team1, unsigned & team2 ) = 0;
};



struct SHeroClassEfficiency
{
  int classes[HeroClassesNumber]; //in percents

  SHeroClassEfficiency() {
    for ( int i = 0; i < HeroClassesNumber; ++i )
      classes[i] = 0;
  }

  void Add( const SHeroClassEfficiency & other ) { for ( int i = 0; i < HeroClassesNumber; ++i ) classes[i] += other.classes[i]; }
  void Sub( const SHeroClassEfficiency & other ) { for ( int i = 0; i < HeroClassesNumber; ++i ) classes[i] -= other.classes[i]; }

  std::string ToString() {
    const char * names[HeroClassesNumber] = { "Tank", "Vang", "Ass", "DD", "Supp", "Jngl" };
    std::string result = "[";
    result.reserve( 64 );
    for ( int i = 0; i < HeroClassesNumber; ++i )
      result += NI_STRFMT( "%s%s:%02d", i ? " " : "", names[i], classes[i] );
    result += "]";
    return result;
  }
};



struct SHeroSkinDescription
{
  string              id;
  lobby::ETeam::Enum  faction;

  SHeroSkinDescription() : faction( lobby::ETeam::None ) {}
};



struct SHeroDescription
{
  string              id;
  THeroShortId        shortId;
  lobby::ESex::Enum   sex;
  lobby::ETeam::Enum  faction;
  bool                botCanBe;
  bool                botCanBeAnEnemy;
  SHeroClassEfficiency classEfficiency;
  vector<SHeroSkinDescription> botSkins;
  vector<THeroShortId> antagonists;

  SHeroDescription() :
  sex( lobby::ESex::Undefined ), faction( lobby::ETeam::None ), botCanBe( true ), botCanBeAnEnemy( true ) {}

  SHeroDescription( const char * _id, lobby::ESex::Enum _sex, lobby::ETeam::Enum _faction ) :
  id( _id ),
  shortId( 0 ),
  sex( _sex ),
  faction( _faction ),
  botCanBe( true ), botCanBeAnEnemy( true ) {}
};



class IHeroesTable : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IHeroesTable, IBaseInterfaceMT );

public:
  virtual THeroShortId MaxShortId() const = 0;
  virtual const SHeroDescription * FindDescr( const string & id ) const = 0;
  virtual const SHeroDescription * FindDescr( THeroShortId id ) const = 0;

  THeroShortId Find( const string & id ) const {
    if ( const SHeroDescription * descr = FindDescr( id ) )
      return descr->shortId;
    return 0; }

  const char * Find( THeroShortId id ) const {
    if ( const SHeroDescription * descr = FindDescr( id ) )
      return descr->id.c_str();
    return "<unknonwn>"; }
};




struct RankDescription
{
  float           from, to;
  int             index;
  int             mergedIndex;
  int             mergeRanksCount;
  EBasket::Enum   basket;
  bool            highRating;
  string          name;
  bool            useForceMM;
  bool            usePlayerRatingMM;


  RankDescription() :
  from( 0 ), to( 0 ),
  index( 0 ),
  mergedIndex( 0 ),
  mergeRanksCount( 0 ),
  basket( EBasket::Undefined ),
  highRating( false ),
  useForceMM( false ),
  usePlayerRatingMM(false)
  {}
};



class IRankTable : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IRankTable, IBaseInterfaceMT );

public:
  virtual const RankDescription * FindRank( float _rating ) const = 0;
  virtual const RankDescription * FindRankByIndex( int _idx  ) const = 0;
  virtual const RankDescription * FindRankByMergedIndex( int _mergedIdx ) const = 0;
  virtual int RanksNumber() const = 0;
  virtual int MergedRanksNumber() const = 0;
};

} //namespace mmaking

#endif //IMMAKINGLOGIC_H_INCLUDED
