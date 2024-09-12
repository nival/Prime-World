#include "stdafx.h"

#include "../Core/Transceiver.h"
#include "../Scene/DBScene.h"

#include "LuxPlatform.h"

#include "LuxDef.h"

#include "MinigameSessionInterface.h"
#include "../PF_GameLogic/SessionEventType.h"

#include "Easel.h"
#include "EaselWorldClientConvertHelper.h"
#include "Random.h"

#include "LuxPaintBlastBoost.h"
#include "LuxJokerBoost.h"
#include "LuxGameBoard.h"
#include "LuxGameBoardChains.h"
#include "LuxBallChain.h"
#include "LuxPath.h"
#include "LuxGameLogic.h"

#include "EaselTrajectory.h"

#include "../System/nalgoritm.h"


namespace PF_Minigames
{

const int numRandAttempts = 20;
const int maxNumSameColorsInRow = 2;

//////////////////////////////////////////////////////////////////////////
//
// class LuxPlatform implementation 
//
//////////////////////////////////////////////////////////////////////////
LuxPlatform::LuxPlatform( Easel* _easel, EaselNotifier* _pNotifier ) : 
  PF_Core::WorldObjectBase( _easel->GetPFWorld(), false ),
  platformPos(0,0),
  collisionPoint(0,0),
  hasCollision( false ),
  isBallOnPlatform(false),
  notifier(_pNotifier),
  easel(_easel),
  lastColor( NDb::COLOR_BLACK ),
  lastColorRepeatNum( 0 )
{
  randomGenerator.SetRandomSeed( easel->GetRandomSeed() );

  bool triple = easel->GetWorldSessionInterface()->GetCurrentBidon() == NDb::BIDONTYPE_PALETTE;

  const int ballsCount = triple ? 3 : 2;
  balls.resize( ballsCount, 0 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxPlatform::~LuxPlatform()
{
	isBallOnPlatform = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxPlatform::FindLocator( const NDb::DBSceneObject* _sceneObject, const char* name, Placement& locatorPlacement )
{
  if ( !_sceneObject )
    return false;

  for ( int i = 0; i < _sceneObject->attached.size(); ++i )
  {
    if ( _sceneObject->attached[i].component )
    {
      const NDb::AttachedSceneComponent& sceneComponent = _sceneObject->attached[i];

      if ( !sceneComponent.component->locatorList.IsEmpty() )
      {
        vector<NDb::Locator> const &locators = sceneComponent.component->locatorList->locators;
        for ( int j = 0; j < locators.size(); ++j )
        {
          if ( locators[j].name == name )
          {
            Placement basePlacement;
            basePlacement.pos = sceneComponent.placement.pos.GetValue( 0.f );
            basePlacement.rot = sceneComponent.placement.rot.GetValue( 0.f );
            basePlacement.scale = sceneComponent.placement.scale.GetValue( 0.f );

            basePlacement.Transform( locators[j].offset2.GetPlace().pos, locatorPlacement.pos );

            return true;
          }
        }
      }
    }
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxPlatform::InitialCreateBalls( LuxGameBoard* gameBoard )
{
  NDb::EColor nextColor = NDb::COLOR_ANY;

  for ( int i = 0; i < balls.size(); ++i )
  {
    if ( i < balls.size() )
    {
      nextColor = GetNextColor( nextColor, gameBoard );     
      CreateBall( i, nextColor, EBallType::Simple );
    }
    else
    {
      balls[i] = 0;
    }
  }
}

bool LuxPlatform::UpdateBalls( bool forceNewBall, LuxGameBoard* gameBoard )
{
  bool changed = false;
  NDb::EColor nextColor = NDb::COLOR_ANY;

  for ( int i = 0; i < balls.size(); ++i )
  {
    if ( !balls[i] )
      continue;

    if ( !IsColorInChains( balls[i]->Color(), gameBoard ) )
    {
      nextColor = GetNextColor( nextColor, gameBoard );     
      CreateBall( i, nextColor, EBallType::Simple );
      changed = true;
    }
  }

  if ( !forceNewBall )
    return changed;

  for ( int i = 1; i < balls.size(); ++i )
  {
    if ( balls[i - 1] && ( balls[i - 1]->Color() == NDb::COLOR_ANY ) )
      continue;

    balls[i - 1] = balls[i];
  }

  nextColor = GetNextColor( nextColor, gameBoard );     
  CreateBall( balls.size() - 1, nextColor, EBallType::Simple );

  return true;
}

void LuxPlatform::SwapBalls()
{

  //this is only for one purpose: not to spam events every time. only the fact that matters
  static bool hasBallsChanged = false;

  if (!hasBallsChanged && IsValid(easel))
  {
    hasBallsChanged = true;
    IWorldSessionInterface * sessionInterface =  easel->GetWorldSessionInterface();

    if (sessionInterface)
      sessionInterface->LogMinigameEvent(SessionEventType::MG2BallsChanged, 0, 0);
  }


  CObj<LuxBall> firstBall = balls[0];

  for ( int i = 1; i < balls.size(); ++ i)
  {
    balls[i - 1] = balls[i];
  }

  balls[balls.size() - 1] = firstBall;

  SetPlatformPos(platformPos);
}

bool LuxPlatform::IsColorInChains( NDb::EColor color, LuxGameBoard* gameBoard ) const
{
  if ( color == NDb::COLOR_ANY )
    return true;

  ColorWeights weights;
  CollectColorWeights( weights, gameBoard );

  return ( weights.find( color ) != weights.end() );
}

float LuxPlatform::GetBulletVelocity()
{
  return easel->GetData()->commonParams->ballVelocities.bulletVelocity;
}

LuxBall* LuxPlatform::CreateBall( int pos, NDb::EColor color, EBallType::Enum _type )
{
  balls[pos] = new LuxBall( easel->GetPFWorld(), notifier, _type, platformPos, color );
  balls[pos]->SetSpeed( GetBulletVelocity() );

  balls[pos]->SetDirection( SVector(0, -1 * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER()) );
  balls[pos]->SetState( BALL_STATE_ON_PLATFORM );

  SetPlatformPos(platformPos);
  balls[pos]->InitVisual();

  return balls[pos];
}


LuxBall* LuxPlatform::CreatePaintBlastBall()
{
  return CreateBall( 0, NDb::COLOR_ANY, EBallType::PainBlast );
}


LuxBall* LuxPlatform::CreateJokerBall()
{
  return CreateBall( 0, NDb::COLOR_ANY, EBallType::Joker );
}


CObj<LuxBall> LuxPlatform::FireBulletBall()
{
  CObj<LuxBall> ball = balls[0];
  balls[0] = 0;

  if ( IsValid( ball ) )
    ball->SetState( BALL_STATE_FIRED );

  return ball;
}

bool LuxPlatform::SetPlatformPos(SVector newPos)
{
	platformPos = newPos;

  //“ак как использование функции ConvertWorldToClientCoordinates() всегда приводит к асинку,
  //то здесь мы захардкодим положение шариков в каретке

  //TODO: располагать шарики через локаторы SO, но в клиентском коде
  //¬орлдовый код не должен зависить от локаторов и не должен напр€мую визуализировать шарики в каретке

  //≈сть только одна проблема - откуда выстреливать шарики

  SVector tmpPos = platformPos;
  tmpPos.y += EaselConst::Get_LOGIC_FIELD_HEIGHT() / 2;
  const float ballSize = EaselConst::Get_BALL_DEF_DIAMETER();
  if ( balls.size() == 2 )
  {
    if ( balls[0] )
      balls[0]->SetPosition( SVector( tmpPos.x, tmpPos.y + ballSize ) );

    if ( balls[1] )
      balls[1]->SetPosition( SVector( tmpPos.x, tmpPos.y + 2 * ballSize ) );
  }
  else if ( balls.size() == 3 )
  {
    if ( balls[0] )
      balls[0]->SetPosition( SVector( tmpPos.x, tmpPos.y + 1.3f * ballSize ) );

    const float x = 0.55f, y = 2.25f;

    if ( balls[1] )
      balls[1]->SetPosition( SVector( tmpPos.x + x * ballSize, tmpPos.y + y * ballSize ) );

    if ( balls[2] )
      balls[2]->SetPosition( SVector( tmpPos.x - x * ballSize, tmpPos.y + y * ballSize ) );
  }

  return true;
}

NDb::EColor LuxPlatform::GetNextColor( NDb::EColor _exceptColor, LuxGameBoard* gameBoard )
{
  ColorWeights weights;
  CollectColorWeights( weights, gameBoard );

  float lowActChance = easel->GetData()->commonParams->platformGeneratorParams.lowActChance;

  if ( randomGenerator.Random(0.0f, 1.0f) <= lowActChance )
    return GetNextColorByWeight( _exceptColor, weights, gameBoard );
  else
    return PerformLowAct( weights );
}

NDb::EColor LuxPlatform::PerformLowAct( const ColorWeights& _weights )
{
  if ( _weights.empty() )
    return NDb::COLOR_WHITE;

  NDb::EColor newColor = NDb::COLOR_ANY;

  for(int i = 0; i < numRandAttempts; ++i)
  {
    ColorWeights::const_iterator colorIt = _weights.begin();

    nstl::advance( colorIt, int( randomGenerator.Random( 0, _weights.size() - 1 ) ) );
    newColor = colorIt->first;

    if ( newColor == NDb::COLOR_ANY )
    {
      i--;
      continue;
    }

    if( newColor != lastColor )
    {
      lastColor = newColor;
      lastColorRepeatNum = 1;
      break;
    } 
    else if( lastColorRepeatNum < maxNumSameColorsInRow )
    {
      ++lastColorRepeatNum;
      break;
    }
  }

  return newColor;

}

NDb::EColor LuxPlatform::GetNextColorByWeight( NDb::EColor _exceptColor, const ColorWeights& _weights, LuxGameBoard* gameBoard )
{
  if ( _weights.empty() )
    return NDb::COLOR_WHITE;

  float maxWeigth = _weights.begin()->second.weight;;
  NDb::EColor color = NDb::EColor(0);
  bool noStrongColorsSoFar = true;

  ColorWeights::iterator it = _weights.begin();
  ColorWeights::iterator last = _weights.end();

  // get color with most weight
  for ( ; it != last; ++it )
  {
    float currentWeight = it->second.weight;

    // calculate restriction: generate same color in the raw no more than <maxNumSameColorsInRow>
    bool sameColorInRawOverrun = (lastColor == it->first) && (lastColorRepeatNum >= maxNumSameColorsInRow );
    bool strongColor = !sameColorInRawOverrun && (currentWeight > 0) && !(_exceptColor == it->first);

    if(!noStrongColorsSoFar && !strongColor)
    {
      continue;
    }

    if( (noStrongColorsSoFar && strongColor) || (currentWeight >= maxWeigth) ) 
    {
      maxWeigth = currentWeight;
      color = it->first;
    }

    noStrongColorsSoFar = noStrongColorsSoFar && !strongColor;
  }

  if( color == lastColor )
  {
    lastColorRepeatNum += 1;
  }
  else
  {
    lastColor = color;
    lastColorRepeatNum = 1;
  }

  return color;
}

void LuxPlatform::CollectColorWeights( ColorWeights& _weights, LuxGameBoard* gameBoard ) const
{
  float power = easel->GetData()->commonParams->platformGeneratorParams.colorWeightsPower;

  BoardChains::const_iterator it = gameBoard->GetChains().begin();
  BoardChains::const_iterator last = gameBoard->GetChains().end();

  for( ; it != last; ++it )
  {
    BallChains::const_iterator itC = (*it)->GetChains().begin();
    BallChains::const_iterator lastC = (*it)->GetChains().end();

    for ( ; itC != lastC; ++itC )
    {
      float pathLength = (*itC)->GetPath()->GetTrajectory()->GetLenght();

      LuxBallChain::ChainBalls::const_iterator itB = (*itC)->GetBalls().begin();
      LuxBallChain::ChainBalls::const_iterator lastB = (*itC)->GetBalls().end();

      for ( ; itB != lastB; ++itB )
      {
        NDb::EColor ballColor = itB->ball->Color();
        float ballPath = itB->ball->GetCoveredPath();

        _weights[ballColor].count++;

        float weight = Sign( ballPath / pathLength ) * pow( ballPath / pathLength, power );
        weight = max(weight, 0.00000001f);

        _weights[ballColor].weight += weight;
      }
    }
  }
}


}

REGISTER_SAVELOAD_CLASS_NM( LuxPlatform, PF_Minigames )
