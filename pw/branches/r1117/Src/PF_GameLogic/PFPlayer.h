#pragma once

#include "PFWorldObjectBase.h"
#include "PFUniTarget.h"
#include "../System/NameMap.h"

namespace NDb
{
  struct PlayerStartInfo;
}

namespace PF_Core
{
  _interface IClientObject;
}

namespace NWorld
{
class PFBaseHero;
class PFAbilityData;

class PlayerBehaviourTracker;

class PFPlayer : public PFWorldObjectBase, public NNameMap::Map
{
  NAMEMAP_DECLARE;
  WORLD_OBJECT_METHODS(0x2C59D340, PFPlayer)

  explicit PFPlayer();

  const bool        chatMuted;

  bool              isLocal;
  timer::Time       timeWhenDisconnected;


  ZDATA_(PFWorldObjectBase)
  ZNOPARENT(NNameMap::Map)
  int               userID;
  CPtr<PFBaseHero>  pHero;
  int               playerID;
  NCore::ETeam::Enum teamID;
  NCore::ETeam::Enum originalTeamID;
  NCore::ESex::Enum zzimaSex;
  bool              isPlaying;
  bool              isActive;
  bool              aiForLeaversEnabled;
  int               aiForLeaversThreshold;
  int               aiStartTimer;

  bool              disconnected;
  bool              leaver;

  CObj<PlayerBehaviourTracker> behaviourTracker;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&userID); f.Add(3,&pHero); f.Add(4,&playerID); f.Add(5,&teamID); f.Add(6,&originalTeamID); f.Add(7,&zzimaSex); f.Add(8,&isPlaying); f.Add(9,&isActive); f.Add(10,&aiForLeaversEnabled); f.Add(11,&aiForLeaversThreshold); f.Add(12,&aiStartTimer); f.Add(13,&disconnected); f.Add(14,&leaver); f.Add(15,&behaviourTracker); return 0; }

  PFPlayer( PFWorld * _world, 
            int _playerID,
            NCore::ETeam::Enum _teamID,
            NCore::ETeam::Enum _originalTeamID,
            int _userID,
            NCore::ESex::Enum _zzimaSex,
            bool _aiForLeaversEnabled,
            int _aiForLeaversThreshold,
            const bool chatMuted = false,
            const bool enableBehaviourTracking = true);

 const wstring&     GetPlayerName() const;

  void              AttachHero(PFBaseHero* pHero);
  void              DetachHero(); 
  PFBaseHero*       GetHero() { return pHero; }
  PFBaseHero const* GetHero() const { return pHero; }

  int const         GetPlayerID() const { return playerID; }
  NCore::ETeam::Enum GetTeamID() const { return teamID; }
  NCore::ETeam::Enum GetOriginalTeamID() const { return originalTeamID; }
  int const         GetUserID() const { return userID; }
  void              SetUserID(int id) { userID = id; }

  NCore::ESex::Enum GetZZimaSex() const { return zzimaSex; }

  bool const        IsBot() const { return userID == -1; }

  bool const        IsLocal() const { return isLocal; }
  void              SetIsLocal(bool isLocal) { this->isLocal = isLocal; }

  bool const        IsPlaying() const { return isPlaying; }
  void              SetIsPlaying(bool _isPlaying);

  bool const        IsActive() const { return isActive; }
  void              SetIsActive(bool _isActive) { isActive = _isActive; }

  void              SetTeamID( NCore::ETeam::Enum _teamID ) { teamID = _teamID; }
  void              SetOriginalTeamID( NCore::ETeam::Enum _originalTeamID ) { originalTeamID = _originalTeamID; }

  void              SetDisconnected(const bool _disconnected, const bool _leaver);
  bool const        IsDisconnected() const { return disconnected; }
  bool const        IsLeaver() const { return leaver; }
  timer::Time const GetTimeElapsedSinceDisconnection() const;

  bool              IsChatMuted() const { return chatMuted; }

  virtual bool      Step(float dtInSeconds);

  const CObj<PlayerBehaviourTracker>& GetBehaviourTracker() const { return behaviourTracker; }

protected:
  virtual void      OnDestroyContents();

};


NDb::EFaction TeamIdToFaction( NCore::ETeam::Enum teamId );
NDb::EFaction GetFaction(NWorld::PFPlayer const* pPlayer); 
NDb::EFaction GetOriginalFaction(NWorld::PFPlayer const* pPlayer); 

}
