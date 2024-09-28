#include "stdafx.h"
#include "EaselViewEffects.h"

#include "../System/RandomGen.h"
#include "../Scene/SceneObjectUtils.h"
#include "../PF_Core/EffectsPool.h"

#include "Easel.h"
#include "PF_GameLogic/DBMinigamesTypes.h"
#include "EaselTrajectory.h"
#include "LuxPath.h"
#include "EaselClient.h"
#include "LuxBall.h"
#include "LuxBallExplodedNotification.h"
#include "LuxSorterBoostFiredNotification.h"
#include "PaintFlyingNotification.h"
#include "LuxAlchemistBoostsNotifications.h"
#include "EaselViewAlchemistPot.h"

#include "EaselWorldClientConvertHelper.h"

#include "LuxFallingObject.h"

#include "EaselConstants.h"

#include "LuxBoost.h"
#include "LuxGameBoard.h"
#include "LuxGameLogic.h"
#include "BoostBoard.h"
#include "EaselWorld.h"
#include "EaselSoundsInterface.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SetEffectDestination( NScene::SceneObject& sceneObject, const CVec3& to, float maxLength )
{
  //// setting traverser
  struct PlacementSetter : public NScene::TraverserById
  {
    Placement newPlacement;

    PlacementSetter (const char *id, const Placement& _newPlacement)
      : TraverserById(id)
      , newPlacement(_newPlacement) 
    {
    }

    void operator()(NScene::SceneComponent *pSC)
    {
      pSC->SetBase(newPlacement.pos, newPlacement.rot, newPlacement.scale);
    }
  };

  Placement placement = sceneObject.GetPosition();

  float effectLength = (placement.pos - to).Length();

  // throw out singular cases
  if ( effectLength < FP_EPSILON )
    return false;

  SHMatrix matrix;
  SetLookAtZ( &matrix, placement.pos, to );
  placement.rot.FromEulerMatrix( matrix );

  placement.scale = CVec3( effectLength / maxLength, effectLength / maxLength, effectLength / maxLength );
 
  CVec3 eulDecomp;
  placement.rot.DecompEulerAngles(&eulDecomp.x, &eulDecomp.y, &eulDecomp.z);
  eulDecomp += CVec3(FP_PI, FP_PI, FP_PI2);
  placement.rot.FromEulerAngles(eulDecomp.x, eulDecomp.y, eulDecomp.z);

  sceneObject.SetPlacement(placement);

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselViewEffects::EaselViewEffects()
: lastExplosionRotationAngle(0)
{
}


void EaselViewEffects::ShowPaintBlastCursor( const Placement& placement )
{
  if ( !IsValid( paintblastCursorEffect ) )
  {
    const NDb::Ptr<NDb::DBEaselCommon>& commonEaselData = easel->GetData()->commonParams;
    NDb::Ptr<NDb::BasicEffectStandalone> cursorDB = commonEaselData->aimCursors.cursors[NDb::CURSOR_PAINTBLAST];

    if ( !IsValid( cursorDB ) )
      return;

    paintblastCursorEffect = easel->GetClient().CreateStandaloneEffect( cursorDB, true );
  }

  if ( IsValid( paintblastCursorEffect ) ) 
  {
    if ( !paintblastCursorEffect->GetSceneObject()->IsInScene() )
      paintblastCursorEffect->AddToScene( easel->GetScene() );

    paintblastCursorEffect->SetPosition( placement );
  }
}

void EaselViewEffects::HidePaintBlastCursor()
{
  if ( IsValid( paintblastCursorEffect ) ) 
  {
    paintblastCursorEffect->GetSceneObject()->RemoveFromScene();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::ClearFreeze( bool brute )
{
  if ( freezeEffect )
  {
    freezeEffect->Die();

    if ( IsValid( easel ) )
      easel->GetClient().ReleaseEffect( freezeEffect );

    freezeEffect = 0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::DBEaselFlowEffectGroup* EaselViewEffects::GetDBFlowEffectGroup(float distance) const
{
  const NDb::Ptr<NDb::DBEaselCommon>& commonData = easel->GetData()->commonParams;

  NI_VERIFY(IsValid( commonData ), "common easel data is invalid", return NULL );


  // check if there is no need for flow effect
  if(distance < commonData->effects.flowIntervalsStartDistance)
  {
    return NULL;
  }

  const nstl::vector<NDb::DBEaselFlowEffectGroup>& flowGroups = commonData->effects.flowGroups;

  const NDb::DBEaselFlowEffectGroup* group = NULL;

  // search for suitable group 
  int flowGroupsNum = flowGroups.size();
  for(int i = 0; i < flowGroupsNum; ++i)
  {
    group = &flowGroups[i];
    if( distance < flowGroups[i].intervalEndDistance )
    {
      break;
    }
  }

  return group;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::Init(Easel& _easel)
{
  easel = &_easel;
  (easel->GetNotifier())->Register(*this);
  SubscribeUpdates();

  Reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::Reset()
{
  alchemistPot = 0;

  if ( IsValid( paintblastCursorEffect ) )
    easel->GetClient().ReleaseEffect( paintblastCursorEffect, true );
  paintblastCursorEffect = 0;

  if ( startMovie && IsValid( easel ) )
    easel->GetClient().ReleaseEffect( startMovie, true );
  startMovie = 0;

  if ( endMovie && IsValid( easel ) )
    easel->GetClient().ReleaseEffect( endMovie, true );
  endMovie = 0;

  ClearFreeze( true );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::SubscribeUpdates()
{
  Subscribe( &EaselViewEffects::BallExplosionHandler );
  Subscribe( &EaselViewEffects::PaintFlyHandler );
  Subscribe( &EaselViewEffects::PaintFlyInPointHandler );
  Subscribe( &EaselViewEffects::SorterBoostFiredNotification );
  Subscribe( &EaselViewEffects::AlchemistIncomingFlowHandler );
  Subscribe( &EaselViewEffects::AlchemistOutgoinFlowHandler );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::Update( float deltaTime, LuxGameLogic* _gameLogic )
{
  UpdateStartMovie( _gameLogic );
  UpdateEndMovie( _gameLogic );

  CheckAlchemist( _gameLogic );

 if ( alchemistPot )
   alchemistPot->Update( deltaTime, false );

}

void EaselViewEffects::UpdateStartMovie( LuxGameLogic* _gameLogic )
{
  if ( !IsValid( _gameLogic->GetBoostBoard() ) )
    return;

  LuxBoardState state = _gameLogic->GetGameBoard()->GetBoardState();

  if ( state == BOARDSTATE_LEVEL_BEGIN && !IsValid( startMovie ) )
  {
    CreateStartMovie();
    easel->GetWorld()->GetSound()->PlaySound(NDb::EASELSOUNDTYPE_LEVEL_SCROLL_START);
  }

  if ( state != BOARDSTATE_LEVEL_BEGIN && IsValid( startMovie ) )
  {
    ReleaseStartMovie();
    easel->GetWorld()->GetSound()->StopSound(NDb::EASELSOUNDTYPE_LEVEL_SCROLL_START);
  }
}

void EaselViewEffects::UpdateEndMovie( LuxGameLogic* _gameLogic )
{
  if ( !IsValid( _gameLogic->GetBoostBoard() ) )
    return;

  LuxBoardState state = _gameLogic->GetGameBoard()->GetBoardState();

  if ( state == BOARDSTATE_LEVEL_WON_MOVIE && !IsValid( endMovie ) )
  {
    easel->GetWorld()->GetSound()->PlaySound(NDb::EASELSOUNDTYPE_LEVEL_SCROLL_END);
    CreateEndMovie();
  }

  if ( state != BOARDSTATE_LEVEL_WON_MOVIE && IsValid( endMovie ) )
  {
    ReleaseEndMovie();
    easel->GetWorld()->GetSound()->StopSound(NDb::EASELSOUNDTYPE_LEVEL_SCROLL_END);
  }
}


void EaselViewEffects::CheckAlchemist( LuxGameLogic* _gameLogic )
{
  if ( !IsValid( _gameLogic->GetBoostBoard() ) )
    return;

  CPtr<LuxBoost> boost = _gameLogic->GetBoostBoard()->GetBoost( NDb::BOOSTTYPE_ALCHEMIST );

  if ( !IsValid( boost ) )
  {
    alchemistPot = 0;
    return;
  }

  if ( boost->IsActive() && !IsValid( alchemistPot ) )
  {
    alchemistPot = new EaselViewAlchemistPot();

    NDb::Ptr<NDb::BasicEffectAttached> dbEffect = easel->GetData()->commonParams->alchemistPot;
    alchemistPot->InitPot( easel, dbEffect );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::BallExplosionHandler(const LuxBallExplodedNotification& notification)
{
  NI_VERIFY( IsValid(easel), "EaselViewEffects: something strange happened. easel is dead", return );
  NI_VERIFY( IsValid(notification.ball), "EaselViewEffects: invalid ball passed", return);

  // [@Pavel <GnoM> Cherniavski@] TODO: нужно сделать отдельный эффект взрыва джокера ...
  NDb::EColor color = notification.ball->Color();
  if(color == NDb::COLOR_ANY)
    return;

  SVector ballCoords = notification.ball->Position();
  if( ballCoords.x < 0 || ballCoords.y < 0)
  {
    return;
  }

  // get db record
  const NDb::DBEaselEffectView& effectsDb = easel->GetData()->commonParams->effects;

  // calculate effect position
  Placement effectPos = easel->GetPlacement();
  effectPos.pos = easel->GetConvertHelper()->ConvertWorldToClientCoordinates( ballCoords );

  // Create effect
  CObj<PF_Core::BasicEffectStandalone> effect = easel->GetClient().CreateStandaloneEffect( effectsDb.ballExplosion, false );

  if( !effect )
    return;

  NScene::ModifySceneObjectColors( *effect->GetSceneObject(), easel->GetData()->commonParams->colors[ color ], Render::HDRColor(0,0,0,0) );

  effect->SetPosition( effectPos );
  effect->AddToScene( easel->GetScene() );

  // add random scale and rotation to make explosions more unique

  float minRotation = ToRadian(effectsDb.explosionParams.minRotationAngle);
  NI_VERIFY(minRotation >= 0, "EaselViewEffects: minimal rotation for explosion effect is less than zero", minRotation = 0 );
  NI_VERIFY(minRotation <= FP_2PI, "EaselViewEffects: minimal rotation for explosion effect is greater than FP_2PI", minRotation = FP_2PI );

  float rotateAngle = minRotation;
  if(minRotation != FP_2PI)
  {
    rotateAngle = NRandom::Random(minRotation, FP_2PI);
  }

  rotateAngle += lastExplosionRotationAngle;
  if(rotateAngle > FP_2PI)
  {
    rotateAngle -= FP_2PI;
  }

  Placement placement = effect->GetSceneObject()->GetPosition();
  placement.rot.FromEulerAngles(rotateAngle, 0.0f, 0.0f);

  const CVec3& minScale = effectsDb.explosionParams.minScale;
  const CVec3& maxScale = effectsDb.explosionParams.maxScale;

  CVec3 scale;

  placement.scale.x *= NRandom::Random(minScale.x, maxScale.x);
  placement.scale.y *= NRandom::Random(minScale.y, maxScale.y);
  placement.scale.z *= NRandom::Random(minScale.z, maxScale.z);

  effect->SetPosition(placement);
  lastExplosionRotationAngle = rotateAngle;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::PaintFlyHandler(const PaintFlyingNotification& notification)
{
  NI_VERIFY( IsValid( notification.spTo ), "EaselViewEffects: notified ball is invalid", return );

  PaintFlyingInPointNotification flyInPointNotification;
  flyInPointNotification.from = notification.from;
  flyInPointNotification.to = notification.spTo->GetCoord();
  flyInPointNotification.paintColor = notification.spTo->GetColor();

  PaintFlyInPointHandler(flyInPointNotification);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::PaintFlyInPointHandler( const PaintFlyingInPointNotification& notification )
{
  NI_VERIFY( IsValid(easel), "EaselViewEffects: something strange happened. easel is dead", return );

  // calculate effect position and destination
  const CPtr<EaselWorldClientConvertHelper>& convertHelper = easel->GetConvertHelper();

  SVector fromWorld = notification.from;
  SVector toWorld = notification.to;

  if (
      fromWorld.x < -EaselConst::Get_LOGIC_FIELD_WIDTH() || fromWorld.x > EaselConst::Get_LOGIC_FIELD_WIDTH() || 
      fromWorld.y < -EaselConst::Get_LOGIC_FIELD_HEIGHT() || fromWorld.y > EaselConst::Get_LOGIC_FIELD_HEIGHT()
    )
  {
    // Не нужен тут ассерт NUM_TASK
    //NI_ALWAYS_ASSERT( NStr::StrFmt( "Paint flyed off the table: from (%d, %d) to (%d, %d)", fromWorld.x, fromWorld.y, toWorld.x, toWorld.y ) );
    return;
  }

  Placement from = easel->GetPlacement();
  from.pos = convertHelper->ConvertWorldToClientCoordinates( fromWorld );
  CVec3 to = convertHelper->ConvertWorldToClientCoordinates( toWorld );

  // get db record
  const NDb::DBEaselFlowEffectGroup* effectsGroup = GetDBFlowEffectGroup( (from.pos - to).Length() );

  if ( !effectsGroup )
    return;

  CObj<PF_Core::BasicEffectStandalone> touchEffect =
              easel->GetClient().CreateStandaloneEffect( easel->GetData()->commonParams->effects.flowTouchEffect, false );
  
  if ( !touchEffect )
    return;

  touchEffect->SetPosition( to );
  touchEffect->AddToScene( easel->GetScene() );
  ModifySceneObjectColors( *touchEffect->GetSceneObject(), easel->GetData()->commonParams->colors[ notification.paintColor ], Render::HDRColor(0,0,0,0) );


  CObj<PF_Core::BasicEffectStandalone> effect = easel->GetClient().CreateStandaloneEffect( effectsGroup->flowEffect, false );

  if ( !effect )
    return;

  effect->SetPosition( from );
  effect->AddToScene( easel->GetScene() );

  // Create effect
  NScene::SceneObject* object = effect->GetSceneObject();

  if ( !object )
    return;

  ModifySceneObjectColors( *object, easel->GetData()->commonParams->colors[ notification.paintColor ], Render::HDRColor(0,0,0,0) );
  SetEffectDestination( *object, to, easel->GetData()->commonParams->effects.flowScale );
}

void EaselViewEffects::OnPaintBlastBallExplosion( const SVector& worldCoords )
{
  NI_VERIFY( IsValid(easel), "EaselViewEffects: something strange happened. easel is dead", return );

  NDb::Ptr<NDb::BasicEffectStandalone> dbEffect = easel->GetData()->commonParams->effects.paintblastExplosion;

  Placement effectPos = easel->GetPlacement();
  effectPos.pos = easel->GetConvertHelper()->ConvertWorldToClientCoordinates( worldCoords );

  CObj<PF_Core::BasicEffectStandalone> effect = easel->GetClient().CreateStandaloneEffect( dbEffect, false );
  if( !effect )
    return;

  effect->SetPosition( effectPos );
  effect->AddToScene( easel->GetScene() );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::OnFreeze()
{
  ClearFreeze( true );

  NI_VERIFY( IsValid( easel ), "", return );

  NDb::Ptr<NDb::BasicEffectStandalone> dbEffect = easel->GetData()->commonParams->effects.freezeEffect;

  Placement effectPos = easel->GetPlacement();
  effectPos.pos = easel->GetConvertHelper()->ConvertWorldToClientCoordinates( SVector( EaselConst::Get_LOGIC_FIELD_WIDTH () / 2, EaselConst::Get_LOGIC_FIELD_HEIGHT() / 2 ) );

  freezeEffect = easel->GetClient().CreateStandaloneEffect( dbEffect, true );
  if( !freezeEffect )
    return;

  freezeEffect->SetPosition(effectPos);
  freezeEffect->AddToScene(easel->GetScene());
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::OnUnfreeze()
{
  ClearFreeze( false );
}


void EaselViewEffects::SorterBoostFiredNotification(const LuxSorterBoostFiredNotification& notification)
{
  NI_VERIFY( IsValid(easel), "EaselLuxEffects: something strange happened. easel is dead", return );

  NDb::Ptr<NDb::BasicEffectStandalone> dbEffect = easel->GetData()->commonParams->effects.sortEffect;

  Placement effectPos = easel->GetPlacement();
  effectPos.pos = easel->GetConvertHelper()->ConvertWorldToClientCoordinates(SVector(EaselConst::Get_LOGIC_FIELD_WIDTH()/2,EaselConst::Get_LOGIC_FIELD_HEIGHT()/2));

  CObj<PF_Core::BasicEffectStandalone> effect = easel->GetClient().CreateStandaloneEffect( dbEffect, false );
  if( !effect )
    return;

  effect->SetPosition(effectPos);
  effect->AddToScene(easel->GetScene());
}

void EaselViewEffects::CreateEndMovie()
{
  NI_VERIFY( IsValid(easel), "EaselLuxEffects: something strange happened. easel is dead", return );

  NDb::Ptr<NDb::BasicEffectStandalone> dbEffect = easel->GetData()->commonParams->effects.gameWonEffect;
  if(!IsValid(dbEffect) )
  {
    return;
  }

  Placement effectPos = easel->GetPlacement();
  effectPos.pos = easel->GetConvertHelper()->ConvertWorldToClientCoordinates(SVector(EaselConst::Get_LOGIC_FIELD_WIDTH()/2,EaselConst::Get_LOGIC_FIELD_HEIGHT()/2));

  CObj<PF_Core::BasicEffectStandalone> effect = easel->GetClient().CreateStandaloneEffect( dbEffect, true );
  if( !effect )
    return;

  effect->SetPosition(effectPos);
  effect->AddToScene(easel->GetScene());
  endMovie = effect;
  
  NScene::SceneObject* object = effect->GetSceneObject();
  if( !object )
    return;

  NDb::Ptr<NDb::Material> dbOverrideMaterial = easel->GetPainterLevelData()->paintMaterial;
  if(IsValid(dbOverrideMaterial))
  {
    // updating material
    struct MProc : public Render::IMaterialProcessor, public NonCopyable
    {
      NDb::Ptr<NDb::Material> dbNewMaterial;

      MProc(NDb::Ptr<NDb::Material> _material) : dbNewMaterial(_material)  {};
      virtual void operator()(Render::BaseMaterial &material)
      {
        if(material.GetSubPriority() == -2)
        {
          material.FillMaterial( dbNewMaterial.GetPtr(), 0 ); //TODO: Add correct texturePoolId
          material.SetPaintMaterialModePin( NDb::PAINTMATERIALMODEPIN_FINAL );
          material.SetSubPriority( -2 );
        }
      }
    } proc(dbOverrideMaterial);

    NScene::ForAllMaterials(*object, proc);
  }
  
}

void EaselViewEffects::ReleaseEndMovie()
{
  if( !endMovie )
    return;

  if ( IsValid( easel ) )
    easel->GetClient().ReleaseEffect( endMovie );

  endMovie->Die();
  endMovie = 0;
}

void EaselViewEffects::CreateStartMovie()
{
  NI_VERIFY( IsValid(easel), "EaselLuxEffects: something strange happened. easel is dead", return);

  NDb::Ptr<NDb::BasicEffectStandalone> dbEffect = easel->GetData()->commonParams->effects.gameStartEffect;
  if( !dbEffect )
    return;

  Placement effectPos = easel->GetPlacement();
  effectPos.pos = easel->GetConvertHelper()->ConvertWorldToClientCoordinates(SVector(EaselConst::Get_LOGIC_FIELD_WIDTH()/2,EaselConst::Get_LOGIC_FIELD_HEIGHT()/2));

  CObj<PF_Core::BasicEffectStandalone> effect = easel->GetClient().CreateStandaloneEffect( dbEffect, true );
  if( !effect )
    return;

  effect->SetPosition(effectPos);
  effect->AddToScene(easel->GetScene());
  startMovie = effect;
  
  NScene::SceneObject* object = effect->GetSceneObject();
  if(!object)
  {
    return;
  }

  NDb::Ptr<NDb::Material> dbOverrideMaterial = easel->GetPainterLevelData()->paintMaterial;
  
  if( IsValid( dbOverrideMaterial ) )
  {
    // updating material
    struct MProc : public Render::IMaterialProcessor, public NonCopyable
    {
      NDb::Ptr<NDb::Material> dbNewMaterial;

      MProc(NDb::Ptr<NDb::Material> _material) : dbNewMaterial(_material)  {};
      virtual void operator()(Render::BaseMaterial &material)
      {
        if ( material.GetSubPriority() == -2 )
        {
          material.FillMaterial( dbNewMaterial.GetPtr(), 0 ); //TODO: Add correct texturePoolId
          material.SetPaintMaterialModePin( NDb::PAINTMATERIALMODEPIN_EMPTY );
          material.SetSubPriority( -2 );
        }
      }
    } proc(dbOverrideMaterial);

     NScene::ForAllMaterials(*object, proc);
  }
}


void EaselViewEffects::ReleaseStartMovie()
{
  if( !startMovie )
    return;

  startMovie->Die();

  if ( IsValid( easel ) )
    easel->GetClient().ReleaseEffect( startMovie );

  startMovie = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::AlchemistIncomingFlowHandler( const LuxAlchemistIncomingFlowNotification & notification )
{
  if ( !alchemistPot )
    return;

  if ( !alchemistPot->VisualIsValid() )
    return; //Minigame place is under FOW

  EaselWorldClientConvertHelper * convertHelper = easel->GetConvertHelper();
  SVector potPosition = convertHelper->ConvertClientToWorldCoordinates( alchemistPot->PotPlacement().pos );

  PaintFlyingInPointNotification ntfy;
  ntfy.from = notification.fromPoint;
  ntfy.to = potPosition;
  ntfy.paintColor = notification.color;

  PaintFlyInPointHandler( ntfy );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewEffects::AlchemistOutgoinFlowHandler( const LuxAlchemistOutgoinFlowNotification & notification )
{
  if ( !alchemistPot )
    return;

  if ( !alchemistPot->VisualIsValid() )
    return; //Minigame place is under FOW

  EaselWorldClientConvertHelper * convertHelper = easel->GetConvertHelper();

  const Placement & potPlacement = alchemistPot->PotPlacement();
  SVector potPosition = convertHelper->ConvertClientToWorldCoordinates( potPlacement.pos );

  //We have nothing to do but redirect the notification
  PaintFlyingNotification * pRedirect = new PaintFlyingNotification;

  pRedirect->from = potPosition;
  pRedirect->spTo = notification.toPoint;
  
  if ( IsValid( easel->GetNotifier() )  )
    easel->GetNotifier()->Notify( *pRedirect );

  alchemistPot = 0;
}

} // PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::EaselViewEffects)
