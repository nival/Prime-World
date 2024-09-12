#include "stdafx.h"
#include "EaselWorld.h"

#include "DBEasel.h"

#include "Easel.h"
#include "LuxGameLogic.h"
#include "PaintLogic.h"
#include "LuxFallingBoard.h"

#include "EaselEventSounds.h"

#include "EaselStatistics.h"

namespace PF_Minigames
{

bool g_enableBackgroundMusic = true;
REGISTER_DEV_VAR("Easel_Background_Music_enable",g_enableBackgroundMusic,STORAGE_NONE);

NDebug::PerformanceDebugVar easelPerf_WorldStep( "World step", "EaselPerf", 0, 0.0f, true );

//////////////////////////////////////////////////////////////////////////
//
// class EaselWorld implementation
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
EaselWorld::EaselWorld( PF_Core::IWorld* _pWorld ) :
  PF_Core::WorldObjectBase( _pWorld, false ),
  nextID(0)
{

}

EaselWorld::~EaselWorld()
{

}

bool EaselWorld::Init(Easel& _easel)
{
  easel = &_easel;

  luxGameLogic = new LuxGameLogic( GetWorld() );
  paintGameLogic = new PaintLogic( GetWorld(), this );

  easelPriestess = CreatePriestessProxy();
  soundObserver = CreateSoundObserver();
  easelSound = CreateEaselSounds();

  easelPriestess->SetEaselPtr( easel );
  
  return true;
}

//////////////////////////////////////////////////////////////////////////
void EaselWorld::StartGame(int currentLevel, const CObj<EaselLevelStatistics> _levelStatistics, NWorld::PFEaselPlayer* player )
{
  NI_VERIFY( IsValid(easel), "EaselWorld: easel is already dead or null", return );
  NI_VERIFY( IsValid(_levelStatistics), "EaselWorld: level statistics is uninitialized", return )
  NI_VERIFY(IsValid(easelPriestess),"EaselWorld object is corrupt (easel priestess)", return );

  levelStatistics = _levelStatistics;

  StartLuxGameLogic( player );
  paintGameLogic->InitLogic( easel, easel->GetNotifier() );
  StartSoundLogic();
  StartStatistics();

  easelPriestess->SetMinigameLevel(currentLevel);
}

//////////////////////////////////////////////////////////////////////////
void EaselWorld::StopGame()
{
  easelPriestess->ApplyDelayedGold();    // applying delayed money ...

  GetLogic()->GetFallingBoard()->ResetFallingObjects();

  StopSoundLogic();
  paintGameLogic->UninitLogic();
}
//////////////////////////////////////////////////////////////////////////
void EaselWorld::StartLuxGameLogic( NWorld::PFEaselPlayer* player )
{
  // creating game level
  luxGameLogic->InitGame(easel,
                                   easel->GetNotifier(),
                                   paintGameLogic,
                                   easelPriestess, player );
  
  // starting game level
  luxGameLogic->StartGame();
}


//////////////////////////////////////////////////////////////////////////
void EaselWorld::StartSoundLogic()
{
  if ( !IsValid( soundObserver) || !IsValid( easelSound ) )
    return;

    // sound observer initialization
  soundObserver->Init(*(easel.GetPtr()));

  // sound logic initialization
  int iRes = easelSound->InitSounds( easel->GetData()->soundData );
  if(iRes != LUX_OK)
    return;

  // setting paint observer pointer and start to observation
  soundObserver->SetEaselSoundsPtr( easelSound );
  soundObserver->StartObserving();

  return;
}

//////////////////////////////////////////////////////////////////////////
bool EaselWorld::StopSoundLogic()
{
  if ( IsValid( soundObserver ) )
    soundObserver->StopObserving();

  if ( IsValid( easelSound ) )
  easelSound->UninitSounds();

  return true;
}

bool EaselWorld::StartStatistics()
{
  levelStatistics->InitStats( easel, easelPriestess, paintGameLogic );

  return true;
}

//////////////////////////////////////////////////////////////////////////
void EaselWorld::UpdateInputMove(SVector _mousePos)
{
  #pragma REMINDER( "TODO: убрать магические числа" )

  _mousePos *= 10;

  luxGameLogic->UpdateInputMove(_mousePos);
}

//////////////////////////////////////////////////////////////////////////
void EaselWorld::StepM(const EaselStepInfo& info)
{
  NDebug::PerformanceDebugVarGuard perf(easelPerf_WorldStep, false);

  #pragma REMINDER( "TODO: убрать магические числа" )

  SEaselMouseInput mouseInput;

  mouseInput.xCoord = info.inputState.mousePos.x * 10;
  mouseInput.yCoord = info.inputState.mousePos.y * 10;
  mouseInput.leftBtnClicked = info.inputState.mouseLeftButton;
  mouseInput.rightBtnClicked = info.inputState.mouseRightButton;

  luxGameLogic->ProcessStep( info.deltaTime, mouseInput );
  paintGameLogic->ProcessStep( info.deltaTime, luxGameLogic );
  levelStatistics->ProcessStep( info.deltaTime );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselWorld::ProcessKeyboardEvent( EEaselKeyboardEvents::Enum event )
{
  return luxGameLogic ? luxGameLogic->ProcessKeyboardEvent( event ) : false;
}


//////////////////////////////////////////////////////////////////////////
//
// class EaselWorldLocal implementation
//
//////////////////////////////////////////////////////////////////////////
EaselWorldLocal::EaselWorldLocal( PF_Core::IWorld* _pWorld ) : EaselWorld( _pWorld )
{

}

EaselWorldLocal::~EaselWorldLocal()
{

}

EaselPriestess* EaselWorldLocal::CreatePriestessProxy()
{
  return new EaselPriestessLocal( PF_Core::WorldObjectBase::GetWorld() );
}

SoundObserver* EaselWorldLocal::CreateSoundObserver()
{
  return new SoundObserver();
}

IEaselSounds* EaselWorldLocal::CreateEaselSounds()
{
  return new EaselEventSounds();
}

//////////////////////////////////////////////////////////////////////////
//
// class EaselWorldRemote implementation
//
//////////////////////////////////////////////////////////////////////////
EaselWorldRemote::EaselWorldRemote( PF_Core::IWorld* _pWorld, IRemoteToLocalLink * localLink ) :
EaselWorld( _pWorld ),
localLink( localLink )
{

}

EaselWorldRemote::~EaselWorldRemote()
{

}

EaselPriestess* EaselWorldRemote::CreatePriestessProxy()
{
  EaselPriestessRemote * proxy = new EaselPriestessRemote(  PF_Core::WorldObjectBase::GetWorld(), localLink );
  return proxy;
}

SoundObserver* EaselWorldRemote::CreateSoundObserver()
{
  return new NullSoundObserver();
}

IEaselSounds* EaselWorldRemote::CreateEaselSounds()
{
  return new EaselEventNullSounds();
}

} // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( EaselWorld, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselWorldLocal, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselWorldRemote, PF_Minigames )
