#include "stdafx.h"

#include "Easel.h"
#include "EaselWorld.h"
#include "BoostsFactory.h"
#include "LuxDef.h"
#include "LuxBoost.h"
#include "LuxPaintBlastBoost.h"
#include "LuxJokerBoost.h"
#include "LuxFreezeBoost.h"
#include "LuxSorterBoost.h"
#include "LuxMagnetBoost.h"
#include "LuxAlchemistBoost.h"

namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// class LuxBoostsFactory implementation
//
//////////////////////////////////////////////////////////////////////////
LuxBoostsFactory::LuxBoostsFactory( Easel * _easel ) :
easel( _easel )
{

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBoostsFactory::~LuxBoostsFactory()
{
}

LuxBoost* LuxBoostsFactory::CreateBoost(NDb::EBoostType _type,
                                  const NDb::Ptr<NDb::DBEaselData>& _pData)
{
  if ( !IsValid( _pData ) )
    return 0;

  NDb::EBoostUsage _usage = _pData->gameboosts.boostsTemplate[_type].boostUsage;

  switch ( _type )
  {
    case NDb::BOOSTTYPE_PAINTBLAST:  return CreatePaintBlastBoost( _usage, _pData );
    case NDb::BOOSTTYPE_FREEZE:      return CreateFreezeBoost( _usage, _pData );
    case NDb::BOOSTTYPE_JOKER:       return CreateJokerBoost( _usage, _pData );
    case NDb::BOOSTTYPE_SORTER:      return CreateSorterBoost( _usage, _pData );
    case NDb::BOOSTTYPE_ALCHEMIST:   return CreateAlchemistBoost( _usage, _pData );
    case NDb::BOOSTTYPE_MAGNET:      return CreateMagnetBoost( _usage,_pData );

    default:
      return 0;
  }
}

LuxBoost* LuxBoostsFactory::CreatePaintBlastBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData)
{
  return new LuxPaintBlastBoost( easel->GetPFWorld(), easel,
                                  pData->gameboosts.paintblast.boostBase.name,
                                  pData->gameboosts.paintblast.boostBase.cooldown,
                                  pData->gameboosts.paintblast.boostBase.accesslevel,
                                  pData->gameboosts.paintblast.boostBase.price,
                                  pData->gameboosts.paintblast.radius );
}

LuxBoost* LuxBoostsFactory::CreateJokerBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData)
{
  return new LuxJokerBoost( easel->GetPFWorld(), easel,
                                  pData->gameboosts.joker.boostBase.name,
                                  pData->gameboosts.joker.boostBase.cooldown,
                                  pData->gameboosts.joker.boostBase.accesslevel,
                                  pData->gameboosts.joker.boostBase.price );
}

LuxBoost* LuxBoostsFactory::CreateFreezeBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData)
{
  return new LuxFreezeBoost( easel->GetPFWorld(), easel,
                                  pData->gameboosts.freeze.boostBase.name,
                                  pData->gameboosts.freeze.boostBase.cooldown,
                                  pData->gameboosts.freeze.boostBase.accesslevel,
                                  pData->gameboosts.freeze.boostBase.price,
                                  pData->gameboosts.freeze.seconds );
}

LuxBoost* LuxBoostsFactory::CreateSorterBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData)
{
  return new LuxSorterBoost( easel->GetPFWorld(), easel,
                                pData->gameboosts.sorter.boostBase.name,
                                pData->gameboosts.sorter.boostBase.cooldown,
                                pData->gameboosts.sorter.boostBase.accesslevel,
                                pData->gameboosts.sorter.boostBase.price );
}

LuxBoost* LuxBoostsFactory::CreateMagnetBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData)
{
  //Why this bunch of parameters? Is is better to drag entire NDb-structure into LuxMagnetBoost's ctor..
  return new LuxMagnetBoost( easel->GetPFWorld(), easel,
                                pData->gameboosts.magnet.boostBase.name,
                                pData->gameboosts.magnet.boostBase.cooldown,
                                pData->gameboosts.magnet.boostBase.accesslevel,
                                pData->gameboosts.magnet.boostBase.price,
                                pData->gameboosts.magnet.searchSeconds,
                                pData->gameboosts.magnet.radiusR1,
                                pData->gameboosts.magnet.radiusR2,
                                pData->gameboosts.magnet.numBallToEat );
}

LuxBoost* LuxBoostsFactory::CreateAlchemistBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData)
{
  const NDb::DBAlchemistBoost& alchemistParams = pData->gameboosts.alchemist;

  return new LuxAlchemistBoost( easel->GetPFWorld(), easel,
                              alchemistParams.boostBase.name,
                              alchemistParams.boostBase.cooldown,
                              alchemistParams.boostBase.accesslevel,
                              alchemistParams.boostBase.price,
                              alchemistParams.alchemistDuration,
                              alchemistParams.additionalPaint,
                              alchemistParams.paintMult );
}

}

