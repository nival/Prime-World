#include "stdafx.h"

#include "EaselLuxViewPath.h"

#include "Easel.h"
#include "LuxPath.h"
#include "LuxGameLogic.h"
#include "LuxGameBoard.h"

#include "MinigameClientObject.h"
#include "EaselConstants.h"

#include "EaselTrajectory.h"
#include "EaselLuxStaticObject.h"
#include "EaselWorld.h"
#include "EaselSoundsInterface.h"

#include "EaselLuxViewBambooObject.h"
#include "EaselLuxViewWellObject.h"

#include "EaselWorldClientConvertHelper.h"
#include "../Scene/AnimatedPlacement.h"
#include "../PF_Core/BasicEffect.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// class EaselLuxViewPath implementation
//
//////////////////////////////////////////////////////////////////////////
EaselLuxViewPath::EaselLuxViewPath(const CPtr<Easel>& _easel, LuxPath* _path ) :
  easel(_easel),
  coveredPath(0),
  firstRun(true)
{
  pathConverter = new PathConverter( _easel );
  rollInConverter = new BambooRollInConverter();
  rollOutConverter = new WellRollOutConverter();
  coordsConverter = new SplineBallCoordsConverter(pathConverter,rollInConverter,rollOutConverter);

  path = _path;

  InitStartPos( _easel, _path );
  InitEndPos( _easel, _path );
}

EaselLuxViewPath::~EaselLuxViewPath()
{
  Uninit();
}


void EaselLuxViewPath::Uninit()
{
  CleanUp();
}

bool EaselLuxViewPath::InitStartPos(const CPtr<Easel>& _easel, LuxPath* _path)
{
  CObj<EaselLuxViewBambooObject> startPoint = new EaselLuxViewBambooObject();

  SVector pointCoords;
  _path->GetTrajectory()->GetCoordsByLenght(0,pointCoords);

  Placement placement = _easel->GetPlacement();
  placement.pos = _easel->GetConvertHelper()->ConvertWorldToClientCoordinates(pointCoords);
  
  NScene::AnimatedPlacement offset;
  offset.Init(_path->GetStartOffset(),0);

  // [@Irakly <neko.lich> Archangelsky@] TODO: заменить в данных, а не менять x и y через код
  Placement offsetPlacement = offset.GetPlacement();
  offsetPlacement.pos = CVec3(-offsetPlacement.pos.y, -offsetPlacement.pos.x, offsetPlacement.pos.z);
  placement += offsetPlacement;

  if ( startPoint->InitBambooObject(_easel,_easel->GetData()->commonParams->startPipe,placement)  )
  {
    rollInConverter->Init(startPoint->GetStartLocator(), startPoint->GetEndLocator(), placement);
     
    // registering object
    easel->GetClient().AddObject( startPoint, false );

    // adding object to container
    pathObjects.push_back(CPtr<MinigameClientObject>(startPoint));

    return true;
  }

  return false;
}

bool EaselLuxViewPath::InitEndPos(const CPtr<Easel>& _easel, LuxPath* _path)
{
  CObj<EaselLuxViewWellObject> endPoint = new EaselLuxViewWellObject();

  SVector pointCoords;
  int64 lenght = _path->GetTrajectory()->GetLenght();
  _path->GetTrajectory()->GetCoordsByLenght(lenght,pointCoords);

  Placement placement = _easel->GetPlacement();
  placement.pos = _easel->GetConvertHelper()->ConvertWorldToClientCoordinates(pointCoords);

  NScene::AnimatedPlacement offset;
  offset.Init(_path->GetEndOffset(),0);

  // [@Irakly <neko.lich> Archangelsky@] TODO: заменить в данных, а не менять x и y через код
  Placement offsetPlacement = offset.GetPlacement();
  offsetPlacement.pos = CVec3(-offsetPlacement.pos.y, -offsetPlacement.pos.x, offsetPlacement.pos.z);
  placement += offsetPlacement;

  if ( endPoint->InitWellObject(_easel,_easel->GetData()->commonParams->endWell,placement)  )
  {
    rollOutConverter->Init(endPoint->GetStartLocator(), endPoint->GetMidLocator(), endPoint->GetEndLocator(), placement);
    
    easel->GetClient().AddObject( endPoint, false );

    // adding object to container
    pathObjects.push_back(CPtr<MinigameClientObject>(endPoint));

    return true;
  }

  return false;
}

void EaselLuxViewPath::CleanUp()
{
  {
    PathObjects::iterator it = pathObjects.begin();
    PathObjects::iterator last = pathObjects.end();

    for( ; it != last; ++it )
    {
      if ( IsValid( *it ) )
        easel->GetClient().ReleaseObject(*it);
    }
  }

  CleanUpPath();
}

void EaselLuxViewPath::CleanUpPath()
{
  {
    PathTailObjects::iterator it = pathTail.begin();
    PathTailObjects::iterator last = pathTail.end();

    for( ; it != last; ++it )
    {
      if ( IsValid( *it ) )
        easel->GetClient().ReleaseEffect( *it );
    }
  }

  ReleasePathHeadEffect();
}

void EaselLuxViewPath::Step( float deltaTime, LuxGameLogic* _gameLogic )
{
  if ( !IsValid( _gameLogic->GetGameBoard() ) )
    return;

  LuxBoardState state = _gameLogic->GetGameBoard()->GetBoardState();

  if ( state > BOARDSTATE_LEVEL_RUN )
  {
    CleanUpPath();
  }

  if ( state != BOARDSTATE_LEVEL_RUN )
    return;

  if ( !IsValid( pathHeadEffect ) && firstRun )
  {
    CreateNewPathHeadEffect( _gameLogic );
    coveredPath = 0;
    firstRun = false;
  }

  if ( IsValid( pathHeadEffect ) )
  {
    float chainVelocity = _gameLogic->GetGameData()->commonParams->effects.pathfinderVelocity * 1000.f;
    float effectInterval = _gameLogic->GetGameData()->commonParams->effects.pathfinderInterval * 1000.f;

    coveredPath += chainVelocity * (deltaTime * 1000.f);

    if ( coveredPath > path->GetTrajectory()->GetLenght() )
    {
      ReleasePathHeadEffect();
    }
    else
    {
      int needToPlace = int( double(coveredPath) / effectInterval );

      if ( needToPlace > pathTail.size() )
      {
        for ( int i = pathTail.size(); i <= needToPlace; ++i )
        {
          int64 nextPoint = i * int( effectInterval );

          bool isPointVisible = !path->IsPointInsideTunnel( nextPoint, _gameLogic );

          CreateNewPathTailEffect( _gameLogic, isPointVisible );
          PlaceEffectOnPath( pathTail.back(), nextPoint );
        }
      }

      PlaceEffectOnPath( pathHeadEffect, coveredPath );
    }
  }
}

void EaselLuxViewPath::PlaceEffectOnPath( PF_Core::BasicEffectStandalone* _effect, int64 _pathPos )
{
  SVector worldPos;
  path->GetTrajectory()->GetCoordsByLenght( _pathPos, worldPos );
  CVec3 clientPos = easel->GetConvertHelper()->ConvertWorldToClientCoordinates( worldPos );

  if ( IsValid( _effect ) )
    _effect->SetPosition( clientPos );
}

void EaselLuxViewPath::CreateNewPathHeadEffect( LuxGameLogic* _gameLogic )
{
  if ( IsValid( pathHeadEffect ) )
    ReleasePathHeadEffect();

  pathHeadEffect = easel->GetClient().CreateStandaloneEffect( _gameLogic->GetGameData()->commonParams->effects.pathfinderHead, true );

  if ( pathHeadEffect )
    pathHeadEffect->AddToScene( easel->GetScene() );

  easel->GetWorld()->GetSound()->PlaySound(NDb::EASELSOUNDTYPE_SCORPION_START);
}

void EaselLuxViewPath::ReleasePathHeadEffect()
{
  if ( IsValid( pathHeadEffect ) )
    easel->GetClient().ReleaseEffect( pathHeadEffect );

  pathHeadEffect = 0;

  easel->GetWorld()->GetSound()->StopSound(NDb::EASELSOUNDTYPE_SCORPION_START);
}

void EaselLuxViewPath::CreateNewPathTailEffect( LuxGameLogic* _gameLogic, bool visible )
{
  CObj<PF_Core::BasicEffectStandalone> pathTailEffect = 
    easel->GetClient().CreateStandaloneEffect( _gameLogic->GetGameData()->commonParams->effects.pathfinderTail, true );

  if ( IsValid( pathTailEffect ) && visible )
    pathTailEffect->AddToScene( easel->GetScene() );

  pathTail.push_back( pathTailEffect );
}

}

BASIC_REGISTER_CLASS( PF_Minigames::EaselLuxViewPath )
