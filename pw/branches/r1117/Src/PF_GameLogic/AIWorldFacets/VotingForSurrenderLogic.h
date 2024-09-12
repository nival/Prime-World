#ifndef VOTINGFORSURRENDER_H_A0242D48_60
#define VOTINGFORSURRENDER_H_A0242D48_60

#include "./../../System/TimeHelpers.h"
#include "../PFWorldObjectBase.h"
#include "./../../System/NameMap.h"
#include "UI/DBVotingForSurrender.h"
#include "System/StarForce/StarForce.h"


namespace NGameX { 
  class ClientVotingForSurrender;  

}

namespace NWorld 
{ 
class PFBaseHero;
class PFBaseUnit;

namespace AIWorldFacets
{

class SimpleTimerWitnNameMap: public SimpleTimer, public NNameMap::Map
{
  NAMEMAP_DECLARE;
public:
  ZDATA_(SimpleTimer)
  ZNOPARENT(NNameMap::Map)
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(SimpleTimer*)this); return 0; }
  
  float GetTimeToAlarmMinutesFloor() const { return floor(GetTimeToAlarm() / 60); }
  float GetTimeToAlarmMinutesCeil() const { return ceil(GetTimeToAlarm() / 60); }
  float GetTimeToAlarmSecOnlyFloor() const { return floor(fmod( GetTimeToAlarm(), 60)); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VotingForSurrenderNameMap;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VotingForSurrenderLogic: public PFWorldObjectBase, public NNameMap::Map
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x67884C80, VotingForSurrenderLogic, NGameX::ClientVotingForSurrender )
  NAMEMAP_DECLARE;
  friend class VotingForSurrenderNameMap;
  typedef VotingForSurrenderNameMap NameMap;
public:
  enum VoteResult
  {
    VotedForFight,
    VotedForSurrender
  };

  typedef map<int, VoteResult> PlayersVoteResult;
    
  struct State
  { 
    State() {}
    bool IsVotingInProgress() const { return !result.empty(); }
    void Clear() { result.clear(); }
    ZDATA
    ZNOPARENT(NNameMap::Map)
    PlayersVoteResult result;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&result); return 0; }
  
    friend bool operator==( const State &s1, const State &s2 ) { return s1.result == s2.result; }
    friend bool operator!=( const State &s1, const State &s2 ) { return  !(s1 == s2); }
  };
  
  struct Statistics
  {
    int playersCount;
    int votesForSurrender;
    int votesForFight;
    
    Statistics(): playersCount(0), votesForSurrender(0), votesForFight(0) {}  
  };
  
public:
  VotingForSurrenderLogic();
  
  VotingForSurrenderLogic( 
    PFWorld* pWorld, NCore::ETeam::Enum team, 
    NDb::Ptr<NDb::VotingForSurrender> pDb
  );
  
  void InitPerMissionData( NDb::Ptr<NDb::VotingForSurrenderPerMission> pDbMission );
  
  void Start( CPtr<PFPlayer> pPlayer );
  void MakeDecision( CPtr<PFPlayer> pPlayer, VoteResult result );
  void Abort();
  
  virtual bool Step( float dtInSeconds );
  
  const State &GetCurrState() const { return state; }
  STARFORCE_EXPORT void CalcStatistics( const State &state, Statistics &stat ) const;
  NCore::ETeam::Enum GetTeam() const { return team; }
  const wstring &GetTeamName() const;

  int GetSurrenderVotes() const { return surrenderVotes; }
  
private:
  void Init( NCore::ETeam::Enum team, NDb::Ptr<NDb::VotingForSurrender> pDb, NDb::Ptr<NDb::VotingForSurrenderPerMission> pDbMission );
  STARFORCE_EXPORT void CheckForVotingComplete();
  STARFORCE_EXPORT void CheckForVotingCompleteImpl();
  bool UpdateLeavers();
  void StartSurrender();
  void StopVoting();
  void ResetVoting();
  void SendUserMsg( NDb::VFSUserMessages msg, const NameMap &map ) const;
  virtual void Reset();

  bool TryVoteForBotPlayer(const NWorld::PFPlayer* const player);
  bool TryVoteForDisconnectedPlayer(const NWorld::PFPlayer* const player);
private:    
  ZDATA_(PFWorldObjectBase)
  ZNOPARENT(NNameMap::Map)
  NCore::ETeam::Enum team;
  State state;
  SimpleTimerWitnNameMap votingCooldown;  
  SimpleTimer beforeSurrender;
  SimpleTimer votingDuration;
  int surrenderVotes; //¬ыставл€етс€ при голосовании за сдачу
  NDb::Ptr<NDb::VotingForSurrender> pDb;
  NDb::Ptr<NDb::VotingForSurrenderPerMission> pDbMission;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&team); f.Add(3,&state); f.Add(4,&votingCooldown); f.Add(5,&beforeSurrender); f.Add(6,&votingDuration); f.Add(7,&surrenderVotes); f.Add(8,&pDb); f.Add(9,&pDbMission); return 0; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VotingForSurrenderNameMap : public NNameMap::Map
{
  NAMEMAP_DECLARE;

public:
  explicit VotingForSurrenderNameMap( CPtr<VotingForSurrenderLogic> pThis ):
    pThis(pThis)
  {}
  
  VotingForSurrenderNameMap( CPtr<VotingForSurrenderLogic> pThis, CPtr<NWorld::PFPlayer> pPlayer ):
    pThis(pThis), pPlayer(pPlayer)
  {}
  
  VotingForSurrenderNameMap( CPtr<VotingForSurrenderLogic> pThis, const VotingForSurrenderLogic::Statistics &stat ):
    pThis(pThis), stat(stat)
  {}
  
  CPtr<NWorld::PFPlayer> GetPlayer() const { return pPlayer; }
  NCore::ETeam::Enum GetTeam() const { return pThis->GetTeam(); }
  
private:
  CPtr<NWorld::PFPlayer> pPlayer;
  CPtr<VotingForSurrenderLogic> pThis;
  VotingForSurrenderLogic::Statistics stat;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NCore::WorldCommand* VotingForSurrenderStartCommandCreate( CPtr<PFPlayer> pPlayer );
NCore::WorldCommand* VotingForSurrenderMakeDecisionCommandCreate( CPtr<PFPlayer> pPlayer, bool vote );


}

}

#endif //#define VOTINGFORSURRENDER_H_A0242D48_60