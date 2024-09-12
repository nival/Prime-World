#include "stdafx.h"

#include "LuxChainGenerator.h"

#include "LuxPath.h"
#include "LuxBallChain.h"
#include "LuxBall.h"
#include "LuxBall.h"

#include "EaselNotifications.h"

#include "PaintLogic.h"

namespace PF_Minigames
{

const int RANDOM_RETRIES  = 100;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxChainGenerator::LuxChainGenerator( PF_Core::IWorld* _pWorld )
: PF_Core::WorldObjectBase( _pWorld, false )
, numBallColors(0)
, numBallsGenerated(0)
, numPaintColors(0)
{

}

LuxChainGenerator::~LuxChainGenerator()
{

}

bool LuxChainGenerator::Init(EaselNotifier* _notifier,
                             int _seed)
{
  if(!IsValid(_notifier))
    return false;

  notifier   = _notifier;

  generator.SetRandomSeed(_seed);
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxChainGenerator::ChooseColorsForUsage(const NDb::EPaintStatistics& stats)
{
  NDb::EColor lastColor = NDb::EColor(-1);
  NDb::EColor color = lastColor;

  int colorUseCount[ NDb::KnownEnum<NDb::EColor>::sizeOf ];
  memset(&colorUseCount, 0, sizeof(colorUseCount));
  int colorsUsedCount = 0;

  // first fill with existing in paint colors
  int numColorsToPaint = 0;
  for(int i = 0; i < NDb::KnownEnum<NDb::EColor>::sizeOf ; ++i)
  {
    if(stats.remainColorCapacity[i] > 0)
    {
      usedColors[numColorsToPaint] = NDb::EColor(i);
      paintColors[numColorsToPaint] = NDb::EColor(i);
      ++numColorsToPaint;
      colorUseCount[i]++;
    }
  }

  numPaintColors = numColorsToPaint;

  // fill with other colors
  int numColors = stats.allPaintColors.size();
  for(; numColorsToPaint < NDb::KnownEnum<NDb::EColor>::sizeOf; ++numColorsToPaint)
  {
    
    // we use RANDOM_RETRIES to prevent infinite loops
    for(int i = 0; i < RANDOM_RETRIES; ++i)
    {
      color = stats.allPaintColors[ generator.Random(0, numColors - 1) ];

      if( (color != lastColor) && (colorUseCount[color]*numColors <= colorsUsedCount) )
      {
        break;
      }
    }

    colorsUsedCount++;
    colorUseCount[color]++;
    lastColor = color;

    usedColors[numColorsToPaint] = color;
  }

  //randomize colors
  for(int i = 0; i < stats.remainColorsToPaint; ++i)
  {
    int swapWith = generator.Random(0, stats.remainColorsToPaint - 1);
    swap( usedColors[i], usedColors[swapWith] );
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxChainGenerator::GenerateOneColorChunks( const NDb::DBEaselChains* _params )
{
  NDb::EColor lastColor = NDb::EColor(-1);
  NDb::EColor color = lastColor;

  // generate same color chains
  numBallsGenerated = 0;

  memset(&colorUseCount, 0, sizeof(colorUseCount));
  int colorsUsedCount = 0;

  NDb::EColor* availableColors = paintColors;
  int* numAvailableColors = &numPaintColors;

  while( numBallsGenerated < _params->numBallsInChain)
  {
    int chainLength = generator.Random(_params->minSameColorChain, _params->maxSameColorChain);

    chainLength = min( chainLength, _params->numBallsInChain - numBallsGenerated );
    chainLength = max( chainLength, _params->minSameColorChain);

    // we use RANDOM_RETRIES to prevent infinite loops
    for(int i = 0; i < RANDOM_RETRIES; ++i)
    {
      color = availableColors[ generator.Random(0, *numAvailableColors - 1 ) ];

      if( (color != lastColor) && (colorUseCount[color]*numBallColors <= colorsUsedCount) )
      {
        break;
      }
    }

    colorsUsedCount++;
    colorUseCount[color]++;
    lastColor = color;

    for(int i = 0; i < chainLength; ++i)
    {
      chain[numBallsGenerated + i] = color;
    }

    numBallsGenerated += chainLength;
    availableColors = usedColors;
    numAvailableColors = &numBallColors;
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxChainGenerator::RearrangeColorsInChain( const NDb::DBEaselChains* _params )
{
  NI_VERIFY(numBallsGenerated >= 2, "LuxChainGenerator: chain generation params is invalid. numBallsInChain < 2", return);

  for(int ball = 1; ball < numBallsGenerated - 1; ++ball)
  {
    if(generator.Random(1, 100) <= _params->colorsDistortionPercentage )
    {
      continue;
    }

    for(int i = 0; i < RANDOM_RETRIES; ++i)
    {
      int swapWith = generator.Random(1, numBallsGenerated - 2);

      if( (ball != swapWith) )
      {
        swap(chain[swapWith], chain[ball]);
        break;
      }      
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxChainGenerator::FillChainWithBalls( LuxBallChain* newChain )
{
  // add generate chain code there
  for ( int i = 0; i < numBallsGenerated; ++i )
  {
    CObj<LuxBall> _ball = new LuxBall( GetWorld(), notifier, EBallType::Simple, SVector(0,0), chain[i] );
    _ball->InitVisual();

    _ball->SetState( BALL_STATE_ROLL_IN );
    newChain->AddChainBallInit( _ball );
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxChainGenerator::Generate( LuxBallChain* newChain, const NDb::DBEaselChains* _params, PaintLogic* _paintLogic )
{
  NDb::EPaintStatistics stats;

  _paintLogic->GetPaintStatistics( stats );

  if(stats.remainPaintCapacity <= 0)
    return false;

  static int minNumColors = 3;

  numBallsGenerated = 0;

  numBallColors = stats.remainColorsToPaint;
  numBallColors = max(numBallColors, minNumColors);

  ChooseColorsForUsage( stats );

  NI_VERIFY(paintColors > 0, "LuxChainGenerator: there is no available colors to paint", return false);

  GenerateOneColorChunks( _params );
  RearrangeColorsInChain( _params );
 
  FillChainWithBalls(newChain);

  return true;
}

}

REGISTER_SAVELOAD_CLASS_NM( LuxChainGenerator, PF_Minigames );