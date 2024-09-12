#include "stdafx.h"

#include "LuxGameBoardChains.h"

#include "DBEasel.h"
#include "EaselTrajectory.h"

#include "Random.h"

#include "LuxBall.h"

#include "LuxChainGenerator.h"

#include "LuxPath.h"

#include "LuxGameBoard.h"

#include "LuxChainGeneratedNotification.h"
#include "LuxChainMergedNotification.h"
#include "LuxChainDestroyedNotification.h"

#include "LuxGameLogic.h"
#include "EaselPriestess.h"
#include "EaselConstants.h"
#include "Easel.h"

namespace PF_Minigames
{

bool EASEL_FORBID_CHAINS_GENERATION = false;
REGISTER_DEV_VAR("easel_forbid_chains_generation",EASEL_FORBID_CHAINS_GENERATION,STORAGE_NONE);

const int RANDOM_RETRIES  = 100;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddHittedBallToChain(LuxBallChain& chain, int64 ballPos, LuxBall* bullet, /*out*/bool &fColorMatched)
{
  bullet->SetCoveredPath( ballPos );
  chain.AddChainBallRunTime( bullet, fColorMatched );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxGameBoardChain::LuxGameBoardChain( PF_Core::IWorld* _pWorld, LuxGameBoard *_pGameBoard )
: PF_Core::WorldObjectBase( _pWorld, false )
, nextChainTimeLeft(0)
, newChainOffset(0)
, pNotifier(0)
, defaultChainSpeed(10)
, chainSpeed(10)
, killAfterEndOffset(0)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxGameBoardChain::IsAnyChainMoving() const
{
  BallChains::const_iterator chainsIter = chains.begin();
  for(; chainsIter != chains.end(); ++chainsIter)
  {
    if((*chainsIter)->GetState() == LuxBallChain::STATE_ON_BOARD 
      && (*chainsIter)->GetSpeed() != 0)
      return true;
  }
  
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::SetChainsSpeed(int _speed)
{
  BallChains::iterator chainsIter = chains.begin();
  for(; chainsIter != chains.end(); ++chainsIter)
    (*chainsIter)->SetSpeed(_speed);

  chainSpeed = _speed;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LuxGameBoardChain::Init( const NDb::DBEaselData* _data,
                             EaselNotifier* notifier,
                             LuxPath* _path,
                             LuxChainGenerator* _chainsGenerator)
{
  NI_VERIFY( (notifier != NULL), "LuxGameBoardChain: init failed - notifier is invalid", return LUX_ERROR );
  NI_VERIFY( IsValid(_path), "LuxGameBoardChain: init failed - path is invalid", return LUX_ERROR );
  NI_VERIFY( IsValid(_chainsGenerator), "LuxGameBoardChain: init failed - chains generator invalid", return LUX_ERROR );

  gameData = _data;
  pNotifier = notifier;

  int chainTravelTime = _data->commonParams->chainTravelTime;
  NI_VERIFY(chainTravelTime > 0, "LuxGameBoardChain: init failed - chain travel time is invalid", return LUX_ERROR );

  newChainOffset = _data->startPointOffset * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
  killAfterEndOffset = _data->killChainAfterOffset * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();

  chainPath = _path;
  chainsGenerator = _chainsGenerator;

  int speed = chainPath->GetTrajectory()->GetLenght() / chainTravelTime;
  speed = (speed * chainPath->GetChainsData()->speedMultiplier) / 100;

  defaultChainSpeed = speed;
  chainSpeed = speed;

  nextChainTimeLeft += chainPath->GetChainsData()->firstChainDelay;

  return LUX_OK;
}

//////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::AddChain( LuxBallChain* _newChain )
{
  if(!IsValid(_newChain))
    return;

  chains.push_back(_newChain);  // inserting chain;

  ValidateChains();
}

void LuxGameBoardChain::ValidateChains()
{
  // removing empty chains
  BallChains::iterator _chainsIter = chains.begin();
  while(_chainsIter != chains.end())
  {
    if((*_chainsIter)->GetNumChainBalls() == 0)
    {
      _chainsIter = chains.erase(_chainsIter);
      continue;
    }
    else
      ++_chainsIter;
  }  

  // sorting chains ...
  // setting sort predicate ...
  struct SortPred : public nstl::binary_function<CObj<LuxBallChain>,CObj<LuxBallChain>,bool>
  {
    bool operator()(const CObj<LuxBallChain> &lhs, const CObj<LuxBallChain> &rhs) const
    {
      if(lhs->GetChainPosition() >= rhs->GetChainPosition())
        return true;
      else
        return false;
    }
  };

  chains.sort(SortPred());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::ForceNewChainGeneration( LuxGameLogic* _gameLogic )
{ 
  GenerateNewChain( _gameLogic ); 
  nextChainTimeLeft = chainPath->GetChainsData()->nextChainDelay;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::GenerateNewChains( int deltaTime, LuxGameLogic* _gameLogic )
{
  // generate new chain after specified time
  nextChainTimeLeft -= deltaTime;
  if(nextChainTimeLeft <= 0)
  {
    GenerateNewChain( _gameLogic );
    nextChainTimeLeft = chainPath->GetChainsData()->nextChainDelay;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::RemoveSameColorSequences( LuxGameBoard* _gameBoard )
{
  if ( chains.empty() )
    return;

  CObj<LuxBallChain> newChain;

  BallChains::iterator itCurrent = chains.begin();
  
  do
  {
    // explode all same color segments in every chain
    while( newChain = (*itCurrent)->ExplodeFirstSameColorSegment() )
    {
      (*itCurrent)->ProcessTunnelsIntersection();

      CObj<LuxBallChain> tonnelTearOffTail = (*itCurrent)->BackwardTearOffTonnel();

      if ( IsValid(tonnelTearOffTail) )
      {
        ++itCurrent;
        itCurrent = chains.insert( itCurrent, tonnelTearOffTail );
      }

      // if there is teared off tail - add it as a separate chain
      if ( IsValid( newChain ) )
      {
        ++itCurrent;
        itCurrent = chains.insert( itCurrent, newChain );
      }
    }

    // remove chain if it exploded completely
    if((*itCurrent)->GetNumChainBalls() == 0)
    {
      if(pNotifier != 0)
      {
        LuxChainDestroyedNotification *pNotification = new LuxChainDestroyedNotification();
        pNotification->chain = *itCurrent;

        if ( IsValid( pNotifier ) )
          pNotifier->Notify(*pNotification);
      }

      _gameBoard->GetGameLogic()->GetPristessProxy()->AddGoldDelayed( _gameBoard->GetGameLogic()->GetEasel()->GetPriestessLevelStats()->chainKillNafta );
      DevTrace( "MG2 DEBUG: Add gold for ChainExplode: chainKillNafta(%d) = total(%d)", _gameBoard->GetGameLogic()->GetEasel()->GetPriestessLevelStats()->chainKillNafta, _gameBoard->GetGameLogic()->GetEasel()->GetPriestessLevelStats()->chainKillNafta );
            
      itCurrent = chains.erase(itCurrent);
    }
    else
    {
      ++itCurrent;
    }
  } while(itCurrent != chains.end());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::ProcessPaintBlast(const SVector &_refBlastPos,int64 _radius)
{
  if(chains.empty())
    return;

  BallChains::iterator itCurrent = chains.begin();

  do
  {
    CObj<LuxBallChain> newChain;
    // explode all same color segments in every chain
    while( newChain = (*itCurrent)->ExplodePaintBlastWave(_refBlastPos,_radius) )   // !!! другой метод 
    {
      // if there is teared off tail - add it as a separate chain
      if ( IsValid( newChain )  )
      {
        ++itCurrent;
        itCurrent = chains.insert( itCurrent, newChain );
        //lpfnNewChainCallback(newChain); // notifying callback
        //pGameBoard->AddNewChain(newChain);
      }
    }

    // remove chain if it exploded completely
    if((*itCurrent)->GetNumChainBalls() == 0)
      itCurrent = chains.erase(itCurrent);
    else
      ++itCurrent;
    
  } while(itCurrent != chains.end());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LuxGameBoardChain::DestroyAllChains()
{
  if ( chains.empty()  )
    return;

  BallChains::iterator chainsIter = chains.begin();
  for(; chainsIter != chains.end(); ++chainsIter)
  {
    (*chainsIter)->ExplodeChainBalls();
  }

  chains.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::GenerateNewChain( LuxGameLogic* _gameLogic )
{
  if ( EASEL_FORBID_CHAINS_GENERATION  )
    return;

  CObj<LuxBallChain> newChain = new LuxBallChain( chainPath, pNotifier, _gameLogic->GetEasel() );
  newChain->SetDefaultSpeed( defaultChainSpeed );
  newChain->SetSpeed( chainSpeed );

  if( chainsGenerator->Generate( newChain, chainPath->GetChainsData(), _gameLogic->GetPaintLogic() ) )
  {
    newChain->SetChainPosition(newChainOffset);

    chains.push_back(newChain);
    if(pNotifier != 0)
    {
      LuxChainGeneratedNotification *pnotification = new LuxChainGeneratedNotification();

      if ( IsValid( pNotifier ) )
        pNotifier->Notify(*pnotification);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::UpdateChainsSpeed()
{

  if(chains.empty())
  {
    return;
  }

  // move chains
  BallChains::iterator itCurrent = chains.end();
  const BallChains::iterator itBegin = chains.begin();
  
  --itCurrent;
  (*itCurrent)->UpdateChainSpeed(true);

  while ( itCurrent != itBegin )
  {
    --itCurrent;  
    (*itCurrent)->UpdateChainSpeed(false);  
  }
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::MoveChains(int deltaTime)
{
  // move chains
  BallChains::iterator itCurrent = chains.begin();
  const BallChains::iterator itEnd = chains.end();
  for(; itCurrent != itEnd; ++itCurrent)
  {
    (*itCurrent)->MoveChain(deltaTime);
  }

}

void LuxGameBoardChain::CleanUpChains()
{
  chains.remove_if( CleanUpChainsPred() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::MergeIntersectingChains()
{
  if(chains.size() < 2)
  {
    return ;
  }

  // 
  BallChains::iterator itCurrent = chains.begin();
  BallChains::iterator itPrevious = itCurrent;
  ++itCurrent;
  do
  {
    if( (*itCurrent)->IsIntersects(**itPrevious) )
    {
      if(pNotifier != 0)
      {
        LuxChainMergedNotification *pnotification = new LuxChainMergedNotification();

        if ( IsValid( pNotifier ) )
          pNotifier->Notify(*pnotification);
      }
      
      if( (*itPrevious)->MergeTail(*itCurrent))
      {
        itCurrent = chains.erase(itCurrent);
      }
      else
      {
        itPrevious = itCurrent;
        ++itCurrent;
      }
    }
    else
    {
      itPrevious = itCurrent;
      ++itCurrent;
    }
  } while( itCurrent != chains.end() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::RemoveChainsCameToEnd( int _afterExitDistance )
{
  // 
  // Pavel<GnoM>Cherniavski TODO: нужно сделать реализацию на основе нормально remove_if алгоритма
  //
  BallChains::iterator itCurrent = chains.begin();
  while( itCurrent != chains.end() )
  {
    if((*itCurrent)->GetNumChainBalls() == 0)
    {
      itCurrent = chains.erase(itCurrent);
      continue;
    }

    int64 chainTailPos = (*itCurrent)->GetChainPosition() - (*itCurrent)->GetChainLength() - killAfterEndOffset;
    if( chainTailPos > chainPath->GetTrajectory()->GetLenght() + (_afterExitDistance * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER() ) )
    {
      itCurrent = chains.erase(itCurrent);
    }
    else
    {
      ++itCurrent;
    }
  } 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameBoardChain::SortAllChainsElements()
{
  BallChains::iterator itCurrent = chains.begin();
  const BallChains::iterator itEnd = chains.end();
  for(; itCurrent != itEnd; ++itCurrent)
  {
    // sorting each chain
    (*itCurrent)->SortChain();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxGameBoardChain::CheckChainReachedEnd(int64 _endOffset) const
{
  if ( chains.empty()  )
    return false;

  CPtr<LuxBallChain> _chain = chains.front();
  if(chainPath->GetTrajectory()->GetLenght() + _endOffset /*<=*/< _chain->GetChainPosition())
    return true;
  else
    return false;
}

} //PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( LuxGameBoardChain, PF_Minigames )