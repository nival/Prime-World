#include "stdafx.h"
#include "TalentRollDataCache.h"
#include "RollLog.h"


namespace roll
{

static float s_cacheTimeout = 60.0f; //in minutes
REGISTER_VAR( "roll_cache_timeout", s_cacheTimeout, STORAGE_NONE );


TalentRollDataCache::TalentRollDataCache( timer::Time now ) :
lastUpdate( 0 )
{
}



void TalentRollDataCache::Put( lobby::TUserId uid, const NCore::TalentRollData & data )
{
  Entry & entry = storage[uid];
  entry.data.generationIndex = data.generationIndex;

  // merge data
  NCore::TTalentRollTable::const_iterator itEnd = data.rollTable.end();
  for ( NCore::TTalentRollTable::const_iterator it = data.rollTable.begin(); it != itEnd; ++it )
  {
    entry.data.rollTable[it->first] = it->second;
  }

  entry.lastAccess = lastUpdate;

  ROLL_LOG_DBG( "Talent roll data cache updated. uid=%d, gen_idx=%d", uid, entry.data.generationIndex );
}



void TalentRollDataCache::GetCorrectData( NCore::TalentRollData & result, const NCore::TalentRollData & newData, lobby::TUserId uid )
{
  Storage::iterator it = storage.find( uid );
  if ( it == storage.end() ) {
    result = newData;
    return;
  }

  Entry & cacheEntry = it->second;

  if ( newData.generationIndex >= cacheEntry.data.generationIndex )
    result = newData;
  else
  {
    ROLL_LOG_WRN( "Talent roll data cache conflict: uid=%d, new_gen_idx=%d, cache_gen_idx=%d", uid, newData.generationIndex, cacheEntry.data.generationIndex );

    result.generationIndex = cacheEntry.data.generationIndex;

    //result = cacheEntry.data; // should merge hash_map
    NCore::TTalentRollTable::const_iterator itEnd = newData.rollTable.end();
    NCore::TTalentRollTable::const_iterator cacheEnd = cacheEntry.data.rollTable.end();
    for ( NCore::TTalentRollTable::const_iterator it = newData.rollTable.begin(); it != itEnd; ++it )
    {
      NCore::TTalentRollTable::const_iterator itCache = cacheEntry.data.rollTable.find( it->first );
      if ( itCache == cacheEnd )
      {
        // no cache record
        cacheEntry.data.rollTable[it->first] = it->second;
        result.rollTable[it->first] = it->second;
      }
      else
      {
        // cache record hit
        result.rollTable[it->first] = itCache->second;
      }
    }
    return;
  }
}



void TalentRollDataCache::Poll( timer::Time now )
{
  lastUpdate = now;

  if ( s_cacheTimeout )
  {
    timer::Time minAccessTime = now - s_cacheTimeout * 60.0f;

    for ( Storage::iterator it = storage.begin(); it != storage.end(); )
    {
      lobby::TUserId uid = it->first;
      Entry & cacheEntry = it->second;
      if ( cacheEntry.lastAccess < minAccessTime )
      {
        ROLL_LOG_DBG( "Talent roll data cache expired. uid=%d, gen_idx=%d", uid, cacheEntry.data.generationIndex );
        it = storage.erase( it );
        continue;
      }

      ++it;
    }
  }
}

} //namespace roll
