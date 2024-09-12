#include "stdafx.h"
#include "CmdLineLite.h"



CmdLineLite & CmdLineLite::Instance()
{
  static CmdLineLite inst;
  return inst;
}



void CmdLineLite::Init(int nArgsCount, const char * const ppszArgs[])
{
  NI_ASSERT( nArgsCount > 0, "" );
  m_arArgs.clear();
  m_arArgs.reserve( nArgsCount - 1 );
  for( int i = 1; i < nArgsCount; ++i )
    m_arArgs.push_back( ppszArgs[i] );
}




void CmdLineLite::Init(const char * pszCmdLn)
{
  m_arArgs.clear();
  m_arArgs.reserve(16);

  const char * pszSeps = " \t";
  while ( true )
  {
    //skip spaces:
    pszCmdLn += strspn( pszCmdLn, pszSeps );
    if( !*pszCmdLn )
      break;

    //find end of the line
    bool bQuoted = ( *pszCmdLn == '"' );
    int arg_len = bQuoted ? strcspn( ++pszCmdLn, "\"" ) : strcspn( pszCmdLn, pszSeps );
    m_arArgs.push_back( string( pszCmdLn, arg_len ) );

    if( pszCmdLn[arg_len] == 0 )
      break;
    else
      pszCmdLn += arg_len + 1;
  }
}




void CmdLineLite::InitFromWin32()
{
#ifndef NI_PLATF_LINUX
  Init( GetCommandLine() );
#else
  // TODO: port to linux
#endif

  //let's remove module's name from cmd line
  if( !m_arArgs.empty() )
    m_arArgs.erase( m_arArgs.begin() );
}




const char * CmdLineLite::Argument( int uIndex )
{
  return uIndex < m_arArgs.size() ? m_arArgs[uIndex].c_str() : NULL;
}




bool CmdLineLite::IsKeyDefined( const char * pszKey ) const
{
  for( int i = 0; i < m_arArgs.size(); ++i )
    if( !NStr::ICmp( m_arArgs[i].c_str(), pszKey ) )
      return true;
  return false;
}




const char * CmdLineLite::GetStringKey(const char * pszKey, const char * pszDefault) const
{
  for( int i = 0; i < m_arArgs.size(); ++i )
    if( !NStr::ICmp( m_arArgs[i].c_str(), pszKey ) )
      if ( i + 1 < m_arArgs.size() )
        if ( ItIsArg( i + 1 ) )
          return m_arArgs[i + 1].c_str();

  return pszDefault;
}




#pragma warning( disable : 4996 ) //warning C4996: 'sscanf': This function or variable may be unsafe

int CmdLineLite::GetIntKey(const char * pszKey, int nDefault) const
{
  const char * pszStr = GetStringKey( pszKey );
  if( !pszStr )
    return nDefault;
  
  int nVal = nDefault;
  int end = 0;
  if( sscanf( pszStr, "%i%n", &nVal, &end ) == 1 )
    if ( end == (int)strlen( pszStr ) )
      return nVal;

  return nDefault;
}



float CmdLineLite::GetFloatKey( const char * pszKey, float fDefault ) const
{
  const char * pszStr = GetStringKey( pszKey );
  if( !pszStr )
    return fDefault;

  float fVal = fDefault;
  int end = 0;
  if( sscanf( pszStr, "%f%n", &fVal, &end ) == 1 )
    if ( end == (int)strlen( pszStr ) )
      return fVal;

  return fDefault;
}



int CmdLineLite::GetStringKeys( vector<string> & result, const char * pszKey, const char * pszDefault ) const
{
  result.clear();

  for( int i = 0; i < m_arArgs.size(); ++i )
    if( !NStr::ICmp( m_arArgs[i].c_str(), pszKey ) )
      if ( i + 1 < m_arArgs.size() )
        if ( ItIsArg( i + 1 ) ) {
          result.push_back( m_arArgs[i + 1] );
          ++i;
        }

  return result.size();
}



int CmdLineLite::GetIntKeys( vector<int> & result, const char * pszKey, int nDefault ) const
{
  result.clear();

  for( int i = 0; i < m_arArgs.size(); ++i )
    if( !NStr::ICmp( m_arArgs[i].c_str(), pszKey ) )
      if ( i + 1 < m_arArgs.size() )
        if ( ItIsArg( i + 1 ) ) {
          int nVal = nDefault;
          if ( sscanf( m_arArgs[i + 1].c_str(), "%i", &nVal ) == 1 ) {
            result.push_back( nVal );
            ++i;
          }
        }

  return result.size();
}



int CmdLineLite::GetMultipleStringKeys( const char * key, TMultiStringArgs & result ) const
{
  for( int i = 0; i < m_arArgs.size(); )
    if( !NStr::ICmp( m_arArgs[i].c_str(), key ) )
    {
      ++i;

      result.push_back( TStringList() );
      TStringList & item = result.back();

      for ( ; i < m_arArgs.size(); ++i )
      {
        if ( !ItIsArg( i ) )
          break;
        item.push_back( m_arArgs[i] );
      }
    }
    else
      ++i;

  return result.size();
}



int CmdLineLite::GetMultipleIntKeys( const char * key, TMultiIntArgs & result ) const
{
  for( int i = 0; i < m_arArgs.size(); 0)
    if( !NStr::ICmp( m_arArgs[i].c_str(), key ) )
    {
      ++i;

      result.push_back( TIntList() );
      TIntList & item = result.back();

      for ( ; i < m_arArgs.size(); ++i )
      {
        if ( !ItIsArg( i ) )
          break;

        int nVal = 0;
        if( sscanf( m_arArgs[i].c_str(), "%i", &nVal ) != 1 )
          break;

        item.push_back( nVal );
      }
    }
    else
      ++i;

  return result.size();
}



bool CmdLineLite::ItIsArg( int index ) const
{
  NI_VERIFY( index >= 0 && index < m_arArgs.size(), "", return false )
  const char * arg = m_arArgs[index].c_str();
  return arg[0] && ( arg[0] != '-' );
}
