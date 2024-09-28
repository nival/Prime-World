#include "stdafx.h"
#include "Minigames.h"

#include "MinigamesMain.h"

#include "Clinic.h"

#include "EaselMinigame.h"


#include "MinigameCommands.h"
#include "../Client/ScreenCommands.h"

#include "../PF_GameLogic/PFMinigamePlace.h"


namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Minigames::Minigames( NWorld::PFWorld * _pWorld ) :
MinigamesBase( _pWorld ),
fadeTime( 0.5f ),
currentFadeTime( 0.f ),
doFade( false ),
fadeIn( true ),
fadeEnabled( true )
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Minigames::~Minigames()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Minigames::InitGames()
{
  //@iA@TODO: Может быть, создавать объекты миниигр тоже через NDb-фабрику?

  //CObj<Clinic> clinic = new Clinic();
  //if( clinic->Init( this, GetNativeMain()->GetScene() ) )
  //  RegisterMinigame( clinic.GetPtr(), "Clinic" );

  CObj<EaselMinigame> easel = new EaselMinigame( GetWorld(), IsLocal() );
  if( easel->InitMinigames( this, GetNativeMain()->GetScene() ) )
    RegisterMinigame( easel.GetPtr(), "Easel" );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Minigames::StartMinigame( NWorld::PFMinigamePlace * place )
{
  if ( MinigamesBase::StartMinigame( place ) )
  {
    currentFadeTime = 0.f;
    fadeIn = true;

    // [[@Irakly <neko.lich> Archangelsky@]] TODO: "Временный хак, оставляющий стол из сессии в миниигре для миниигры Easel. Надо реализовать механизм для всех объектов миниигр, освещаемых статикой"
    fadeEnabled = ( place->MinigameId() != "Easel" );
    doFade = fadeEnabled;

    return true;
  }

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Minigames::LeaveMinigame()
{
  MinigamesBase::LeaveMinigame();

  currentFadeTime = 0.f;
  fadeIn = false;

  // [[@Irakly <neko.lich> Archangelsky@]] TODO: "Временный хак, оставляющий стол из сессии в миниигре для миниигры Easel. Надо реализовать механизм для всех объектов миниигр, освещаемых статикой"
  doFade = fadeEnabled;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Minigames::UpdateM( float deltaTime )
{
  currentFadeTime += deltaTime;

  if ( currentFadeTime > fadeTime * 2.f && !fadeIn )
    doFade = false;

  MinigamesBase::UpdateM( deltaTime );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Minigames::SetPlacement( const Placement & _placement )
{
  placement = _placement;

  NI_ASSERT( IsValid( GetNativeMain() ), "" );

  NScene::IScene * scene = GetNativeMain()->GetScene();
  NScene::PlaceOnTerrain( scene->GetHeightsController(), placement.pos );

  MinigamesBase::SetPlacement( _placement );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Minigames::GetMinigamePlaceOpacity() const
{
  if (fadeIn)
    return 1.f - Clamp(currentFadeTime / fadeTime, 0.f, 1.f);
  else
    return Clamp(currentFadeTime / fadeTime, 0.f, 1.f);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Minigames::DoFade() const
{
  return doFade;
}

} // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( Minigames, PF_Minigames )
