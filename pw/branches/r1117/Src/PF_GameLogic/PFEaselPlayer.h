#pragma once

#include "PFHero.h"
#include "../PF_Minigames/MinigameSessionInterface.h"


namespace NGameX
{
  _interface INaftaInfoProvider;
}

namespace NWorld
{

class PFBaseMaleHero;
class PFMinigamePlace;

class PFEaselPlayer : public PFBaseHero, public PF_Minigames::IWorldSessionInterface
{
  WORLD_OBJECT_METHODS( 0x8B77F380, PFEaselPlayer );

protected:

  ZDATA_(PFBaseHero)
  ZNOPARENT(PF_Minigames::IWorldSessionInterface)

  CObj<PF_Minigames::IMinigames> minigames;

  NDb::EBidonType bidon;
  CPtr<PFMinigamePlace> minigamePlace;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseHero*)this); f.Add(2,&minigames); f.Add(3,&bidon); f.Add(4,&minigamePlace); return 0; }

  PFEaselPlayer(PFWorld* pWorld, const SpawnInfo &info, NDb::EUnitType unitType, NDb::EFaction faction, NDb::EFaction _originalFaction);
  virtual ~PFEaselPlayer() {};

  void ForceLeaveMinigame();

  virtual void                OnDestroyContents();
  virtual bool                Step(float dtInSeconds);
  virtual void                OnGameFinished( const NDb::EFaction failedFaction );
  virtual void                OnBeforeClose();
  virtual void                DropCooldowns( DropCooldownParams const& dropCooldownParams );

  void                        Isolate( bool isolate );
  bool                        StartMinigame( PFMinigamePlace * pPlace );

  // IWorldSessionInterface
  virtual PF_Minigames::IMinigames* GetMinigames() { return minigames; }
  virtual int                 GetPriestessID() const { return GetObjectId(); }
  virtual int                 GetPriestessUserId() const { return GetPlayerId(); }
  virtual NWorld::PFWorld *   GetSessionWorld() { return GetWorld(); }
  virtual bool                OnLeaveMinigameCmd();
  virtual int                 GetPriestessLevel() const { return GetNaftaLevel(); }
  virtual void                SetNaftaInfoProvider(NGameX::INaftaInfoProvider * naftaInfoProvider);
  virtual int                 GetGold() const { return PFBaseHero::GetGold(); }
  virtual void                AddGold( int _toAdd ) { return PFBaseHero::AddGold( _toAdd ); }
  virtual void                TakeGold( int _value ) { PFBaseHero::TakeGold( _value ); }
  virtual bool                CanBuyZZBoost();
  virtual void                BuyZZBoost();
  
  //minigame logging
  virtual void                LogMinigameEvent( SessionEventType::EventType eventType, int param1, int param2);
  
  virtual int                 GetTotalNaftaEarned() const { return PFBaseHero::GetTotalNaftaEarned(); }

  virtual PFMinigamePlace *   GetMinigamePlace() const {return minigamePlace;}

  virtual void                GetItemTransferTargets( vector<CPtr<PFBaseHero>> & targets );
  virtual bool                CanGetScrollDuplicate( PFBaseHero * target );
  virtual bool                AddItemToHero( PFBaseHero * target, const NDb::Consumable * pDBDesc, int quantity );

  virtual NDb::EBidonType     GetCurrentBidon() const { return bidon; }
  virtual void                SetCurrentBidon( NDb::EBidonType _bidon );

  virtual void                OnMapLoaded();

  virtual void                MinigameEvent( NDb::EBaseUnitEvent eventType);

protected:
  PFEaselPlayer() {}

  virtual void OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc = 0);
};

} // namespace NWorld
