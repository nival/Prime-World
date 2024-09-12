#pragma once

#include "Easel.h"

namespace PF_Minigames
{

_interface IRemoteToLocalLink;

//////////////////////////////////////////////////////////////////////////
//
// logic processor class, placed on remote client
//
//////////////////////////////////////////////////////////////////////////
class EaselRemote : public Easel
{
  OBJECT_METHODS( 0xF467F441, EaselRemote );
protected:
  EaselRemote() {}

public:
  EaselRemote( PF_Core::IWorld* _pWorld, IRemoteToLocalLink * localLink, bool _nullView );
  ~EaselRemote();

  virtual void StartLevel( int paintId, int levelID, int seed, NWorld::PFEaselPlayer * player );
  virtual void StopLevel();

  virtual void StepM( const EaselStepInfo& info );

  virtual bool ProcessMouseMove(const CVec2& _pos);
  virtual bool ProcessMouseEvent( EEaselMouseEvents::Enum _key );

  void SetLocalGame( Easel* _localGame ) { localGame = _localGame; }

  bool TransferItem( NWorld::PFBaseHero * target, int transactionId );

  // from WorldObject
  virtual void OnAfterReset();

private:
  CPtr<IRemoteToLocalLink> localLink;
  bool nullView;

  CPtr<Easel> localGame;

  // creation overloads
  virtual EaselWorld* CreateWorldObject();
  virtual EaselView* CreateViewObject( Easel* _easel );
};

} //namespace PF_Minigames
