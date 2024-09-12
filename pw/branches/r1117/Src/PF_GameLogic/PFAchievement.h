#pragma once

#include "PFStatistics.h"
#include "PFUIEvent.h"
#include "DBStats.h"
#include "PFMinigameCommon.h"
#include "StatisticsStreak.h"

namespace NWorld
{

class PFKillerVictimEvent : public NGameX::PFUIEvent
{
public:
  PFKillerVictimEvent( NDb::Ptr<NDb::UIEvent> const& dbDesc, NWorld::PFBaseUnit* owner = 0 ) : PFUIEvent(dbDesc, owner) {};
  void SetVictim( PFBaseHero * victim ) { pVictim = victim; }
  CPtr<PFBaseHero> const &  GetVictim() const { return pVictim; }

  virtual bool IsCurrentHeroEventParticipant( NWorld::PFPlayer const * pCurentPlayer );
private:
  CPtr<PFBaseHero> pVictim;
};

///////////////////////////////////////////////////////////////////////////////////////////////
// Achievements stuff
///////////////////////////////////////////////////////////////////////////////////////////////

class PFAchievBase : public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS(0x4D738341, PFAchievBase);

public:
  explicit PFAchievBase() {}
  PFAchievBase( NDb::AchievBase const& db, PFWorld* world );
  virtual void Init( const CPtr<PFBaseHero> owner, CPtr<PFStatistics> pStatistics );
  virtual void CreateUIEvent();
  virtual void OnOwnerDie      ( ) {} ;

  virtual void OnKill          ( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {};
  virtual void OnAssist        ( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {};

  virtual void OnApplicatorUse ( const PFBaseApplicator* pAppl, float curTime ) {} ;

  virtual void OnTowerDestroy  ( const CPtr<PFTower>& pTower ) {} ;
  virtual void OnTowerAssist   ( const CPtr<PFTower>& pTower ) {} ;

  virtual void OnVictory       ( const NDb::EFaction failedFaction ) {};

#ifndef _SHIPPING
  virtual void OnCheatPlay( float time );
	virtual bool NeedToBeStepped() { return true; }
  virtual bool Step(float dtInSeconds);
  float timeToPlayFakeAchiev;
#else
	virtual bool NeedToBeStepped() { return false; }
#endif

  // priestess events
  virtual void OnHeartsFromMG     ( float hearts ) {} ;
  virtual void OnMinigameComplete ( const NDb::DBID &game ) {} ;
  virtual void OnMinigameLevelEnd ( const NDb::DBID &game, int levelIndex, EMinigameLevelStatus::Enum status ) {} ;

  const NDb::Ptr<NDb::AchievBase>& GetDBBase() const { return pDB; }

  virtual const NDb::Ptr<NDb::Texture>& GetImage() const { return pDB->image; }
  virtual const CTextRef& GetTooltip() const { return pDB->tooltip; }

  int GetRank() { return maxRank; }

  int GetCount() const { return count; }

  ZDATA_(PFWorldObjectBase)
  CPtr<PFBaseHero> pOwner;
  CPtr<PFStatistics> pStatistics;

  // total achievement count
  int count;
  // for break on death ruler achievements
  int maxRank;

  // score section
  int score;
  int newScore;
	NDb::Ptr<NDb::AchievBase> pDB;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&pOwner); f.Add(3,&pStatistics); f.Add(4,&count); f.Add(5,&maxRank); f.Add(6,&score); f.Add(7,&newScore); f.Add(8,&pDB); return 0; }

protected:
  typedef NDb::AchievBase CreateParams;

  void Process();

  virtual void ProcessCustom() { maxRank = 1; };
  virtual void SendUIEvent();
  virtual void UpdateScore();
  bool IsNoAssistance( const CPtr<PFBaseUnit>& pVictim );

  CObj<NGameX::PFUIEvent> pEvent; //TODOLOF
};

class PFAchievRuler : public DBLinker<PFAchievBase, NDb::AchievRuler>
{
  WORLD_OBJECT_METHODS(0x4D738B40, PFAchievRuler);

public:
  explicit PFAchievRuler() {}
  PFAchievRuler( CreateParams const &db, PFWorld* world );

  virtual void OnOwnerDie();
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}

#ifndef _SHIPPING
  virtual void OnCheatPlay( float time );
#endif

  ZDATA_(DBLinker)
  int curVal;
  int maxSpree;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&curVal); f.Add(3,&maxSpree); return 0; }
protected:
  virtual void ProcessCustom();
  virtual void SendUIEvent();

  void IncreaseValue();
};

class PFAchievFirstBlood : public DBLinker<PFAchievBase, NDb::AchievFirstBlood>
{
  WORLD_OBJECT_METHODS(0x4D738B41, PFAchievFirstBlood);

  explicit PFAchievFirstBlood() {}
public:
  PFAchievFirstBlood( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}

  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievDoubleKill : public DBLinker<PFAchievBase, NDb::AchievDoubleKill>
{
  WORLD_OBJECT_METHODS(0x4D738B42, PFAchievDoubleKill);

  explicit PFAchievDoubleKill() {}
public:
  PFAchievDoubleKill( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievMassKill : public DBLinker<PFAchievBase, NDb::AchievMassKill>
{
  WORLD_OBJECT_METHODS(0x4D738B44, PFAchievMassKill);

  explicit PFAchievMassKill() {}
public:
  PFAchievMassKill( CreateParams const &db, PFWorld* world ) : Base(db, world), maxKillCount(0) {}

  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  int maxKillCount;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&maxKillCount); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievDuel : public DBLinker<PFAchievBase, NDb::AchievDuel>
{
  WORLD_OBJECT_METHODS(0x4D738B45, PFAchievDuel);

  explicit PFAchievDuel() {}
public:
  PFAchievDuel( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievChase : public DBLinker<PFAchievBase, NDb::AchievChase>
{
  WORLD_OBJECT_METHODS(0x4D738B46, PFAchievChase);

  explicit PFAchievChase () {}
public:
  PFAchievChase( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievAvenge : public DBLinker<PFAchievBase, NDb::AchievAvenge>
{
  WORLD_OBJECT_METHODS(0x4D738B47, PFAchievAvenge);

  explicit PFAchievAvenge () {}
public:
  PFAchievAvenge( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievDominate : public DBLinker<PFAchievBase, NDb::AchievDominate>
{
  WORLD_OBJECT_METHODS(0x4D738B49, PFAchievDominate);

  explicit PFAchievDominate() {}
public:
	PFAchievDominate( CreateParams const &db, PFWorld* world );

#ifndef _SHIPPING
  virtual void OnCheatPlay( float time );
#endif

  virtual void CreateUIEvent();
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
	int curVal; // tmp variable
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&curVal); return 0; }
protected:
  virtual void ProcessCustom();
  virtual void SendUIEvent();

};

class PFAchievVendetta : public DBLinker<PFAchievBase, NDb::AchievVendetta>
{
  WORLD_OBJECT_METHODS(0x4D738B4A, PFAchievVendetta);

  explicit PFAchievVendetta () {}
public:
  PFAchievVendetta( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void CreateUIEvent();
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
#ifndef _SHIPPING
  virtual void OnCheatPlay( float time );
#endif
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievCeremonialKill : public DBLinker<PFAchievBase, NDb::AchievCeremonialKill>
{
  WORLD_OBJECT_METHODS(0x4D738B4B, PFAchievCeremonialKill);

  explicit PFAchievCeremonialKill () {}
public:
  PFAchievCeremonialKill( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievKillingSpree : public DBLinker<PFAchievRuler, NDb::AchievKillingSpree>
{
  WORLD_OBJECT_METHODS(0x4D738B4C, PFAchievKillingSpree);
  
  explicit PFAchievKillingSpree() {}
public:
  PFAchievKillingSpree( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void UpdateScore();
};

class PFAchievDoubleAssist : public DBLinker<PFAchievBase, NDb::AchievDoubleAssist>
{
  WORLD_OBJECT_METHODS(0x4D738B4D, PFAchievDoubleAssist);

  explicit PFAchievDoubleAssist() {}
public:
  PFAchievDoubleAssist( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievMassAssist : public DBLinker<PFAchievBase, NDb::AchievMassAssist>
{
  WORLD_OBJECT_METHODS(0x4D738B4E, PFAchievMassAssist);

  explicit PFAchievMassAssist () {}
public:
  PFAchievMassAssist( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

struct SaviourInfo
{
  ZDATA
  float timeToProcess;
  bool waitForDie;
  float timeToLog;
  ConstPtr<PFBaseHero> lamb;  
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&timeToProcess); f.Add(3,&waitForDie); f.Add(4,&timeToLog); f.Add(5,&lamb); return 0; }

  SaviourInfo() : timeToProcess(0.0f), waitForDie(false), timeToLog(0.0f), lamb(0) {}
};

class PFAchievSaviour : public DBLinker<PFAchievBase, NDb::AchievSaviour>
{
  WORLD_OBJECT_METHODS(0x4D738B4F, PFAchievSaviour);

  explicit PFAchievSaviour () {}
public:
  PFAchievSaviour( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnApplicatorUse ( const PFBaseApplicator* pAppl, float curTime );
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual bool NeedToBeStepped() { return true; }
  virtual bool Step(float dtInSeconds);
  void CheckForRunProcess( const PFBaseHero* lamb, float time );
  ZDATA_(DBLinker)
  nstl::vector<SaviourInfo> saviourInfos;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&saviourInfos); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievMasterControl : public DBLinker<PFAchievRuler, NDb::AchievMasterControl>
{
  WORLD_OBJECT_METHODS(0x4D738B50, PFAchievMasterControl);

  explicit PFAchievMasterControl () {}
public:
  PFAchievMasterControl( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist ( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void UpdateScore();
};

class PFAchievAssistingSpree : public DBLinker<PFAchievRuler, NDb::AchievAssistingSpree>
{
  WORLD_OBJECT_METHODS(0x4D738B51, PFAchievAssistingSpree);

  explicit PFAchievAssistingSpree () {}
public:
  PFAchievAssistingSpree( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void UpdateScore();
};

class PFAchievBorderGuard : public DBLinker<PFAchievBase, NDb::AchievBorderGuard>
{
  WORLD_OBJECT_METHODS(0x4D738B52, PFAchievBorderGuard);

  explicit PFAchievBorderGuard() {}
public:
  PFAchievBorderGuard( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievFirstAssault : public DBLinker<PFAchievBase, NDb::AchievFirstAssault>
{
  WORLD_OBJECT_METHODS(0x4D738B53, PFAchievFirstAssault);
  
  explicit PFAchievFirstAssault () {}
public:
  PFAchievFirstAssault (CreateParams const &db, PFWorld* world );

  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnTowerDestroy( const CPtr<PFTower>& pTower );
  virtual void OnTowerAssist ( const CPtr<PFTower>& pTower );
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom();
};

class PFAchievDemolishingSpree : public DBLinker<PFAchievRuler, NDb::AchievDemolishingSpree>
{
  WORLD_OBJECT_METHODS(0x4D738B54, PFAchievDemolishingSpree);

  explicit PFAchievDemolishingSpree() {}
public:
  PFAchievDemolishingSpree( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnTowerDestroy( const CPtr<PFTower>& pTower );
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void UpdateScore();
};

class PFAchievTowerDeny : public DBLinker<PFAchievBase, NDb::AchievTowerDeny>
{
  WORLD_OBJECT_METHODS(0x4D738B55, PFAchievTowerDeny);

  explicit PFAchievTowerDeny() {}
public:
  PFAchievTowerDeny( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnTowerDestroy( const CPtr<PFTower>& pTower );
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
private:
  virtual void ProcessCustom() {};
};

class PFAchievClearWay : public DBLinker<PFAchievBase, NDb::AchievClearWay>
{
  WORLD_OBJECT_METHODS(0x4D738B56, PFAchievClearWay);

  explicit PFAchievClearWay () {}
public:
  PFAchievClearWay( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnTowerDestroy( const CPtr<PFTower>& pTower );
  virtual void OnTowerAssist ( const CPtr<PFTower>& pTower );
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
private:
  virtual void ProcessCustom() {};
};

class PFAchievBaseStrike : public DBLinker<PFAchievBase, NDb::AchievBaseStrike>
{
  WORLD_OBJECT_METHODS(0x4D738B57, PFAchievBaseStrike);

  explicit PFAchievBaseStrike () {}
public:
  PFAchievBaseStrike(CreateParams const &db, PFWorld* world );

  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  int barracks;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&barracks); return 0; }
private:
  virtual void ProcessCustom() {};
};

class PFAchievVandalism : public DBLinker<PFAchievRuler, NDb::AchievVandalism>
{
  WORLD_OBJECT_METHODS(0x4D738B58, PFAchievVandalism);

  explicit PFAchievVandalism () {}
public:
  PFAchievVandalism( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void UpdateScore();
};

class PFAchievWarLord : public DBLinker<PFAchievRuler, NDb::AchievWarLord>
{
  WORLD_OBJECT_METHODS(0x4D738B59, PFAchievWarLord);

  explicit PFAchievWarLord () {}
public:
  PFAchievWarLord( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void UpdateScore();
};

class PFAchievCleanUpCreeps : public DBLinker<PFAchievBase, NDb::AchievCleanUpCreeps>
{
  WORLD_OBJECT_METHODS(0x4D738B5A, PFAchievCleanUpCreeps);

  explicit PFAchievCleanUpCreeps () {}
public:
	PFAchievCleanUpCreeps(CreateParams const &db, PFWorld* world );

  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  vector<float> creepKillTime;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&creepKillTime); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievDragonSlayer : public DBLinker<PFAchievBase, NDb::AchievDragonSlayer>
{
  WORLD_OBJECT_METHODS(0x4D738B5B, PFAchievDragonSlayer);

  explicit PFAchievDragonSlayer () {}
public:
	PFAchievDragonSlayer(CreateParams const &db, PFWorld* world );

  virtual void OnKill  ( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  ZDATA_(DBLinker)
  bool was;
  float time;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&was); f.Add(3,&time); return 0; }
protected:
  virtual void ProcessCustom() {};

  bool IsDragon(class PFBaseUnit const *pUnit)
  {
    typedef nstl::vector<NDb::Ptr<NDb::Creature>> Creatures;
    Creatures dragons = GetDB().dragons;

    for ( Creatures::iterator iter = dragons.begin(); iter != dragons.end(); iter++ )
    {
      if ( pUnit->DbUnitDesc() == *iter )
      {
        return true;
      }
    }
    return false;
  }

};

class PFAchievKittySlayer : public DBLinker<PFAchievBase, NDb::AchievKittySlayer>
{
  WORLD_OBJECT_METHODS(0x37B1DC01, PFAchievKittySlayer);

  explicit PFAchievKittySlayer () {}
public:
	PFAchievKittySlayer(CreateParams const &db, PFWorld* world );

  virtual void OnKill  ( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  ZDATA_(DBLinker)
  int killCount;
  int assistCount;
  float time;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&killCount); f.Add(3,&assistCount); f.Add(4,&time); return 0; }
protected:
  virtual void ProcessCustom() {}

  bool IsKitty(class PFBaseUnit const *pUnit)
  {
    typedef nstl::vector<NDb::Ptr<NDb::Creature>> Creatures;
    Creatures kitties = GetDB().kitties;

    for ( Creatures::iterator iter = kitties.begin(); iter != kitties.end(); iter++ )
    {
      if ( pUnit->DbUnitDesc() == *iter )
      {
        return true;
      }
    }
    return false;
  }

};

class PFAchievLegend : public DBLinker<PFAchievBase, NDb::AchievLegend>
{
  WORLD_OBJECT_METHODS(0x4D738B5C, PFAchievLegend);

  explicit PFAchievLegend () {}
public:
	PFAchievLegend(CreateParams const &db, PFWorld* world );
    
  virtual void OnKill ( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  bool was;
  float time;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&was); f.Add(3,&time); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievForestHunter : public DBLinker<PFAchievRuler, NDb::AchievForestHunter>
{
  WORLD_OBJECT_METHODS(0x4D738B5D, PFAchievForestHunter);
  
  explicit PFAchievForestHunter () {}
public:
  PFAchievForestHunter( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  void UpdateScore();
};

// priestess achievements
class PFAchievStreak : public DBLinker<PFAchievBase, NDb::AchievStreak>
{
  WORLD_OBJECT_METHODS(0x4D739B01, PFAchievStreak);
  
public:
  explicit PFAchievStreak () {}
	PFAchievStreak( CreateParams const &db, PFWorld* world );

  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}

  ZDATA_(DBLinker)
  Statistics::StreakIndexedCounter streak;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&streak); return 0; }
protected:
  void CheckForAchiev();

  virtual void ProcessCustom();
  virtual void SendUIEvent();
};

class PFAchievAscension : public DBLinker<PFAchievStreak, NDb::AchievAscension>
{
  WORLD_OBJECT_METHODS(0x4D738C40, PFAchievAscension);

  explicit PFAchievAscension () {}
public:
  PFAchievAscension( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnMinigameLevelEnd ( const NDb::DBID &game, int levelIndex, EMinigameLevelStatus::Enum status );
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievNecklaceOfGlory : public DBLinker<PFAchievStreak, NDb::AchievNecklaceOfGlory>
{
  WORLD_OBJECT_METHODS(0x4D738C41, PFAchievNecklaceOfGlory);

  explicit PFAchievNecklaceOfGlory () {}
public:
  PFAchievNecklaceOfGlory( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnMinigameLevelEnd ( const NDb::DBID &game, int levelIndex, EMinigameLevelStatus::Enum status );
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievGoldRite : public DBLinker<PFAchievStreak, NDb::AchievGoldRite >
{
  WORLD_OBJECT_METHODS(0x4D738C42, PFAchievGoldRite);

  explicit PFAchievGoldRite () {}
public:
  PFAchievGoldRite( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnMinigameLevelEnd ( const NDb::DBID &game, int levelIndex, EMinigameLevelStatus::Enum status );
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievCraftWoman : public DBLinker<PFAchievBase, NDb::AchievCraftWoman >
{
  WORLD_OBJECT_METHODS(0x4D738C43, PFAchievCraftWoman);

  explicit PFAchievCraftWoman () {}
public:
	PFAchievCraftWoman(CreateParams const &db, PFWorld* world );

  virtual void OnHeartsFromMG( float hearts);
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  float curHearts;
  bool was;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&curHearts); f.Add(3,&was); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievFirstMinigameComplete : public DBLinker<PFAchievBase, NDb::AchievFirstMinigameComplete >
{
  WORLD_OBJECT_METHODS(0x4D738C44, PFAchievFirstMinigameComplete);
	
  explicit PFAchievFirstMinigameComplete () {}
public:
	PFAchievFirstMinigameComplete(CreateParams const &db, PFWorld* world );

  virtual void OnMinigameComplete( const NDb::DBID &game );
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  bool was;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&was); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievSessionDuration : public DBLinker<PFAchievBase, NDb::AchievSessionDuration >
{
  WORLD_OBJECT_METHODS(0xE79BD3C1, PFAchievSessionDuration);

  explicit PFAchievSessionDuration () {}
public:
  PFAchievSessionDuration( CreateParams const &db, PFWorld* world ) : Base( db, world ) {}
  virtual void OnVictory ( const NDb::EFaction failedFaction );
  virtual void OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime ) {}
  ZDATA_(DBLinker)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
protected:
  virtual void ProcessCustom() {};
};

class PFAchievBossSlayer : public DBLinker<PFAchievBase, NDb::AchievBossSlayer>
{
  WORLD_OBJECT_METHODS(0xB19BF4C0, PFAchievBossSlayer);

  explicit PFAchievBossSlayer() : currentDataIdx(-1) {}

  typedef const nstl::vector<NDb::AchievBossSlayerData> CustomAchievData;

  void CreateCustomEvents();
public:
  PFAchievBossSlayer(CreateParams const &db, PFWorld* world );

  virtual const NDb::Ptr<NDb::Texture>& GetImage() const { return currentDataIdx >= 0 ? GetDB().creatures[currentDataIdx].image : PFAchievBase::GetImage(); }
  virtual const CTextRef& GetTooltip() const { return currentDataIdx >= 0 ? GetDB().creatures[currentDataIdx].tooltip : PFAchievBase::GetTooltip(); }  

  virtual void Init( const CPtr<NWorld::PFBaseHero> owner, CPtr<NWorld::PFStatistics> statistics );
  virtual void OnKill  ( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  virtual void OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime );
  ZDATA_(DBLinker)
    bool was;
    float time;
    int currentDataIdx;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&was); f.Add(3,&time); f.Add(4,&currentDataIdx); return 0; }

protected:
  int HasAchievForVictim( const CPtr<PFBaseUnit>& pVictim );
  void ProcessAchiev( int achievData, float curTime  );

  virtual void SendUIEvent();
  virtual void UpdateScore();
  

  virtual void ProcessCustom() {};
  hash_map<NDb::DBID, CObj<NGameX::PFUIEvent> > customEvents;

};


} //namespace NWorld
