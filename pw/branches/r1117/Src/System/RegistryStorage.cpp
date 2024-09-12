#include "stdafx.h"
#include "RegistryStorage.h"
#include <shlwapi.h>

namespace registry {

Storage::Storage( const char * productName, bool currentUser, const char * companyName ) :
hMain( NULL )
{
  if ( !companyName )
    companyName = TEXT( "Nival Network" );

  HKEY hparent = currentUser ? HKEY_CURRENT_USER : HKEY_LOCAL_MACHINE;

  const size_t BUF_SZ = 1024;
  char szName[BUF_SZ] = TEXT( "SOFTWARE\\" );
  
  NI_VERIFY( strlen(szName) + strlen( productName ) + strlen( companyName ) + 16 < BUF_SZ, "Out of buffer", return );
  StrCat( szName, companyName );
  StrCat( szName, "\\" );
  StrCat( szName, productName );

  LSTATUS code = ::RegCreateKeyEx( hparent, szName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL, &hMain, NULL );
  NI_VERIFY( code == ERROR_SUCCESS, "Could not open registry key", return );
}

Storage::Storage( ) : hMain( NULL )
{
  LSTATUS code = ::RegOpenCurrentUser(KEY_QUERY_VALUE, &hMain);
  NI_VERIFY( code == ERROR_SUCCESS, "Could not open registry key", return );
}


Storage::~Storage()
{
  if ( hMain )
    ::RegCloseKey( hMain );
}



bool Storage::StoreDword( const char * valueName, DWORD value )
{
  NI_VERIFY( hMain, "Storage is not initialized", return false );

  LSTATUS code = ::RegSetValueEx( hMain, valueName, 0, REG_DWORD, (BYTE *)&value, sizeof( value ) );
  NI_VERIFY( code == ERROR_SUCCESS, "Error writing DWORD to registry", return false );
  return true;
}



bool Storage::ReadDwordEx( const char * valueName, DWORD & value, bool doAsserts )
{
  NI_VERIFY( hMain, "Storage is not initialized", return false );

  DWORD type = 0;
  LSTATUS code = ::RegQueryValueEx( hMain, valueName, 0, &type, NULL, NULL );
  if ( ( code != ERROR_SUCCESS ) || ( type != REG_DWORD ) )
  {
    if ( doAsserts )
      NI_ALWAYS_ASSERT( "Error reading DWORD type from registry" );
    return false;
  }

  DWORD size = sizeof( value );
  code = ::RegQueryValueEx( hMain, valueName, 0, NULL, (LPBYTE)&value, &size );
  if ( ( code != ERROR_SUCCESS ) || ( type != REG_DWORD ) )
  {
    if ( doAsserts )
      NI_ALWAYS_ASSERT( "Error reading DWORD type from registry" );
    return false;
  }

  return true;
}



bool Storage::StoreString( const char * valueName, const char * value )
{
  NI_VERIFY( hMain, "Storage is not initialized", return false );

  LSTATUS code = ::RegSetValueEx( hMain, valueName, 0, REG_SZ, (BYTE *)value, strlen( value ) + 1 );
  NI_VERIFY( code == ERROR_SUCCESS, "Error writing DWORD to registry", return false );
  return true;
}



bool Storage::ReadStringEx( const char * valueName, string & value, bool doAsserts )
{
  NI_VERIFY( hMain, "Storage is not initialized", return false );

  DWORD type = 0;
  DWORD size = 0;
  LSTATUS code = ::RegQueryValueEx( hMain, valueName, 0, &type, NULL, &size );
  if ( ( code != ERROR_SUCCESS ) || ( type != REG_SZ ) || ( size < 1 ) )
  {
    if ( doAsserts )
      NI_ALWAYS_ASSERT( "Error reading string type from registry" );
    return false;
  }

  value.resize( size - 1 );

  code = ::RegQueryValueEx( hMain, valueName, 0, NULL, (LPBYTE)value.c_str(), &size );
  if ( ( code != ERROR_SUCCESS ) || ( type != REG_SZ ) )
  {
    if ( doAsserts )
      NI_ALWAYS_ASSERT( "Error reading string type from registry" );
    return false;
  }
  return true;
}



bool Storage::StoreBinary( const char * valueName, const vector<ni_detail::Byte> & data )
{
  NI_VERIFY( hMain, "Storage is not initialized", return false );

  const BYTE * dataPtr = data.empty() ? NULL : &data[0];
  LSTATUS code = ::RegSetValueEx( hMain, valueName, 0, REG_BINARY, dataPtr, data.size() );
  NI_VERIFY( code == ERROR_SUCCESS, "Error writing blob to registry", return false );
  return true;
}



bool Storage::ReadBinaryEx( const char * valueName, vector<ni_detail::Byte> & buffer, bool doAsserts )
{
  NI_VERIFY( hMain, "Storage is not initialized", return false );

  DWORD type = 0;
  DWORD size = 0;
  LSTATUS code = ::RegQueryValueEx( hMain, valueName, 0, &type, NULL, &size );
  if ( ( code != ERROR_SUCCESS ) || ( type != REG_BINARY ) )
  {
    if ( doAsserts )
      NI_ALWAYS_ASSERT( "Error reading blob type from registry" );
    return false;
  }

  buffer.resize( size );

  BYTE * dataPtr = buffer.empty() ? NULL : &buffer[0];
  code = ::RegQueryValueEx( hMain, valueName, 0, NULL, dataPtr, &size );
  if ( ( code != ERROR_SUCCESS ) || ( type != REG_BINARY ) )
  {
    if ( doAsserts )
      NI_ALWAYS_ASSERT( "Error reading string type from registry" );
    return false;
  }
  return true;
}

bool Storage::OpenSubKey(const char* path, PHKEY hSecond, bool readOnly = true, bool createKey = false)
{
  DWORD dwDisposition = createKey ? REG_CREATED_NEW_KEY : REG_OPENED_EXISTING_KEY ;
  REGSAM samDesired = readOnly ? KEY_READ : KEY_READ | KEY_WRITE ;

  LSTATUS code = ::RegCreateKeyEx(hMain, path, 0, NULL, REG_OPTION_NON_VOLATILE, samDesired, NULL, hSecond, &dwDisposition);
  NI_VERIFY( code == ERROR_SUCCESS, "Could not open registry key", return false);

  return true;
}

void Storage::CloseKey(PHKEY key)
{
  if (key)
    ::RegCloseKey(*key);
}


} //namespace registry
