#include "stdafx.h"
#include "MmQueueIterator.h"
#include "Db/DBServer.auto.h"
#include "System/InlineProfiler.h"


namespace mmaking
{

MmRequest * QueueIterator::NextRequest( QueueIteratorCtx & ctx )
{
  ctx = QueueIteratorCtx();
  
  if (isRandomChoise)
    return NextRandomRequest(ctx);
  
  
  for ( ; ; ++current )
  {
    if ( current == requests.end() )
      return 0;

    StrongMT<MmRequest> req = current->second;

    if (!checkRequest(req, ctx))
      continue;
    
    ++current;
    return req;
  }
    
}


MmRequest * QueueIterator::NextRandomRequest( QueueIteratorCtx & ctx )
{
  for ( ; ; ++current_key)
  {
    if ( current_key == key_requests.end() )
      return 0;
    
    const mmaking::TRequestUId key = (*current_key);
    
    BaseMMaking::TRequestMap::const_iterator it = requests.find(key);
    if ( it == requests.end() )
      return 0;

    StrongMT<MmRequest> req = it->second;

    if (!checkRequest(req,ctx))
       continue;  

    ++current_key;
    return req;
  }

}

bool QueueIterator::checkRequest(MmRequest* req, QueueIteratorCtx & ctx)
{
  if ( revision && revision!=-1)
    if ( req->CommonData().clientRevision != revision )
      return false;

  if ( basket != EBasket::Undefined )
      if ( req->Basket() != basket && req->Basket()!= EBasket::Leaver )
      return false;

  ctx.waitTime = now - req->StartTime();

  timer::Time waitTimePenalty = 0;
   
  switch (sidesLocale.size())
  {
    case 1:
      if ( !FilterPresampleByLocale( req, ctx.waitTime, waitTimePenalty, sidesLocale[0] ) )
        return false;
      break; 
    case 2:
      if ( !FilterPresampleByLocale( req, ctx.waitTime, waitTimePenalty, sidesLocale[0] ) )
        if ( !FilterPresampleByLocale( req, ctx.waitTime, waitTimePenalty, sidesLocale[1] ) )
          return false;
      break;
  
  }

  ctx.pingIsGood = false;
  if ( !FilterPresampleByPing( req, ctx.waitTime, waitTimePenalty, ctx.pingIsGood ) )
    return false;

  ctx.waitTime = Max( 0.0, ctx.waitTime - waitTimePenalty );
  
  return true;
}


bool QueueIterator::FilterPresampleByLocale( MmRequest * _req, timer::Time _waitTime, timer::Time & _waitTimePenalty, const TGeoIndex& primaryLocale )
{
  NI_PROFILE_FUNCTION;

  const TGeoIndex requestLoc = _req->Locale();

  if ( !requestLoc ) //Unknown locale is compatible with everything
    return true;

  if ( requestLoc != primaryLocale )
    if ( locales.Isolated( requestLoc ) || locales.Isolated( primaryLocale ) )
      return false;

  if ( flags & F_IgnoreLocaleAndPing )
    return true;

  if ( !donorLocale )
    return ( requestLoc == primaryLocale );

  if ( flags & F_RatingSortMode )
  {
    if ( requestLoc == primaryLocale )
    {
      if ( _waitTime < settings->localeWaitTimeThreshold )
        return false;
      _waitTimePenalty += settings->localeWaitTimeThreshold;
      return true;
    }
    else
      if ( requestLoc == donorLocale )
        return true;

    return false;
  }

  return ( requestLoc == primaryLocale ) || ( requestLoc == donorLocale );
}



bool QueueIterator::FilterPresampleByPing( MmRequest * _req, timer::Time _waitTime, timer::Time & _waitTimePenalty, bool & _pingIsGood )
{
  NI_PROFILE_FUNCTION;

  _pingIsGood = true;

  if ( flags & F_IgnoreLocaleAndPing )
    return true;

  if ( config->ignorePings )
    return true;

  if ( !geolocation )
    return true;

  const LocationPingInfo * info = _req->LocationPing( geolocation );
  NI_VERIFY( info, "", return false );

  //timer::Time penalty = info->avgQuality * settings->locationPingSettings.worstPingWaitTimePenalty;
  timer::Time penalty = 0;
  if ( info->avgQuality > 0.01 )
    penalty = settings->locationPingSettings.worstPingWaitTimePenalty;
  
  if ( _waitTime < penalty )
    return false;

  _waitTimePenalty += penalty;

  _pingIsGood = ( info->avgQuality < settings->locationPingSettings.goodEnoughPingFactor );
  return true;
}

} //namespace mmaking
