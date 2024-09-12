#ifndef EASELCOMMANDS_H_INCLUDED
#define EASELCOMMANDS_H_INCLUDED

#include "EaselMinigame.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCore
{
	class WorldCommand;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
  enum EBoostType;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

_interface IWorldSessionInterface;
class MinigamesMain;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHIPPING
NCore::WorldCommand* CreateEaselCheatDropCooldowns( IWorldSessionInterface* _sessionInterface );
NCore::WorldCommand* CreateEaselCheatWinGame( IWorldSessionInterface* _sessionInterface );
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselCommandsSender : public CObjectBase 
{
  OBJECT_METHODS(0x9D6BBC00,EaselCommandsSender);

public:
  EaselCommandsSender();
  ~EaselCommandsSender();

  const CPtr<IWorldSessionInterface> GetWorldSessionInterface() const { return session; };
  
  void Init( EaselMinigame * _minigame );

  void PushNextCommand();

  // Common commands
  void SendLeaveMinigameCommand();
  void SendPauseMinigameCommand( bool enablePause );

  // Easel commands  
  void SendBoostFiredCommand( NDb::EBoostType _type );
  void SendRemoteUpdateCommand( uint _stepCounter, short _inputX, short _inputY, bool _mouseLeft, bool _mouseRight );
  void SendLevelStartCommand( int _levelID, int _paintID, int _randomSeed );
  void SendLevelStopCommand();
  void SendRegenerateBoostsCommand( int _levelID, int _randomSeed, bool _needToPay );
  void SendKeyboardEventCommand( EEaselKeyboardEvents::Enum event );
  void SendTransferItemCommand( NWorld::PFBaseHero * target, int transactionId );

private:

  typedef nstl::list< CObj<NCore::WorldCommand> > CommandStack;

  CommandStack commandStack;

  CPtr<MinigamesMain>  minigameMain;
  CPtr<IWorldSessionInterface>   session;
  CPtr<EaselMinigame> minigameClient;

  uint currentStepID;
};


} //namespace PF_Minigames

#endif //EASELCOMMANDS_H_INCLUDED
