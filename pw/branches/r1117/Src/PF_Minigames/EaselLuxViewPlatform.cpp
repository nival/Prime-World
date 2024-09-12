#include "stdafx.h"
#include "MinigameSessionInterface.h"

#include "Easel.h"
#include "EaselLuxViewPlatform.h"
#include "EaselWorldClientConvertHelper.h"

#include "EaselView.h"
#include "EaselViewEffects.h"

#include "../Render/debugrenderer.h"
#include "../Scene/SceneObject.h"
#include "../Scene/SceneObjectUtils.h"
#include "../Scene/AnimatedPlacement.h"

#include "../PF_Core/EffectsPool.h"
#include "../PF_Core/LightningEffect.h"

//Minimap interoperation
//#include "../PF_GameLogic/MinimapControl.h"
#include "../Scene/Camera.h"
#include "../UI/Resolution.h"

#include "../PF_GameLogic/AdventureScreen.h"
#include "../PF_GameLogic/Minimap.h"

namespace
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PlatformPositionGeneratorA : public PF_Core::PositionGenerator
{
  PlatformPositionGeneratorA( PF_Minigames::EaselLuxViewPlatform* _platform ) : platform(_platform) {}

  virtual bool GetPos(CVec3 &pos_) const { platform->GetLaserPointA( pos_ ); return true; }

protected:
  CPtr<PF_Minigames::EaselLuxViewPlatform> platform;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PlatformPositionGeneratorB : public PF_Core::PositionGenerator
{
  PlatformPositionGeneratorB( PF_Minigames::EaselLuxViewPlatform* _platform ) : platform(_platform) {}

  virtual bool GetPos(CVec3 &pos_) const { platform->GetLaserPointB( pos_ ); return true; }

protected:
  CPtr<PF_Minigames::EaselLuxViewPlatform> platform;
};

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselLuxViewPlatform::EaselLuxViewPlatform() :
  showPointer( false )
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxViewPlatform::OnDestroyContents()
{
  HideLaserEffects();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselLuxViewPlatform::InitPlatform( Easel& _easel, LuxPlatform* _platform )
{
	easel = &_easel;
  platform = _platform;

	// load from db
  const NDb::Ptr<NDb::DBEaselCommon>& commonParams = easel->GetData()->commonParams;
  
  Placement objPlacement = easel->GetPlacement();

  // initializing lerp object 
  lerpPlatformPos = new LuxViewPlatformLerp(platform,easel->GetConvertHelper());

  bool paletteBidon = _easel.GetWorldSessionInterface()->GetCurrentBidon() == NDb::BIDONTYPE_PALETTE;
  showPointer = _easel.GetWorldSessionInterface()->GetCurrentBidon() == NDb::BIDONTYPE_MAGICPOINTER;

  NDb::Ptr<NDb::DBSceneObject> dbSceneObject = paletteBidon ? 
                                    commonParams->platform.triplePlatformObject :
                                    commonParams->platform.platformObject;

  MinigameClientObject::Init(NULL, _easel.GetScene(), dbSceneObject, objPlacement, false);

  return sceneObject;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxViewPlatform::InitLaserEffect( CObj<PF_Core::LightningEffect>& laser, const NDb::LightningEffect* dbEffect )
{
  if ( !laser )
  {
    if ( IsValid( easel ) )
      laser = easel->GetClient().CreateLightningEffect( dbEffect, true );

    if ( laser )
    {
      laser->SetPositionGeneratorBegin( new PlatformPositionGeneratorA( this ) );
      laser->SetPositionGeneratorEnd( new PlatformPositionGeneratorB( this ) );
      laser->AddToScene( scene );
    }
  }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxViewPlatform::ShowLaserEffects()
{
  if ( showPointer )
  {
    const NDb::Ptr<NDb::DBEaselCommon>& commonParams = easel->GetData()->commonParams;
 
    if ( !targetEffect )
    {
      if ( IsValid( easel ) )
        targetEffect = easel->GetClient().CreateStandaloneEffect( commonParams->platform.laserPointer, true );

      if ( targetEffect )
        targetEffect->AddToScene( scene );
    }

    InitLaserEffect( laserEffect1, commonParams->platform.laser );
    InitLaserEffect( laserEffect2, commonParams->platform.laser2 );

    if ( !sourceEffect )
    {
      if ( IsValid( easel ) )
        sourceEffect = easel->GetClient().CreateAttachedEffect( commonParams->platform.laserSource, true );

      if ( sourceEffect )
        sourceEffect->Attach( Get( sceneObject ) );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxViewPlatform::HideLaserEffects()
{
  if ( showPointer )
  {
    if ( targetEffect )
    {
      if ( IsValid( easel ) )
        easel->GetClient().ReleaseEffect( targetEffect );
      targetEffect = 0;
    }

    if ( laserEffect1 )
    {
      if ( IsValid( easel ) )
        easel->GetClient().ReleaseEffect( laserEffect1 );
      laserEffect1 = 0;
    }

    if ( laserEffect2 )
    {
      if ( IsValid( easel ) )
        easel->GetClient().ReleaseEffect( laserEffect2 );
      laserEffect2 = 0;
    }

    if ( sourceEffect )
    {
      if ( IsValid( easel ) )
        easel->GetClient().ReleaseEffect( sourceEffect );
      sourceEffect = 0;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselLuxViewPlatform::GetLaserPointA( CVec3& _pos ) const
{
  const NScene::Locator* locator = sceneObject->FindLocator( "Laser" );

  if ( !locator )
    return false;

  locator->CalculateWorldPosition( _pos );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselLuxViewPlatform::GetLaserPointB( CVec3& _pos ) const
{
  if ( !targetEffect )
    return false;

  const NScene::Locator* locator = targetEffect->GetSceneObject()->FindLocator( "Target" );

  if ( !locator )
    return false;

  locator->CalculateWorldPosition( _pos );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxViewPlatform::Update(float deltaTime, bool gameOnPause)
{
	NI_VERIFY( IsValid(easel), "EaselLuxViewPlatform: something strange happened. easel is dead", return );

	// need to increment delta timer
  lerpPlatformPos->IncrementElapsedTime(deltaTime);

  // calculating platform position based on interpolated data ...
  Placement newPlacement;
  if(!lerpPlatformPos->vLerp(newPlacement))  // object is not visible at all
  {
    SetVisible(false);
  }
  else
  {
    SetVisible(true);
    SetPosition( newPlacement.pos );

    //Update minimap:
    SHMatrix projViewMtx = scene->GetCamera()->GetProjectiveMatrix() * scene->GetCamera()->GetViewMatrix();
    UI::Rect bounds;
    UI::GetWindowPlacement( &bounds, sceneObject->GetWorldAABB(), projViewMtx );
  }

  if ( showPointer && IsValid( platform ) && IsValid( platform->GetBulletBall() ) )
  {
    if ( platform->HasCollision() )
    {
      ShowLaserEffects();

      CVec3 pos = easel->GetConvertHelper()->ConvertWorldToClientCoordinates( platform->GetCollisionPoint(), EaselConst::Get_BALL_DEF_RADIUS() );

      if ( targetEffect )
      {
        Placement placement = newPlacement;
        placement.pos = pos;
        targetEffect->SetPosition( placement );
      }

      Render::HDRColor color = easel->GetData()->commonParams->colors[ platform->GetBulletBall()->Color() ];

      NScene::ModifySceneComponentColors( *targetEffect->GetSceneObject(), "recolor", color, Render::HDRColor() );
      NScene::ModifySceneComponentColors( *Get( sceneObject ), "recolor", color, Render::HDRColor() );

      if ( laserEffect1 )
        laserEffect1->ModifyColor( color, Render::HDRColor() );
    }
    else
    {
      HideLaserEffects();
    }
  }

  bool showAim = false;

  if ( IsValid( platform ) && IsValid( platform->GetBulletBall() ) )
  {
    if ( platform->HasCollision() && platform->GetBulletBall()->Type() == EBallType::PainBlast )
    {
      CVec3 pos = easel->GetConvertHelper()->ConvertWorldToClientCoordinates( platform->GetCollisionPoint(), EaselConst::Get_BALL_DEF_RADIUS() );

      Placement placement = newPlacement;
      placement.pos = pos;

      easel->GetView()->GetEffects()->ShowPaintBlastCursor( placement );

      showAim = true;
    }
  }

  if ( !showAim )
    easel->GetView()->GetEffects()->HidePaintBlastCursor();

  MinigameClientObject::Update( deltaTime,gameOnPause );
}

} // PF_Minigames

BASIC_REGISTER_CLASS( PF_Minigames::EaselLuxViewPlatform );