#include "stdafx.h"
#include "BinChunkSerializer.h"
#include "BinChunkSaverImpl.h"
#include "BinChunkLoaderImpl.h"


IBinSaver * CreateReadBinSaver( Stream * pStream, IProgressHook * pProgress )
{
  if ( !IsValid( pStream ) )
    return 0;

  return new BinChunkLoaderImpl( pStream, pProgress );
}



IBinSaver * CreateWriteBinSaver( Stream * pStream, const int version, const bool compress )
{
  if ( !IsValid( pStream ) )
    return 0;

  return new BinChunkSaverImpl( pStream, version );
}
