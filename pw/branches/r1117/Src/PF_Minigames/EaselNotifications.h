#pragma once
#include "../PF_Core/WorldObject.h"
#include "../System/UpdateProcessor.h"
#include "../System/Updater.h"


namespace PF_Minigames
{

_interface IEaselNotifier : public IObjectBase
{
  typedef CObjectBase tNotification;
  typedef Updater::CUpdateProcessor tObserver;

  virtual bool Notify( tNotification& notification ) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// easel luxor logic, paint logic and view interact with each other through the instance of this class
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselNotifier : public IEaselNotifier, public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9D6BBB02, EaselNotifier );
private:
  EaselNotifier() {}
public:
	EaselNotifier( PF_Core::IWorld* _pWorld  );

	void Register( tObserver& observer );
  void Register(int _typeID, Updater::IUpdateProcessorFunc *_pFunc);
  
	// return false if notification isn't valid
	virtual bool Notify( tNotification& notification );

  Updater::CUpdater updater;
};

}
