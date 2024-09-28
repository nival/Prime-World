#include "stdafx.h"
#include "LoadingProgress.h"


BASIC_REGISTER_CLASS( LoadingProgress );


void LoadingProgress::InitPartialWeight( int id, float weight )
{
  threading::MutexLock lock( mutex );

  pair<TItems::iterator, bool> result = items.insert( TItems::value_type( id, SItem( weight ) ) );
  NI_ASSERT( result.second, "Such progress group already exists" );
}



void LoadingProgress::SetPartialProgress( int id, float t )
{
  threading::MutexLock lock( mutex );

  TItems::iterator it = items.find( id );
  NI_VERIFY( it != items.end(), "Unknown progress group", return );
  it->second.currentProgress = t;
}



float LoadingProgress::GetTotalProgress() const
{
  threading::MutexLock lock( mutex );

  float totalWeight = 0;
  for ( TItems::iterator it = items.begin(); it != items.end(); ++it )
    totalWeight += it->second.weight;

  if ( totalWeight < 1e-3 )
    return 0;

  float result = 0;
  for ( TItems::iterator it = items.begin(); it != items.end(); ++it )
    result += it->second.weight / totalWeight * Clamp( it->second.currentProgress, 0.0f, 1.0f );

  return result;
}
