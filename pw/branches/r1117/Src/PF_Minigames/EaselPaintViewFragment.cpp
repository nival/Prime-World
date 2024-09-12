#include "stdafx.h"
#include "EaselPaintViewFragment.h"

#include "DBEasel.h"

#include "../Scene/SceneObject.h"
#include "../Scene/SceneObjectUtils.h"

#include "Easel.h"
#include "EaselWorldClientConvertHelper.h"

#include "EaselPaintLayerSceneComponent.h"

#include "../Render/debugrenderer.h"
#include "../PF_Core/EffectsPool.h"


namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::OnDestroyContents()
{
  KillEffects();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselPaintViewFragment::Init(Easel& _easel, const CObj<NScene::EaselPaintSceneComponent>& _paint,
                                  CPaintFragment* fragment, const NDb::DBFragment* dbFragment)
{
  NI_VERIFY( IsValid( fragment ), "EaselPaintViewFragment: passed logic fragment is invalid", return false);
	NI_VERIFY( _paint , "EaselPaintViewFragment: paint is invalid", return false);

	easel = &_easel;
  logicFragment = fragment;
  scene = easel->GetScene();
  complete = false;
  paint = _paint;
  
  const NDb::Ptr<NDb::DBEaselCommon>& commonData = easel->GetData()->commonParams;

  if(!IsValid( commonData ) || (dbFragment == NULL))
  {
    return false;
  }

  const CPtr<EaselWorldClientConvertHelper>& _converter = easel->GetConvertHelper();

  fragmentColor = dbFragment->fragmentColor;
  colorCapacity = logicFragment->GetColorCapacity(fragmentColor);

  // fill color capacities
  int numPoints = logicFragment->GetNumPoints();
  NI_VERIFY( numPoints <= MAX_PAINT_POINTS_PER_FRAGMENT, "EaselPaintViewFragment: too much points in fragment", numPoints = MAX_PAINT_POINTS_PER_FRAGMENT);
  for(int i = 0; i < numPoints; ++i)
  {
    CPtr<CPainterPoint> _point = logicFragment->GetPoint( i );
    if ( IsValid( _point ) )
    {
      colorPointCapacity[i] = _point->GetCapacity();
      colorPointColor[i] = _point->GetColor();
      colorPointPos[i] = _converter->ConvertWorldToClientCoordinates(_point->GetCoord());      
    }    
  }

  // create placement
  Placement objPlacement = easel->GetPlacement();

  sceneObject = AutoPtr<NScene::SceneObject>(new NScene::SceneObject( scene ) );

  for(int i = 0; i < numPoints; ++i)
  {
    draftLayer[i] = new NScene::EaselPaintLayerSceneComponent( *paint, dbFragment->paintFragmentId, i, false );
    draftLayer[i]->SetId("draftlayer");
  }

  completeLayer = new NScene::EaselPaintLayerSceneComponent( *paint, dbFragment->paintFragmentId, 0, true);
  completeLayer->SetId("completelayer");

  completeEffectLayer = new NScene::EaselPaintLayerSceneComponent( _paint->GetGeometryName(), dbFragment->completeEffectMaterial, 1, _paint->GetPlacement());
  completeEffectLayer->SetId("completeeffectlayer");

  // set placement to all layers
  for(int i = 0; i < numPoints; ++i)
  {
    draftLayer[i]->ForceOpacity(0.0f);
    sceneObject->Add( draftLayer[i] );
  }

  completeLayer->ForceOpacity(0.0f);
  completeEffectLayer->ForceOpacity(0.0f);

  sceneObject->Add( completeLayer );
  sceneObject->Add( completeEffectLayer );

  sceneObject->UpdateForced();
  sceneObject->AddToScene( scene );

  sceneObject->SetPlacement( objPlacement );
  tmpAABB = sceneObject->GetWorldAABB();

  fIsInit = true;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::ShowFragment()
{
  if ( fIsInit == true && fIsHidden  )
  {
    EnableComponent("draftlayer",true);
    EnableComponent("completelayer",true);
    EnableComponent("completeeffectlayer",true);

    fIsHidden = false;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::HideFragment()
{
  if(fIsInit == true && fIsHidden == false)
  {
    EnableComponent("draftlayer",false);
    EnableComponent("completelayer",false);
    EnableComponent("completeeffectlayer",false);

    fIsHidden = true;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::AddDraftFadeWaitInterval(int _exceptThisOne, float _waitInterval)
{
  int numPoints = logicFragment->GetNumPoints();

  for( int i = 0; i < numPoints; ++i )
  {
    if(i == _exceptThisOne)
    {
      continue;
    }
    draftLayer[i]->AddFadeWaitInterval( _waitInterval );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::AddDraftFade(float _fade, float _duration)
{
  int numPoints = logicFragment->GetNumPoints();

  for( int i = 0; i < numPoints; ++i )
  {
    draftLayer[i]->AddFade( _fade,_duration );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::UpdatePointState(int point)
{
  int colorAmount = logicFragment->GetPointColorAmount(fragmentColor, point);

  if(colorPointAmount[point] == colorAmount)
  {
    return;
  }

  const NDb::PaintFragmentFillParams& paintFillParams = easel->GetData()->commonParams->effects.fillParams;

  colorPointAmount[point] = colorAmount;

  float colorChange = float(colorAmount)/colorPointCapacity[point];

  if(remainFillTime < paintFillParams.paintFillStartTime)
  {
    float waitInterval = paintFillParams.paintFillStartTime - remainFillTime;
    remainFillTime = paintFillParams.paintFillStartTime;
    AddDraftFadeWaitInterval(-1, waitInterval);
    completeLayer->AddFadeWaitInterval( waitInterval );
    completeEffectLayer->AddFadeWaitInterval( waitInterval );
  }

  AddDraftFadeWaitInterval(point, paintFillParams.fillInterval);
  draftLayer[point]->AddFade( colorChange, paintFillParams.fillInterval);
  completeLayer->AddFadeWaitInterval( paintFillParams.fillInterval );
  completeEffectLayer->AddFadeWaitInterval( paintFillParams.fillInterval );
  remainFillTime += paintFillParams.fillInterval;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::UpdateState()
{

  NI_VERIFY( IsValid(easel), "EaselPaintViewFragment: something strange happened. easel is dead", return );

  if((colorCapacity == 0) || complete)
  {
    return;
  }

  const NDb::PaintFragmentFillParams& paintFillParams = easel->GetData()->commonParams->effects.fillParams;

  int colorAmount = logicFragment->GetColorAmount(fragmentColor);

  // check every point
  int numPoints = logicFragment->GetNumPoints();
  NI_VERIFY( numPoints <= MAX_PAINT_POINTS_PER_FRAGMENT, "EaselPaintViewFragment: too much points in fragment", numPoints = MAX_PAINT_POINTS_PER_FRAGMENT);
  for(int i = 0; i < numPoints; ++i)
  {
    UpdatePointState(i);
  }

  // handle fragment completion
  if(colorAmount == colorCapacity)
  {
    complete = true;

    // fade out draft layer after complete coloring
    AddDraftFadeWaitInterval(-1, paintFillParams.completeFadeIn );
    AddDraftFade( 0.0f, 0.0f);

    // fade in complete part after coloring
    completeLayer->AddFade( 1.0f, paintFillParams.completeFadeIn );

    // add fade effect after complete coloring
    completeEffectLayer->AddFade(1.0f, paintFillParams.completeEffectFadeIn);
    completeEffectLayer->AddFade(0.0f, paintFillParams.completeEffectFadeOut);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::Update(float deltaTime, bool gameOnPause)
{
	NI_VERIFY( IsValid(easel), "EaselPaintViewFragment: something strange happened. easel is dead", return );

	//SetPosition()
	MinigameClientObject::Update( deltaTime, gameOnPause );

  remainFillTime = max(0, remainFillTime - deltaTime);

  UpdateFragments();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::AddEffect( const NDb::BasicEffectStandalone* dbEffect, CObj<PF_Core::BasicEffectStandalone>& effect, CPainterPoint* _point )
{
  NI_ASSERT( IsValid( easel ), "" );

  if ( !effect )
  {
    NI_ASSERT( !effect, "" );

    effect = easel->GetClient().CreateStandaloneEffect( dbEffect, true );

    if ( effect )
      effect->AddToScene( scene );
  }

  if ( effect )
  {
    Placement basePlacement = easel->GetConvertHelper()->GetMinigamePlacement();

    basePlacement.pos 
      = easel->GetConvertHelper()->ConvertWorldToClientCoordinates( _point->GetCoord() );      

    effect->SetPosition( basePlacement );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::RemoveEffect( CObj<PF_Core::BasicEffectStandalone>& effect )
{
  if ( effect )
  {
    effect->Die();

    if ( IsValid( easel ) )
      easel->GetClient().ReleaseEffect( effect );

    effect = 0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::UpdateFragments() 
{ 
  int numPoints = logicFragment->GetNumPoints();

  const NDb::Ptr<NDb::DBEaselCommon>& commonParams = easel->GetData()->commonParams;

  bool isMagnetPreselected = false;

  for ( int i = 0; i <  numPoints; ++i )
  {
    CPtr<CPainterPoint> point = logicFragment->GetPoint( i );

    if ( point->GetMode() == EPainterPointMode::MagnetHighlight && point->HasRoom() )
    {
      AddEffect( commonParams->magnetEffects.magnetHighlight, magnetHighlight[i], point );

      if ( magnetHighlight[i] )
        NScene::ModifySceneComponentColors( *magnetHighlight[i]->GetSceneObject(), "recolor", commonParams->colors[ point->GetColor() ], Render::HDRColor() );
    }
    else
    {
      RemoveEffect( magnetHighlight[i] );
    }

    if ( point->GetMode() == EPainterPointMode::MagnetPreselect )
    {
      isMagnetPreselected = true;
      AddEffect( commonParams->magnetEffects.magnetPreselect, magnetPreselect, point );

      if ( magnetPreselect )
        NScene::ModifySceneComponentColors( *magnetPreselect->GetSceneObject(), "recolor", commonParams->colors[ point->GetColor() ], Render::HDRColor() );
    }
    else
    {
      RemoveEffect( magnetPreselect );
    }

    if ( point->GetMode() == EPainterPointMode::MagnetInstalled )
    {
      AddEffect( commonParams->magnetEffects.magnet, magnet[i], point );

      if ( magnet[i] )
        NScene::ModifySceneComponentColors( *magnet[i]->GetSceneObject(), "recolor", commonParams->colors[ point->GetColor() ], Render::HDRColor() );
    }
    else
    {
      RemoveEffect( magnet[i] );
    }
  }
  
  if ( !isMagnetPreselected )
    RemoveEffect( magnetPreselect );
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewFragment::KillEffects() 
{
  RemoveEffect( magnetPreselect );

  for ( int i = 0; i <  MAX_PAINT_POINTS_PER_FRAGMENT; ++i )
  {
    RemoveEffect( magnetHighlight[i] );
    RemoveEffect( magnet[i] );
  }
}

} // PF_Minigames

BASIC_REGISTER_CLASS( PF_Minigames::EaselPaintViewFragment );