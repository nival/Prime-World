#pragma once

#include "IMMakingLogic.h"
#include "HeroesTable.h"
#include "BaseMMaking.h"
#include "MMakingLog.h"
#include "db/DBServer.auto.h"
#include "cxxtest/TestSuite.h"
#include "System/FileSystem/TestFileSystem.h"


class MMakingLogicCallbackMock : public mmaking::IMMakingLogicCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( MMakingLogicCallbackMock, mmaking::IMMakingLogicCallback, BaseObjectMT );

public:
  explicit MMakingLogicCallbackMock( bool _tolerateFail = false ) : lastRequestUId( 0 ), lastGameId( 0 ), tolerateFail( _tolerateFail ) {}

  virtual void MmResultAddRequest( mmaking::TRequestUId _requestUId, bool _ok ) { TS_ASSERT( tolerateFail || _ok ); lastRequestUId = _requestUId; }
  virtual void MmResultRemoveRequest( mmaking::TRequestUId _requestUId, bool _ok ) { TS_ASSERT( tolerateFail || _ok ); lastRequestUId = _requestUId; }
  virtual void MmResultAddReconnectGame( lobby::TGameId _gameId, bool _ok ) { TS_ASSERT( tolerateFail || _ok ); lastGameId = _gameId; }
  virtual void MmResultRemoveReconnectGame( lobby::TGameId _gameId, bool _ok ) { TS_ASSERT( tolerateFail || _ok ); lastGameId = _gameId; }

  mmaking::TRequestUId LastRequestUId() const { return lastRequestUId; }
  lobby::TGameId LastGameId() const { return lastGameId; }

  void Reset() {
    lastRequestUId = 0;
    lastGameId = 0;
  }

  void TolerateFail( bool _yes ) { tolerateFail = _yes; }

private:
  mmaking::TRequestUId  lastRequestUId;
  lobby::TGameId        lastGameId;
  bool                  tolerateFail;
};




class MmRanksMock : public mmaking::IRankTable, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( MmRanksMock, mmaking::IRankTable, BaseObjectMT );
public:
  MmRanksMock()
  {
    ranks[0].from = 0;
    ranks[0].to = 1500;
    ranks[0].index = 0;
    ranks[0].mergedIndex = 0;
    ranks[0].basket = mmaking::EBasket::Newbie;
    ranks[0].name = "newb";
    ranks[1].from = 1500;
    ranks[1].to = 3000;
    ranks[1].index = 1;
    ranks[1].mergedIndex = 1;
    ranks[1].basket = mmaking::EBasket::Normal;
    ranks[1].name = "norm";
  }

  virtual const mmaking::RankDescription * FindRank( float _rating ) const
  {
    if ( _rating > ranks[1].from )
      return ranks + 1;
    return ranks;
  }

  virtual const mmaking::RankDescription * FindRankByIndex( int _idx  ) const
  {
    TS_ASSERT( _idx >= 0 && _idx < 2 );
    return ranks + _idx;
  }

  virtual const mmaking::RankDescription * FindRankByMergedIndex( int _mergedIdx ) const
  {
    TS_ASSERT( _mergedIdx >= 0 && _mergedIdx < 2 );
    return ranks + _mergedIdx;
  }

  virtual int RanksNumber() const { return 2; }
  virtual int MergedRanksNumber() const { return 2; }

  mmaking::RankDescription ranks[2];
};



class MMakingTestBase
{
public:
  MMakingTestBase() {}


  void setUpMmTest( int heroesCount = 30, int botHeroesCount = 20, int enemyBotsHeroesCount = 10, bool maleHeroes = true , bool femaleHeroes = true )
  {
    NDb::SetResourceCache( NDb::CreateGameResourceCache( new TestFileSystem( "", true ), 0 ) );

    mmConfig = mmaking::CreateConfigFromStatics();

    settings = new NDb::MapMMakingSettings;

    mmConfig->logLevel = mmaking::ELogLevel::Normal;

    StrongMT<mmaking::HeroesTable> h = new mmaking::HeroesTable;
    for ( int i = 0; i < heroesCount; ++i ) {
      mmaking::SHeroDescription descr;
      descr.sex = lobby::ESex::Male;
      descr.botCanBe = ( i < botHeroesCount );
      descr.botCanBeAnEnemy = ( i < enemyBotsHeroesCount );

      if ( maleHeroes )
      {
        descr.id = NStr::StrFmt( "M%d", i + 1 );
        h->Add( descr );
      }

      descr.sex = lobby::ESex::Female;
      if ( femaleHeroes )
      {
        descr.id = NStr::StrFmt( "F%d", i + 1 );
        h->Add( descr );
      }
    }

    heroes = h;

    ranks = new MmRanksMock;

    WriteConfig()->ranks.push_back( NDb::MMakingRank() );
    WriteConfig()->ranks.back().debugName = "newb";
    WriteConfig()->ranks.push_back( NDb::MMakingRank() );
    WriteConfig()->ranks.back().debugName = "merc";

    logicCallback = new MMakingLogicCallbackMock;

    nextReqId = 1;
  }


  void tearDownMmTest()
  {
    nextReqId = 0;

    logicCallback = 0;
    heroes = 0;
    settings = 0;
    NDb::SetResourceCache( 0 );
  }


  NDb::MapMMakingSettings * WriteConfig() { return const_cast<NDb::MapMMakingSettings *>( settings.GetPtr() ); }

  const char * MaleHero( int idx ) { return NStr::StrFmt( "M%d", 1 + idx ); }
  const char * FemaleHero( int idx ) { return NStr::StrFmt( "F%d", 1 + idx ); }

protected:
  NDb::Ptr<NDb::MapMMakingSettings>   settings;
  StrongMT<mmaking::MMConfig>         mmConfig;
  StrongMT<MMakingLogicCallbackMock>  logicCallback;
  StrongMT<mmaking::IHeroesTable>     heroes;
  StrongMT<mmaking::IRankTable>       ranks;
  mmaking::TRequestUId                nextReqId;
};
