#include <System/stdafx.h>
#include "MD4.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParseCommandLine( vector<wstring> *pParams, const wstring &commandLine )
{
  pParams->clear();
  for ( NStr::CStringIterator<wchar_t, const wstring&, NStr::CBracketMulticharSeparator<wchar_t, NStr::SQuoteTest<wchar_t> > > it( commandLine, ' ' ); !it.IsEnd(); it.Next() )
  {
    if ( !it.Get().empty() )
      pParams->push_back( it.Get() );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
math::MD4 GenerateMD5( const string &fileName )
{
  string buffer;
  CPtr<FileStream> pStream = new FileStream( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  if ( !IsValid( pStream ) || !pStream->IsOk() )
    return math::MD4();

  buffer.resize( pStream->GetSize() );
  pStream->Read( &(buffer[0]), pStream->GetSize() );

  math::MD5Generator md;
  md.Start();
  md.Update( (const byte*)buffer.c_str(), buffer.length() );
  return md.Stop();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SaveMD4( math::MD4 &md4, const string &szFileName )
{
  CPtr<FileStream> pStream = new FileStream( szFileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
  if ( !IsValid( pStream ) || !pStream->IsOk() )
    return;

  pStream->Write( (const byte*)md4.code, 16 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char * argv[] )
{
#if defined( NV_WIN_PLATFORM )
  vector<wstring> params;
  wstring cmdLine = GetCommandLineW();
  ParseCommandLine( &params, cmdLine );

  if ( params.size() < 3 )
    return - 1;

  string inputFileName = NStr::ToMBCS( params[1] );
  string outputFileName = NStr::ToMBCS( params[2] );
#elif defined( NV_LINUX_PLATFORM )
  if ( argc < 3 ) { return - 1; }

  string inputFileName( argv[ 1 ] );
  string outputFileName( argv[ 2 ] );
#endif

  NStr::TrimBoth( inputFileName, "\"" );
  NStr::TrimBoth( outputFileName, "\"" );

  math::MD4 md4 = GenerateMD5( inputFileName );
  SaveMD4( md4, outputFileName );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
