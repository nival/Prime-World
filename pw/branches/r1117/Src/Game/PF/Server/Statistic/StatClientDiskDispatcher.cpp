#include "stdafx.h"
#include "StatClientDiskDispatcher.h"
#include "system/math/md4.h"


namespace StatisticService
{

ClientDiskDispatcher::ClientDiskDispatcher()
{
  destFolder = NProfile::GetFullFolderPath( NProfile::FOLDER_USER );
  NFile::RemoveSlash( &destFolder );
  destFolder += '\\';
  destFolder += "statdata\\";

  NFile::CreatePath( destFolder );
}


const static char * Salt = "Prime World Launcher";

bool ClientDiskDispatcher::DispatchChunk( const TMessageData & _data, unsigned _msgNumber )
{
  if ( !_data.size() )
    return true;

  time_t seconds = 0;
  time( &seconds );
  string fname = destFolder + NI_STRFMT( "%08x%016x.sta", seconds, timer::GetTicks() );

  FILE * f = fopen( fname.c_str(), "wb" );
  if ( !f )
  {
    WarningTrace( "Cannot create statistics data file. name='%s'", fname );
    return false;
  }

  const ni_detail::UInt32 urlLen = DestUrl().length();
  vector<byte> encodedUrl( DestUrl().size() );
  for ( int i = 0; i < DestUrl().size(); ++i )
    encodedUrl[i] = (byte)DestUrl()[i] ^ (byte)( 0xff & ( ( i + 101 ) * 11 ) );

  math::MD5Generator md5;
  md5.Start();
  md5.Update( (const byte *)Salt, strlen( Salt ) );
  md5.AddObject( urlLen );
  md5.Update( &encodedUrl[0], encodedUrl.size() );
  md5.Update( &_data[0], _data.size() );
  md5.Update( (const byte *)Salt, strlen( Salt ) );
  md5.Stop();

  if ( fwrite( md5.Get().code, md5.Get().DIGEST_SIZE_IN_BYTES, 1, f ) == 1 )
    if ( fwrite( &urlLen, sizeof( urlLen ), 1, f ) == 1 )
      if ( fwrite( &encodedUrl[0], 1, encodedUrl.size(), f ) == (size_t)encodedUrl.size() )
        if ( fwrite( &_data[0], 1, _data.size(), f ) == (size_t)_data.size() )
        {
          fclose( f );

          MessageTrace( "Statistics data chunk written. size=%u, fname=%s", _data.size(), fname );
          return true;
        }

  WarningTrace( "Cannot write statistics data. name='%s', size=%d", fname, _data.size() );
  fclose( f );
  return false;
}

} //namespace StatisticService