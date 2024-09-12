//--------------------------------------------------------------------------------------
// File: ConfigDatabase.cpp
//
// Implementation of configuration database object.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// P.S.: Я к этому мусору отношения не имею. Не виноватый я. Аслан.
//--------------------------------------------------------------------------------------
#include "StdAfx.h"
#include <tchar.h>
//#include "dxut.h"
#pragma warning(disable: 4995)
//#include <windows.h>
//#include <stdio.h>
//#include <map>
#include "ConfigDatabase.h"
//#define INITGUID
//#include <guiddef.h>
//#include <dsound.h>
//#include <dsconf.h>
#pragma warning(default: 4995; disable: 4245)


DWORD GetHexDigits( WCHAR* ptr )
{
  DWORD val = 0;
  while( ( *ptr >= L'0' && *ptr <= L'9' ) || ( *ptr >= L'a' && *ptr <= L'f' ) )
  {
    val *= 16;
    if( *ptr >= L'0' && *ptr <= L'9' )
      val += *ptr - L'0';
    else
      val += *ptr - L'a' + 10;

    ++ptr;
  };
  return val;
}


void ConvertToLower( WCHAR* psz )
{
  while( *psz != L'\0' )
  {
    if( *psz >= L'A' && *psz <= L'Z' )
      *psz += ( L'a' - L'A' );
    ++psz;
  }
}


//HRESULT InitSoundInformation( REFGUID DsoundGuid, SOUND_DEVICE* pSndDev )
//{
//    OSVERSIONINFO vi;
//    vi.dwOSVersionInfoSize = sizeof( vi );
//    ::GetVersionEx( &vi );
//
//    // Obtain the DirectSoundPrivate interface
//
//    typedef HRESULT ( STDAPICALLTYPE *LPFNDLLGETCLASSOBJECT )( REFCLSID, REFIID, LPVOID * );
//
//    HINSTANCE hLibDsound = NULL;
//    LPFNGETCLASSOBJECT pfnDllGetClassObject = NULL;
//    LPCLASSFACTORY pClassFactory = NULL;
//    LPKSPROPERTYSET pKsPropertySet = NULL;
//    HRESULT hr = S_OK;
//    DWORD cDevices = 0;
//    DWORD dwDevNode = 0;
//    WCHAR wszInterface[512] = L"";
//    WCHAR wszModule[MAX_PATH] = L"";
//
//    // Load dsound.dll
//    hLibDsound = LoadLibraryW( L"dsound.dll" );
//
//    if( hLibDsound )
//    {
//        // Find DllGetClassObject
//        pfnDllGetClassObject = ( LPFNDLLGETCLASSOBJECT )GetProcAddress( hLibDsound, "DllGetClassObject" );
//
//        if( pfnDllGetClassObject )
//        {
//            // Create a class factory object
//            hr = pfnDllGetClassObject( CLSID_DirectSoundPrivate, IID_IClassFactory, ( LPVOID* )&pClassFactory );
//
//            // Create the DirectSoundPrivate object and query for an IKsPropertySet interface
//            if( SUCCEEDED( hr ) )
//            {
//                hr = pClassFactory->CreateInstance( NULL, IID_IKsPropertySet, ( LPVOID* )&pKsPropertySet );
//
//                if( pKsPropertySet )
//                {
//                    // We have the interface.  Query DirectSound6 description.
//
//                    DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_1_DATA Basic1;
//                    PDSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_1_DATA pData1 = NULL;
//                    ULONG cbData;
//
//                    Basic1.DeviceId = DsoundGuid;
//
//                    hr = pKsPropertySet->Get( DSPROPSETID_DirectSoundDevice,
//                                              DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_1,
//                                              NULL,
//                                              0,
//                                              &Basic1,
//                                              sizeof( Basic1 ),
//                                              &cbData );
//
//                    if( SUCCEEDED( hr ) )
//                    {
//                        pData1 = ( PDSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_1_DATA )malloc( cbData );
//
//                        if( !pData1 )
//                        {
//                            hr = DSERR_OUTOFMEMORY;
//                        }
//                    }
//
//                    if( SUCCEEDED( hr ) )
//                    {
//                        ZeroMemory( pData1, cbData );
//
//                        pData1->DeviceId = DsoundGuid;
//
//                        hr = pKsPropertySet->Get( DSPROPSETID_DirectSoundDevice,
//                                                  DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_1,
//                                                  NULL,
//                                                  0,
//                                                  pData1,
//                                                  cbData,
//                                                  NULL );
//
//                        // Fill in the info.
//                        dwDevNode = pData1->Devnode;
//                    }
//
//                    // Free device description memory
//                    if( pData1 )
//                        ::free( pData1 );
//
//                    // Query the DirectSound7 description
//
//                    DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_W_DATA Basic;
//                    PDSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_W_DATA pDataW = NULL;
//
//                    Basic.DeviceId = DsoundGuid;
//
//                    hr = pKsPropertySet->Get( DSPROPSETID_DirectSoundDevice,
//                                              DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_W,
//                                              NULL,
//                                              0,
//                                              &Basic,
//                                              sizeof( Basic ),
//                                              &cbData );
//
//                    if( SUCCEEDED( hr ) )
//                    {
//                        pDataW = ( PDSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_W_DATA )malloc( cbData );
//
//                        if( !pDataW )
//                        {
//                            hr = DSERR_OUTOFMEMORY;
//                        }
//                    }
//
//                    if( SUCCEEDED( hr ) )
//                    {
//                        ZeroMemory( pDataW, cbData );
//
//                        pDataW->DeviceId = DsoundGuid;
//
//                        hr = pKsPropertySet->Get( DSPROPSETID_DirectSoundDevice,
//                                                  DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_W,
//                                                  NULL,
//                                                  0,
//                                                  pDataW,
//                                                  cbData,
//                                                  NULL );
//
//                        // Fill in the info.
//                        wcscpy_s( pSndDev->name, 64, pDataW->Description );
//                        wcscpy_s( wszModule, MAX_PATH, pDataW->Module );
//
//                        // Obtain the interface path to extract IDs.
//                        if( VER_PLATFORM_WIN32_WINDOWS == vi.dwPlatformId )
//                        {
//                            // Win9x does not return interface path.  It needs to
//                            // be fetched from registry.
//
//                            HKEY hKey = NULL;
//                            HKEY hDevKey;
//                            DWORD iKey = 0;
//
//                            // On Win9x, we have the DevNode, so find the device in the registry
//                            // with the matching DevNode and gather more info there.
//                            if( ERROR_SUCCESS == ::RegOpenKeyEx( HKEY_LOCAL_MACHINE,
//                                                                 L"System\\CurrentControlSet\\control\\MediaResources\\wave",
//                                                                 0, KEY_READ, &hKey ) )
//                            {
//                                while( true )
//                                {
//                                    WCHAR wszDevKey[MAX_PATH];
//
//                                    if( ERROR_SUCCESS != ::RegEnumKey( hKey, iKey, wszDevKey, MAX_PATH ) )
//                                        break;
//
//                                    if( ERROR_SUCCESS == ::RegOpenKeyEx( hKey, wszDevKey, 0, KEY_READ, &hDevKey ) )
//                                    {
//                                        DWORD dwDevnode;
//                                        DWORD cb;
//                                        DWORD dwType;
//
//                                        cb = sizeof( dwDevnode );
//                                        if( ERROR_SUCCESS == ::RegQueryValueEx( hDevKey, L"DevNode",
//                                                                                NULL, &dwType,
//                                                                                ( BYTE* )&dwDevnode, &cb ) )
//                                        {
//                                            if( dwDevnode == dwDevNode )
//                                            {
//                                                // Found match
//                                                cb = sizeof( wszInterface );
//                                                ::RegQueryValueEx( hDevKey, L"DeviceID",
//                                                                   NULL, &dwType, ( LPBYTE )wszInterface, &cb );
//
//                                                // Occasionally the driver name that DirectSoundEnumerate spits out
//                                                // is garbage.  If that's the case, use the driver name listed here instead.
//                                                if( lstrlenW( wszModule ) < 4 )
//                                                {
//                                                    cb = sizeof( wszModule );
//                                                    ::RegQueryValueEx( hDevKey, L"Driver",
//                                                                       NULL, &dwType, ( LPBYTE )wszModule, &cb );
//                                                }
//                                            }
//                                        }
//                                        ::RegCloseKey( hDevKey );
//                                    }
//                                    iKey++;
//                                }
//                                ::RegCloseKey( hKey );
//                            }
//                        }
//                        else
//                        {
//                            // Interface string is available on NT
//                            wcscpy_s( wszInterface, 512, pDataW->Interface );
//                        }
//                    }
//
//                    // Free device description memory
//                    if( pDataW )
//                        ::free( pDataW );
//
//                    // Release the IKsPropertySet interface
//                    SAFE_RELEASE( pKsPropertySet );
//
//                    // Extract Product/Vendor/Revision/Subsystem IDs from interface string
//                    ConvertToLower( wszInterface );
//
//                    WCHAR* szPre = wcsstr( wszInterface, L"ven_" );
//                    if( szPre )
//                        pSndDev->VendorID = GetHexDigits( szPre + 4 );
//                    szPre = wcsstr( wszInterface, L"dev_" );
//                    if( szPre )
//                        pSndDev->DeviceID = GetHexDigits( szPre + 4 );
//                    szPre = wcsstr( wszInterface, L"subsys_" );
//                    if( szPre )
//                        pSndDev->SubSysID = GetHexDigits( szPre + 7 );
//                    szPre = wcsstr( wszInterface, L"rev_" );
//                    if( szPre )
//                        pSndDev->Revision = GetHexDigits( szPre + 4 );
//
//                    // Obtain driver version.  Try system dir first, then
//                    // try systemDir\drivers.
//                    WCHAR wszDriverPath[MAX_PATH];
//                    ::GetSystemDirectory( wszDriverPath, MAX_PATH );
//                    wcscat_s( wszDriverPath, MAX_PATH, L"\\" );
//                    wcscat_s( wszDriverPath, MAX_PATH, wszModule );
//
//                    // If the file does not exist, use %SystemDir%\drivers.
//                    if( INVALID_FILE_ATTRIBUTES == GetFileAttributes( wszDriverPath ) )
//                    {
//                        ::GetSystemDirectory( wszDriverPath, MAX_PATH );
//                        wcscat_s( wszDriverPath, MAX_PATH, L"\\drivers\\" );
//                        wcscat_s( wszDriverPath, MAX_PATH, wszModule );
//                    }
//
//                    DWORD dwVerHandle;
//                    DWORD dwBufferSize = GetFileVersionInfoSize( wszDriverPath, &dwVerHandle );
//                    LPVOID pBuffer = ::malloc( dwBufferSize );
//                    VS_FIXEDFILEINFO* pVer;
//                    UINT uVerSize;
//                    if( dwBufferSize && pBuffer )
//                    {
//                        if( GetFileVersionInfo( wszDriverPath, dwVerHandle, dwBufferSize, pBuffer ) &&
//                            VerQueryValue( pBuffer, L"\\", ( LPVOID* )&pVer, &uVerSize ) )
//                        {
//                            // Retrieve version number
//                            pSndDev->DriverVersionLowPart = pVer->dwFileVersionLS;
//                            pSndDev->DriverVersionHighPart = pVer->dwFileVersionMS;
//                        }
//                    }
//
//                    ::free( pBuffer );
//                }
//
//                // Release the class factory
//                SAFE_RELEASE( pClassFactory );
//            }
//        }
//
//        FreeLibrary( hLibDsound );
//    }
//
//    return hr;
//}


class CConfigDatabase;

const char k_KeywordDisplayVendor[] = "displayvendor";
const char k_KeywordAudioVendor[] = "audiovendor";
const char k_KeywordApplyToAll[] = "applytoall";
const char k_KeywordRequirements[] = "Requirements";
const char k_KeywordPropertySet[] = "propertyset";
const char k_KeywordIf[] = "if";
const char k_KeywordEndif[] = "endif";
const char k_KeywordRam[] = "ram";
const char k_KeywordVideoram[] = "videoram";
const char k_KeywordSubsysid[] = "subsysid";
const char k_KeywordRevision[] = "revision";
const char k_KeywordDriver[] = "driver";
const char k_KeywordGuid[] = "guid";
const char k_KeywordOs[] = "os";
const char k_KeywordWin95[] = "win95";
const char k_KeywordWin98[] = "win98";
const char k_KeywordWin98se[] = "win98se";
const char k_KeywordWinme[] = "winme";
const char k_KeywordWin2k[] = "win2k";
const char k_KeywordWinxp[] = "winxp";
const char k_KeywordWin2003[] = "win2003";
const char k_KeywordBreak[] = "break";
const char k_KeywordUnknown[] = "unknown";
const char k_KeywordCaps[] = "Caps";
const char k_KeywordCaps2[] = "Caps2";
const char k_KeywordCaps3[] = "Caps3";
const char k_KeywordPresentationIntervals[] = "PresentationIntervals";
const char k_KeywordCursorCaps[] = "CursorCaps";
const char k_KeywordDevCaps[] = "DevCaps";
const char k_KeywordPrimitiveMiscCaps[] = "PrimitiveMiscCaps";
const char k_KeywordRasterCaps[] = "RasterCaps";
const char k_KeywordZCmpCaps[] = "ZCmpCaps";
const char k_KeywordSrcBlendCaps[] = "SrcBlendCaps";
const char k_KeywordDestBlendCaps[] = "DestBlendCaps";
const char k_KeywordAlphaCmpCaps[] = "AlphaCmpCaps";
const char k_KeywordShadeCaps[] = "ShadeCaps";
const char k_KeywordTextureCaps[] = "TextureCaps";
const char k_KeywordTextureFilterCaps[] = "TextureFilterCaps";
const char k_KeywordCubeTextureFilterCaps[] = "CubeTextureFilterCaps";
const char k_KeywordVolumeTextureFilterCaps[] = "VolumeTextureFilterCaps";
const char k_KeywordTextureAddressCaps[] = "TextureAddressCaps";
const char k_KeywordVolumeTextureAddressCaps[] = "VolumeTextureAddressCaps";
const char k_KeywordLineCaps[] = "LineCaps";
const char k_KeywordMaxTextureWidth[] = "MaxTextureWidth";
const char k_KeywordMaxTextureHeight[] = "MaxTextureHeight";
const char k_KeywordMaxVolumeExtent[] = "MaxVolumeExtent";
const char k_KeywordMaxTextureRepeat[] = "MaxTextureRepeat";
const char k_KeywordMaxTextureAspectRatio[] = "MaxTextureAspectRatio";
const char k_KeywordMaxAnisotropy[] = "MaxAnisotropy";
const char k_KeywordStencilCaps[] = "StencilCaps";
const char k_KeywordFVFCaps[] = "FVFCaps";
const char k_KeywordTextureOpCaps[] = "TextureOpCaps";
const char k_KeywordMaxTextureBlendStages[] = "MaxTextureBlendStages";
const char k_KeywordMaxSimultaneousTextures[] = "MaxSimultaneousTextures";
const char k_KeywordVertexProcessingCaps[] = "VertexProcessingCaps";
const char k_KeywordMaxActiveLights[] = "MaxActiveLights";
const char k_KeywordMaxUserClipPlanes[] = "MaxUserClipPlanes";
const char k_KeywordMaxVertexBlendMatrices[] = "MaxVertexBlendMatrices";
const char k_KeywordMaxVertexBlendMatrixIndex[] = "MaxVertexBlendMatrixIndex";
const char k_KeywordMaxPrimitiveCount[] = "MaxPrimitiveCount";
const char k_KeywordMaxVertexIndex[] = "MaxVertexIndex";
const char k_KeywordMaxStreams[] = "MaxStreams";
const char k_KeywordMaxStreamStride[] = "MaxStreamStride";
const char k_KeywordVertexShaderVersion[] = "VertexShaderVersion";
const char k_KeywordMaxVertexShaderConst[] = "MaxVertexShaderConst";
const char k_KeywordPixelShaderVersion[] = "PixelShaderVersion";
const char k_KeywordCPUSpeed[] = "cpuspeed";
const char k_KeywordOverallGraphicDetail[] = "OverallGraphicDetail";
const char k_KeywordMaxOverallGraphicDetail[] = "MaxOverallGraphicDetail";


//------------------------------------------------------------------------------
//
// CPropertySet
//
//------------------------------------------------------------------------------
struct CPropertySet
{
private:
  vector <StringPair> m_Properties;
  const CConfigDatabase& m_Owner;
  CPropertySet& operator =(const CPropertySet&);
public:
  CPropertySet( const CConfigDatabase& );
  void    Set( const char* Property, const char* Value );
  bool    Get( const char* Property, char* Value, int cbValue );
  const vector <StringPair>& GetProperties() const
  {
    return m_Properties;
  }
};


CPropertySet::CPropertySet( const CConfigDatabase& owner ) : m_Owner( owner )
{
}


void CPropertySet::Set( const char* Property, const char* Value )
{
  vector <StringPair>::iterator it, end;
  it = m_Properties.begin();
  end = m_Properties.end();
  while( it != end )
  {
    StringPair& pr = *it;
    if( 0 == _stricmp( pr.first.c_str(), Property ) )
    {
      pr.second = Value;
      return;
    }
    ++it;
  }
  m_Properties.push_back( StringPair( string( Property ), string( Value ) ) );
}


bool CPropertySet::Get( const char* Property, char* Value, int cbValue )
{
  vector <StringPair>::iterator it, end;
  it = m_Properties.begin();
  end = m_Properties.end();
  while( it != end )
  {
    StringPair& pr = *it;
    if( 0 == _stricmp( pr.first.c_str(), Property ) )
    {
      strcpy_s( Value, cbValue, pr.second.c_str() );
      return true;
    }
    ++it;
  }
  return false;
}


//--------------------------------------------------------------------------------
//
// CConfigDatabase
//
//---------------------------------------------------------------------------------
class CConfigDatabase : public IConfigDatabase
{
public:
  CConfigDatabase();
  ~CConfigDatabase();

  //
  // IConfigDatabase
  //
  bool Load(LPCTSTR FileName, const SOUND_DEVICE& soundDevice, const D3DADAPTER_IDENTIFIER9& DDid,
    const D3DCAPS9&, DWORD SystemMemory, DWORD VideoMemory, DWORD CPUSpeed);
  void Release() { delete this; };

  unsigned int GetDevicePropertyCount() const
  {
    return ( int )m_pDevice->GetProperties().size();
  }
  const char*  GetDeviceProperty(unsigned int i) const
  {
    return m_pDevice->GetProperties()[i].first.c_str();
  }
  const char* GetDeviceValue( unsigned int i ) const
  {
    return m_pDevice->GetProperties()[i].second.c_str();
  }

  unsigned int    GetRequirementsPropertyCount() const
  {
    return ( int )m_pRequirements->GetProperties().size();
  }
  const char* GetRequirementsProperty( unsigned int i ) const
  {
    return m_pRequirements->GetProperties()[i].first.c_str();
  }
  const char* GetRequirementsValue( unsigned int i ) const
  {
    return m_pRequirements->GetProperties()[i].second.c_str();
  }

  const vector <StringPair>& GetAggregateProperties() const { return m_pDevice->GetProperties(); }
  const vector <StringPair>* GetNamedProperties( const char* ) const;

  const char* GetGfxDeviceString()   const { return m_DeviceString.c_str(); }
  const char* GetGfxVendorString()   const { return m_VendorString.c_str(); }
  const char* GetSoundDeviceString() const { return m_SoundDeviceString.c_str(); }
  const char* GetSoundVendorString() const { return m_SoundVendorString.c_str(); }

  bool IsError() const { return m_fError; }
  const char* GetErrorString() const { return m_ErrorString.c_str(); }

private:

  // Variables use to read in file
  char* m_pchFile;                            // Pointer to start of file
  char* m_pchCurrent;                         // Current file pointer
  char* m_pchEndOfFile;                       // Pointer to the end of file
  char* m_pchCurrentLine;                     // Pointer to start of this line
  DWORD m_LineNumber;                         // Line Number

  CPropertySet* m_pDevice;
  CPropertySet* m_pRequirements;

  bool m_fError;                              // Errors adding strings
  string m_ErrorString;

  string m_DeviceString;
  string m_VendorString;
  string m_SoundDeviceString;
  string m_SoundVendorString;

  DWORD m_CPUSpeed;                           // CPU Speed passed in
  DWORD m_SystemMemory;                       // System memory passed in
  DWORD m_VideoMemory;                        // Video memory passed in
  D3DADAPTER_IDENTIFIER9 m_AdapterId;         // DDiD passed in
  D3DCAPS9 m_caps;

  SOUND_DEVICE m_SoundDevice;

  map <string, CPropertySet*> m_mapNameToPropertySet;
  map <string, CPropertySet*> m_mapOGDToPropertySet; //OGD==OverallGraphicDetail

  void            SkipToNextLine();
  void            SkipSpace();
  void            SyntaxError( char* ErrorText );
  char* AddFlag( CPropertySet* pPropertySet );
  DWORD           GetDigit();
  DWORD           GetNumber();
  char* GetString();
  DWORD           Get4Digits();
  DWORD           sGet4Digits();
  char* GetCondition();
  bool            DoDisplayVendorAndDevice();
  bool            DoSoundVendorAndDevice();
  bool            DoPropertySet( CPropertySet* pPropertySet );
  bool            DoPropertySets();
  bool            DoRequirements();
  void            ApplyPropertySet( CPropertySet* pSetDst, CPropertySet* pSetSrc );
  bool            DoPreApplyToAll();
  bool            DoPostApplyToAll();
  bool            NextStringIs( const char* psz );
};


const vector <StringPair>* CConfigDatabase::GetNamedProperties( const char* pszName ) const
{
  string strName( pszName );
  map <string, CPropertySet*>::const_iterator it;
  it = m_mapNameToPropertySet.find( strName );
  if( it == m_mapNameToPropertySet.end() )
  {
    return NULL;
  }
  CPropertySet* pSet = ( *it ).second;
  return &pSet->GetProperties();
}


//
// Skip to start of next line
//
void CConfigDatabase::SkipToNextLine()
{
  do
  {
    m_pchCurrent++;
  } while( *( m_pchCurrent - 1 ) != 13 && m_pchCurrent < m_pchEndOfFile );

  if( m_pchCurrent < m_pchEndOfFile && *m_pchCurrent == 10 )
  {
    m_pchCurrent++;
  }

  m_pchCurrentLine = m_pchCurrent;
  m_LineNumber++;
}


//
// Skip over blank spaces
//
void CConfigDatabase::SkipSpace()
{
  while( *m_pchCurrent == ' ' || *m_pchCurrent == 9 )
    m_pchCurrent++;
}


//
// Generic syntax error
//
void CConfigDatabase::SyntaxError( char* ErrorText )
{
  if( !m_fError )
  {
    char tempBuffer[40];
    char* dest = tempBuffer;
    char* source = m_pchCurrentLine;
    while( *source != 13 && dest != &tempBuffer[36] )
    {
      *dest++ = *source++;          // Copy current line into error buffer
    }
    if( dest == &tempBuffer[36] )
    {
      *dest++ = '.';
      *dest++ = '.';
      *dest++ = '.';
    }
    *dest = 0;

    const size_t k_cchBuffer = 256;
    char Buffer[k_cchBuffer];
    sprintf_s( Buffer, k_cchBuffer, "%s on line %d - '%s'", ErrorText, m_LineNumber, tempBuffer );
    Buffer[k_cchBuffer - 1] = 0;
    m_ErrorString = Buffer;
    m_fError = 1;
  }
}


//
// Return a hex digit -1=m_fError  and move pointer on
//
DWORD CConfigDatabase::GetDigit()
{
  DWORD result = DWORD(-1);

  if( *m_pchCurrent >= '0' && *m_pchCurrent <= '9' )
    result = DWORD(*m_pchCurrent++) - '0';
  else {
    if( *m_pchCurrent >= 'a' && *m_pchCurrent <= 'f' )
      result = DWORD(*m_pchCurrent++) - 'a' + 10;
    else {
      if( *m_pchCurrent >= 'A' && *m_pchCurrent <= 'F' )
        result = ( DWORD )( *m_pchCurrent++ ) - 'A' + 10;
    }
  }

  return result;
}


// A number is expected, get it - return -1 for error
DWORD CConfigDatabase::GetNumber()
{
  DWORD result;

  SkipSpace();

  if( *( WORD* )m_pchCurrent != 'x0' )
  {
    if( *m_pchCurrent >= '0' && *m_pchCurrent <= '9' )
    {
      // Decimal number
      result = GetDigit();

      if( result == -1 ) {
        SyntaxError( "Number expected" );
        return -1;
      }

      while( *m_pchCurrent >= '0' && *m_pchCurrent <= '9' )
      {
        DWORD tmp = GetDigit();
        if( tmp == -1 )
          break;

        if( result >= 16602069666338596456 )
        {
          SyntaxError( "Number too large" );
          return -1;
        }

        result = result * 10 + tmp;
      }

      SkipSpace();

      return result;

    }
    else
    {
      SyntaxError( "Number expected" );
      return -1;
    }
  }
  //
  // Hex number?
  //
  m_pchCurrent += 2;

  DWORD tmp = GetDigit();

  if( tmp == -1 )
  {
    SyntaxError( "Number expected" );
    return -1;
  }

  result = 0;

  DWORD hexcount = 0;
  do
  {
    if( hexcount >= 8 )
    {
      SyntaxError( "Number too large" );
      return -1;
    }

    result = result * 16 + tmp;
    ++hexcount;
    tmp = GetDigit();
  } while( tmp != -1 );

  SkipSpace();

  return result;
}


//
// A string is expected, get it - return 0 for error
//
char* CConfigDatabase::GetString()
{
  static char Buffer[256];

  SkipSpace();

  if( *m_pchCurrent++ != '"' )
  {
    SyntaxError( "Expecting """ );
    return 0;
  }

  char* dest = Buffer;

  while( *m_pchCurrent != '"' )
  {
    *dest++ = *m_pchCurrent++;

    if( dest > &Buffer[255] )
    {
      SyntaxError( "String too long" );
      return 0;
    }
  }

  *dest = 0;
  m_pchCurrent++;

  SkipSpace();

  return Buffer;
}


//
// Pointing at a flag = value line, add to the flags being returned
//
#define CHECK_LENGTH(end, start)   if(end == &start[254]) return "Flag too long";

char* CConfigDatabase::AddFlag( CPropertySet* pPropertySet )
{
  char Flag[256];
  char* dest = Flag;

  while( *m_pchCurrent != ' ' && *m_pchCurrent != '=' && *m_pchCurrent != 13 )
  {
    *dest++ = *m_pchCurrent++;
    CHECK_LENGTH(dest, Flag)
  }
  *dest = 0;

  SkipSpace();

  char Value[256];
  dest = Value;

  if( *m_pchCurrent != 13 )
  {
    if( *m_pchCurrent != '=' )
      return "flag = xxx expected";

    m_pchCurrent++;
    SkipSpace();

    if( *m_pchCurrent == '"' )
    {
      do {
        *dest++ = *m_pchCurrent++;
        CHECK_LENGTH(dest, Value)
      } while( *m_pchCurrent != '"' && *m_pchCurrent != 13 );

      if( *m_pchCurrent != '"' )
        return "Missing Quote";

      *dest++ = '"';
      CHECK_LENGTH(dest, Value)
    }
    else
    {
      while( *m_pchCurrent != ' ' && *m_pchCurrent != 13 )
      {
        *dest++ = *m_pchCurrent++;
        CHECK_LENGTH(dest, Value)
      }
    }
  }
  *dest = 0;

  pPropertySet->Set( Flag, Value );

  //  Check for OverallGraphicDetail. This is a special keyword. It is
  //  used to add this property set to another map.
  if( _stricmp( k_KeywordOverallGraphicDetail, Flag ) == 0 )
    m_mapOGDToPropertySet[Value] = pPropertySet;

  return 0;
}

#undef CHECK_LENGTH


//
// Return true if the character is not a alphanumeric
//
bool NotAscii( char Chr )
{
  if( Chr == '>' || Chr == '<' || Chr == '!' || Chr == '=' || Chr == ' ' || Chr == 13 || Chr == 9 )
    return true;

  return false;
}


//
// Returns the next 4 hex digits, -1 if any errors
//
DWORD CConfigDatabase::Get4Digits()
{
  DWORD result;

  DWORD tmp = GetDigit();

  if( tmp == -1 )
    return -1;

  result = tmp << 12;

  tmp = GetDigit();

  if( tmp == -1 )
    return -1;

  result |= tmp << 8;

  tmp = GetDigit();

  if( tmp == -1 )
    return -1;

  result |= tmp << 4;

  tmp = GetDigit();

  if( tmp == -1 )
    return -1;

  result |= tmp;

  return result;
}


//
// Returns the next 4 hex digits, -1 if any errors - SWAPPED version (for guids)
//
DWORD CConfigDatabase::sGet4Digits()
{
  DWORD temp = Get4Digits();

  if( temp == -1 )
    return temp;

  return ( ( temp & 0xff00 ) >> 8 ) + ( ( temp & 0xff ) << 8 );
}


bool CConfigDatabase::NextStringIs( const char* psz )
{
  int cch = ( int )strlen( psz );
  return ( 0 == _strnicmp( m_pchCurrent, psz, cch ) && NotAscii( m_pchCurrent[cch] ) );
}

//
// Evaluate an IF condition
//
// 1=True, 0=False, n=m_fError message
//
//
char* CConfigDatabase::GetCondition()
{
  DWORD Source = 0;
  DWORD Type = 0;       // 0=Value, 1=GUID, 2=Driver, 3=os
  DWORD Compare = 0;    // 0 ==,    1 !=,   2 >,   3 <,   4 >=,    5 <=

  SkipSpace();

  if( NextStringIs( k_KeywordCPUSpeed ) )
  {
    Source = m_CPUSpeed;
    m_pchCurrent += strlen( k_KeywordCPUSpeed );
  }
  else if( NextStringIs( k_KeywordRam ) )
  {
    Source = m_SystemMemory;
    m_pchCurrent += strlen( k_KeywordRam );
  }
  else if( NextStringIs( k_KeywordCaps ) )
  {
    Source = m_caps.Caps;
    m_pchCurrent += strlen( k_KeywordCaps );
  }
  else if( NextStringIs( k_KeywordCaps2 ) )
  {
    Source = m_caps.Caps2;
    m_pchCurrent += strlen( k_KeywordCaps2 );
  }
  else if( NextStringIs( k_KeywordCaps3 ) )
  {
    Source = m_caps.Caps3;
    m_pchCurrent += strlen( k_KeywordCaps3 );
  }
  else if( NextStringIs( k_KeywordPresentationIntervals ) )
  {
    Source = m_caps.PresentationIntervals;
    m_pchCurrent += strlen( k_KeywordPresentationIntervals );
  }
  else if( NextStringIs( k_KeywordCursorCaps ) )
  {
    Source = m_caps.CursorCaps;
    m_pchCurrent += strlen( k_KeywordCursorCaps );
  }
  else if( NextStringIs( k_KeywordDevCaps ) )
  {
    Source = m_caps.DevCaps;
    m_pchCurrent += strlen( k_KeywordDevCaps );
  }
  else if( NextStringIs( k_KeywordPrimitiveMiscCaps ) )
  {
    Source = m_caps.PrimitiveMiscCaps;
    m_pchCurrent += strlen( k_KeywordPrimitiveMiscCaps );
  }
  else if( NextStringIs( k_KeywordRasterCaps ) )
  {
    Source = m_caps.RasterCaps;
    m_pchCurrent += strlen( k_KeywordRasterCaps );
  }
  else if( NextStringIs( k_KeywordZCmpCaps ) )
  {
    Source = m_caps.ZCmpCaps;
    m_pchCurrent += strlen( k_KeywordZCmpCaps );
  }
  else if( NextStringIs( k_KeywordSrcBlendCaps ) )
  {
    Source = m_caps.SrcBlendCaps;
    m_pchCurrent += strlen( k_KeywordSrcBlendCaps );
  }
  else if( NextStringIs( k_KeywordDestBlendCaps ) )
  {
    Source = m_caps.DestBlendCaps;
    m_pchCurrent += strlen( k_KeywordDestBlendCaps );
  }
  else if( NextStringIs( k_KeywordAlphaCmpCaps ) )
  {
    Source = m_caps.AlphaCmpCaps;
    m_pchCurrent += strlen( k_KeywordAlphaCmpCaps );
  }
  else if( NextStringIs( k_KeywordShadeCaps ) )
  {
    Source = m_caps.ShadeCaps;
    m_pchCurrent += strlen( k_KeywordShadeCaps );
  }
  else if( NextStringIs( k_KeywordTextureCaps ) )
  {
    Source = m_caps.TextureCaps;
    m_pchCurrent += strlen( k_KeywordTextureCaps );
  }
  else if( NextStringIs( k_KeywordTextureFilterCaps ) )
  {
    Source = m_caps.TextureFilterCaps;
    m_pchCurrent += strlen( k_KeywordTextureFilterCaps );
  }
  else if( NextStringIs( k_KeywordCubeTextureFilterCaps ) )
  {
    Source = m_caps.CubeTextureFilterCaps;
    m_pchCurrent += strlen( k_KeywordCubeTextureFilterCaps );
  }
  else if( NextStringIs( k_KeywordVolumeTextureFilterCaps ) )
  {
    Source = m_caps.VolumeTextureFilterCaps;
    m_pchCurrent += strlen( k_KeywordVolumeTextureFilterCaps );
  }
  else if( NextStringIs( k_KeywordTextureAddressCaps ) )
  {
    Source = m_caps.TextureAddressCaps;
    m_pchCurrent += strlen( k_KeywordTextureAddressCaps );
  }
  else if( NextStringIs( k_KeywordVolumeTextureAddressCaps ) )
  {
    Source = m_caps.VolumeTextureAddressCaps;
    m_pchCurrent += strlen( k_KeywordVolumeTextureAddressCaps );
  }
  else if( NextStringIs( k_KeywordLineCaps ) )
  {
    Source = m_caps.LineCaps;
    m_pchCurrent += strlen( k_KeywordLineCaps );
  }
  else if( NextStringIs( k_KeywordMaxTextureWidth ) )
  {
    Source = m_caps.MaxTextureWidth;
    m_pchCurrent += strlen( k_KeywordMaxTextureWidth );
  }
  else if( NextStringIs( k_KeywordMaxVolumeExtent ) )
  {
    Source = m_caps.MaxVolumeExtent;
    m_pchCurrent += strlen( k_KeywordMaxVolumeExtent );
  }
  else if( NextStringIs( k_KeywordMaxTextureRepeat ) )
  {
    Source = m_caps.MaxTextureRepeat;
    m_pchCurrent += strlen( k_KeywordMaxTextureRepeat );
  }
  else if( NextStringIs( k_KeywordMaxTextureAspectRatio ) )
  {
    Source = m_caps.MaxTextureAspectRatio;
    m_pchCurrent += strlen( k_KeywordMaxTextureAspectRatio );
  }
  else if( NextStringIs( k_KeywordMaxAnisotropy ) )
  {
    Source = m_caps.MaxAnisotropy;
    m_pchCurrent += strlen( k_KeywordMaxAnisotropy );
  }
  else if( NextStringIs( k_KeywordStencilCaps ) )
  {
    Source = m_caps.StencilCaps;
    m_pchCurrent += strlen( k_KeywordStencilCaps );
  }
  else if( NextStringIs( k_KeywordFVFCaps ) )
  {
    Source = m_caps.FVFCaps;
    m_pchCurrent += strlen( k_KeywordFVFCaps );
  }
  else if( NextStringIs( k_KeywordTextureOpCaps ) )
  {
    Source = m_caps.TextureOpCaps;
    m_pchCurrent += strlen( k_KeywordTextureOpCaps );
  }
  else if( NextStringIs( k_KeywordMaxTextureBlendStages ) )
  {
    Source = m_caps.MaxTextureBlendStages;
    m_pchCurrent += strlen( k_KeywordMaxTextureBlendStages );
  }
  else if( NextStringIs( k_KeywordMaxSimultaneousTextures ) )
  {
    Source = m_caps.MaxSimultaneousTextures;
    m_pchCurrent += strlen( k_KeywordMaxSimultaneousTextures );
  }
  else if( NextStringIs( k_KeywordVertexProcessingCaps ) )
  {
    Source = m_caps.VertexProcessingCaps;
    m_pchCurrent += strlen( k_KeywordVertexProcessingCaps );
  }
  else if( NextStringIs( k_KeywordMaxActiveLights ) )
  {
    Source = m_caps.MaxActiveLights;
    m_pchCurrent += strlen( k_KeywordMaxActiveLights );
  }
  else if( NextStringIs( k_KeywordMaxUserClipPlanes ) )
  {
    Source = m_caps.MaxUserClipPlanes;
    m_pchCurrent += strlen( k_KeywordMaxUserClipPlanes );
  }
  else if( NextStringIs( k_KeywordMaxVertexBlendMatrices ) )
  {
    Source = m_caps.MaxVertexBlendMatrices;
    m_pchCurrent += strlen( k_KeywordMaxVertexBlendMatrices );
  }
  else if( NextStringIs( k_KeywordMaxVertexBlendMatrixIndex ) )
  {
    Source = m_caps.MaxVertexBlendMatrixIndex;
    m_pchCurrent += strlen( k_KeywordMaxVertexBlendMatrixIndex );
  }
  else if( NextStringIs( k_KeywordMaxPrimitiveCount ) )
  {
    Source = m_caps.MaxPrimitiveCount;
    m_pchCurrent += strlen( k_KeywordMaxPrimitiveCount );
  }
  else if( NextStringIs( k_KeywordMaxVertexIndex ) )
  {
    Source = m_caps.MaxVertexIndex;
    m_pchCurrent += strlen( k_KeywordMaxVertexIndex );
  }
  else if( NextStringIs( k_KeywordMaxStreams ) )
  {
    Source = m_caps.MaxStreams;
    m_pchCurrent += strlen( k_KeywordMaxStreams );
  }
  else if( NextStringIs( k_KeywordMaxStreamStride ) )
  {
    Source = m_caps.MaxStreamStride;
    m_pchCurrent += strlen( k_KeywordMaxStreamStride );
  }
  else if( NextStringIs( k_KeywordVertexShaderVersion ) )
  {
    Source = m_caps.VertexShaderVersion;
    m_pchCurrent += strlen( k_KeywordVertexShaderVersion );
  }
  else if( NextStringIs( k_KeywordMaxVertexShaderConst ) )
  {
    Source = m_caps.MaxVertexShaderConst;
    m_pchCurrent += strlen( k_KeywordMaxVertexShaderConst );
  }
  else if( NextStringIs( k_KeywordPixelShaderVersion ) )
  {
    Source = m_caps.PixelShaderVersion;
    m_pchCurrent += strlen( k_KeywordPixelShaderVersion );
  }
  else if( NextStringIs( k_KeywordVideoram ) )
  {
    Source = m_VideoMemory;
    m_pchCurrent += 8;
  }
  else if( NextStringIs( k_KeywordSubsysid ) )
  {
    Source = m_AdapterId.SubSysId;
    m_pchCurrent += 8;
  }
  else if( NextStringIs( k_KeywordRevision ) )
  {
    Source = m_AdapterId.Revision;
    m_pchCurrent += 8;
  }
  else if( NextStringIs( k_KeywordGuid ) )
  {
    Type = 1;
    m_pchCurrent += 4;
  }
  else if( NextStringIs( k_KeywordDriver ) )
  {
    Type = 2;
    m_pchCurrent += 6;
  }
  else if( NextStringIs( k_KeywordOs ) )
  {
    OSVERSIONINFO osinfo;
    osinfo.dwOSVersionInfoSize = sizeof( osinfo );
    GetVersionEx( &osinfo );

    if( osinfo.dwPlatformId == VER_PLATFORM_WIN32_NT )
    {
      if( osinfo.dwMajorVersion == 5 && osinfo.dwMinorVersion == 2 )
        Source = 6;  // Win2003
      else
      {
        Source = 5;
        if( osinfo.dwMajorVersion == 5 && osinfo.dwBuildNumber < 2600 )
          Source = 4;
      }
    }
    else
    {
      Source = 3;
      if( ( osinfo.dwBuildNumber & 0xffff ) <= 2222 )
        Source = 2;
      if( ( osinfo.dwBuildNumber & 0xffff ) <= 1998 )
        Source = 1;
      if( ( osinfo.dwBuildNumber & 0xffff ) <= 950 )
        Source = 0;
    }
    Type = 3;
    m_pchCurrent += 2;
  }
  else
  {
    return "Unknown value";
  }

  SkipSpace();

  if( *( WORD* )m_pchCurrent=='==' )
  {
    m_pchCurrent += 2;
    Compare = 0;
  }
  else
  {
    if( *( WORD* )m_pchCurrent=='=!' )
    {
      m_pchCurrent += 2;
      Compare = 1;
    }
    else
    {
      if( *( WORD* )m_pchCurrent=='><' )
      {
        m_pchCurrent += 2;
        Compare = 1;
      }
      else
      {
        if( *( WORD* )m_pchCurrent=='>=' )
        {
          m_pchCurrent += 2;
          Compare = 4;
        }
        else
        {
          if( *( WORD* )m_pchCurrent=='<=' )
          {
            m_pchCurrent += 2;
            Compare = 5;
          }
          else
          {
            if( *( WORD* )m_pchCurrent=='=<' )
            {
              m_pchCurrent += 2;
              Compare = 5;
            }
            else
            {
              if( *( WORD* )m_pchCurrent=='=>' )
              {
                m_pchCurrent += 2;
                Compare = 4;
              }
              else
              {
                if( *m_pchCurrent == '=' )
                {
                  m_pchCurrent += 1;
                  Compare = 0;
                }
                else
                {
                  if( *m_pchCurrent == '>' )
                  {
                    m_pchCurrent += 1;
                    Compare = 2;
                  }
                  else
                  {
                    if( *m_pchCurrent == '<' )
                    {
                      m_pchCurrent += 1;
                      Compare = 3;
                    }
                    else
                    {
                      if( *m_pchCurrent == '&' )
                      {
                        m_pchCurrent += 1;
                        Compare = 6;
                      }
                      else
                      {
                        return "Unknown operator";
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  SkipSpace();

  if( Type == 1 )                               // GUID  D7B71F83-6340-11CF-4C73-0100A7C2C935
  {
    if( Compare > 1 )
    {
      return "Only == or != allowed";
    }

    DWORD tempGUID[4];

    DWORD res = Get4Digits();

    if( res == -1 )
      return "Invalid GUID";

    DWORD res2 = Get4Digits();

    if( res2 == -1 )
      return "Invalid GUID";

    tempGUID[0] = ( res << 16 ) + res2;

    if( *m_pchCurrent++ != '-' )
    {
      return "Invalid GUID";
    }

    res = Get4Digits();

    if( res == -1 )
      return "Invalid GUID";

    if( *m_pchCurrent++ != '-' )
    {
      return "Invalid GUID";
    }

    res2 = Get4Digits();

    if( res2 == -1 )
      return "Invalid GUID";

    tempGUID[1] = ( res2 << 16 ) + res;

    if( *m_pchCurrent++ != '-' )
    {
      return "Invalid GUID";
    }

    res = sGet4Digits();

    if( res == -1 )
      return "Invalid GUID";

    if( *m_pchCurrent++ != '-' )
    {
      return "Invalid GUID";
    }

    res2 = sGet4Digits();

    if( res2 == -1 )
      return "Invalid GUID";

    tempGUID[2] = ( res2 << 16 ) + res;

    res = sGet4Digits();

    if( res == -1 )
      return "Invalid GUID";

    res2 = sGet4Digits();

    if( res2 == -1 )
      return "Invalid GUID";

    tempGUID[3] = ( res2 << 16 ) + res;

    if( Compare == 0 )
    {
      if( 0 == memcmp( tempGUID, &m_AdapterId.DeviceIdentifier, 16 ) )
        return ( char* )1;
      else
        return ( char* )0;
    }

    if( 0 != memcmp( tempGUID, &m_AdapterId.DeviceIdentifier, 16 ) )
      return ( char* )1;
    else
      return ( char* )0;

  }

  if( Type == 2 )                               // Driver 4.1.25.1111
  {
    LARGE_INTEGER Driver;

    DWORD result = GetNumber();

    if( result == -1 || *m_pchCurrent++ != '.' )
      return "Invalid driver number";

    DWORD result1 = GetNumber();

    Driver.HighPart = ( result << 16 ) + result1;

    if( result == -1 || *m_pchCurrent++ != '.' )
      return "Invalid driver number";

    result = GetNumber();

    if( result == -1 || *m_pchCurrent++ != '.' )
      return "Invalid driver number";

    result1 = GetNumber();

    Driver.LowPart = ( result << 16 ) + result1;

    if( result == -1 )
      return "Invalid driver number";

    __int64 rhs = *( __int64* )&Driver;
    __int64 lhs = *( __int64* )&m_AdapterId.DriverVersion;

    switch( Compare )
    {
    case 0:                                 // ==
      if( lhs == rhs )
        return ( char* )1;
      else
        return ( char* )0;
    case 1:                                 // !=
      if( lhs != rhs )
        return ( char* )1;
      else
        return ( char* )0;
    case 2:                                 // >
      if( lhs > rhs )
        return ( char* )1;
      else
        return ( char* )0;
    case 3:                                 // <
      if( lhs < rhs )
        return ( char* )1;
      else
        return ( char* )0;
    case 4:                                 // >=
      if( lhs >= rhs )
        return ( char* )1;
      else
        return ( char* )0;
    case 5:                                 // <=
      if( lhs <= rhs )
        return ( char* )1;
      else
        return ( char* )0;
    }

    return "Invalid";
  }
  //
  // Get Value (or OS)
  //
  DWORD Value;

  if( Type == 3 )
  {
    if( NextStringIs( k_KeywordWin95 ) )
    {
      Value = 0;
      m_pchCurrent += 5;
    }
    else
    {
      if( NextStringIs( k_KeywordWin98 ) )
      {
        Value = 1;
        m_pchCurrent += 5;
      }
      else
      {
        if( NextStringIs( k_KeywordWin98se ) )
        {
          Value = 2;
          m_pchCurrent += 7;
        }
        else
        {
          if( NextStringIs( k_KeywordWinme ) )
          {
            Value = 3;
            m_pchCurrent += 5;
          }
          else
          {
            if( NextStringIs( k_KeywordWin2k ) )
            {
              Value = 4;
              m_pchCurrent += 5;
            }
            else
            {
              if( NextStringIs( k_KeywordWinxp ) )
              {
                Value = 5;
                m_pchCurrent += 5;
              }
              else
              {
                if( NextStringIs( k_KeywordWin2003 ) )
                {
                  Value = 6;
                  m_pchCurrent += 7;
                }
                else
                {
                  return "Unknown OS";
                }
              }
            }
          }
        }
      }
    }
  }
  else
  {
    Value = GetNumber();

    if( Value == -1 )
    {
      return "Number expected";
    }
  }

  switch( Compare )
  {
  case 0:                                 // ==
    if( Source == Value )
      return ( char* )1;
    else
      return ( char* )0;
  case 1:                                 // !=
    if( Source != Value )
      return ( char* )1;
    else
      return ( char* )0;
  case 2:                                 // >
    if( Source > Value )
      return ( char* )1;
    else
      return ( char* )0;
  case 3:                                 // <
    if( Source < Value )
      return ( char* )1;
    else
      return ( char* )0;
  case 4:                                 // >=
    if( Source >= Value )
      return ( char* )1;
    else
      return ( char* )0;
  case 5:                                 // <=
    if( Source <= Value )
      return ( char* )1;
    else
      return ( char* )0;

  case 6:                                 // &
    if( Source & Value )
      return ( char* )1;
    else
      return ( char* )0;
  }

  return "Invalid";
}


bool CConfigDatabase::Load( LPCTSTR FileName,
                           const SOUND_DEVICE& soundDevice,
                           const D3DADAPTER_IDENTIFIER9& DDid,
                           const D3DCAPS9& caps,
                           DWORD SystemMemory,
                           DWORD VideoMemory,
                           DWORD CPUSpeed )
{
  if( m_pDevice == NULL )
    m_pDevice = new CPropertySet( *this );

  if( m_pRequirements == NULL )
    m_pRequirements = new CPropertySet( *this );

  // Setup return pointers
  m_SoundDevice = soundDevice;
  m_CPUSpeed = CPUSpeed;
  m_SystemMemory = SystemMemory;
  m_VideoMemory = VideoMemory;
  m_AdapterId = DDid;
  m_caps = caps;
  m_fError = false;

  // If driver version is 0.0.0.0 try and read from driver .dll
  if( ( m_AdapterId.DriverVersion.HighPart | m_AdapterId.DriverVersion.LowPart ) == 0 )
  {
    VS_FIXEDFILEINFO ffi;

    DWORD dwHandle;
    DWORD cchver = GetFileVersionInfoSizeA( m_AdapterId.Driver, &dwHandle );
    if( cchver != 0 )
    {
      char* pver = new char[cchver];
      if( pver )
      {
        BOOL bret = GetFileVersionInfoA( m_AdapterId.Driver, dwHandle, cchver, pver );
        if( bret )
        {
          UINT uLen;
          void* pbuf;

          bret = VerQueryValueA( pver, "\\", &pbuf, &uLen );

          if( bret )
          {
            memcpy( &ffi, pbuf, sizeof( VS_FIXEDFILEINFO ) );

            m_AdapterId.DriverVersion.HighPart = ffi.dwFileVersionMS;
            m_AdapterId.DriverVersion.LowPart = ffi.dwFileVersionLS;
          }
        }

        delete [] pver;
      }
    }
  }
  //
  // Try and find video card file
  //
  HANDLE hFile = CreateFile( FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

  if( hFile == INVALID_HANDLE_VALUE )
  {
    TCHAR tszBadFile[MAX_PATH];
    TCHAR tszErrorMsg[MAX_PATH+128];
    if( GetCurrentDirectory( MAX_PATH, tszBadFile ) == 0 )
      tszBadFile[0] = 0;
    _tcscat_s( tszBadFile, MAX_PATH, TEXT("\\") );
    _tcscat_s( tszBadFile, MAX_PATH, FileName );
    _stprintf_s( tszErrorMsg, MAX_PATH + 128, TEXT("Cannot find '%s'"), tszBadFile );

#ifdef _UNICODE
    static char szErrorMsg[MAX_PATH+128];
    // Convert to MBCS
    WideCharToMultiByte( CP_ACP, 0, tszErrorMsg, -1, szErrorMsg, MAX_PATH + 128, NULL, NULL );

    m_ErrorString = szErrorMsg;
#else // _UNICODE
    m_ErrorString = tszErrorMsg;
#endif // _UNICODE
    return false;
  }

  //
  // Read file in
  //
  DWORD Size = GetFileSize( hFile, NULL );
  DWORD Len;
  m_pchFile = new char[Size + 16];                       // Some extra room for string compares
  if( NULL == m_pchFile )
  {
    CloseHandle( hFile );
    return false;
  }

  BOOL bSuccess = ReadFile( hFile, m_pchFile, Size, &Len, NULL );
  CloseHandle( hFile );
  if( !bSuccess )
  {
    delete [] m_pchFile;
    return false;
  }

  m_pchFile[Size] = 13;                                     // Make sure last line ends with CR.
  m_pchCurrent = m_pchFile;
  m_pchCurrentLine = m_pchCurrent;
  m_LineNumber = 1;
  m_pchEndOfFile = m_pchFile + Size;

  if( !DoRequirements() )
  {
    delete [] m_pchFile;
    return false;
  }

  m_pchCurrent = m_pchFile;
  m_pchCurrentLine = m_pchCurrent;
  m_LineNumber = 1;
  if( !DoPropertySets() )
  {
    delete [] m_pchFile;
    return false;
  }

  if( !DoPreApplyToAll() )
  {
    delete [] m_pchFile;
    return false;
  }

  // Save the location marker after pre-ApplyToAll block.
  // Later, audio vendor parsing should begin here too.
  char* pchAfterPreApplyToAll = m_pchCurrent;
  char* pchLineAfterPreApplyToAll = m_pchCurrentLine;
  int nLineNumberAfterPreApplyToAll = m_LineNumber;
  if( !DoDisplayVendorAndDevice() )
  {
    delete [] m_pchFile;
    return false;
  }
  // Save the location marker after display vendor section
  // to help parse the post-applytoall block.
  char* pchAfterDisplayVendor = m_pchCurrent;
  char* pchLineAfterDisplayVendor = m_pchCurrentLine;
  DWORD nLineNumberAfterDisplayVendor = m_LineNumber;

  // Restore text pointers to the location after the pre-
  // ApplyToAll block.
  m_pchCurrent = pchAfterPreApplyToAll;
  m_pchCurrentLine = pchLineAfterPreApplyToAll;
  m_LineNumber = nLineNumberAfterPreApplyToAll;
  if( !DoSoundVendorAndDevice() )
  {
    delete [] m_pchFile;
    return false;
  }

  // Start post-ApplyToAll parsing at the end of
  // both display and audio sections.
  m_pchCurrent = max( m_pchCurrent, pchAfterDisplayVendor );
  m_pchCurrentLine = max( m_pchCurrentLine, pchLineAfterDisplayVendor );
  m_LineNumber = max( m_LineNumber, nLineNumberAfterDisplayVendor );
  if( !DoPostApplyToAll() )
  {
    delete [] m_pchFile;
    return false;
  }

  //
  // Clean up and retrun
  //
  delete [] m_pchFile;
  return true;
}


CConfigDatabase::CConfigDatabase()
{
  m_pDevice = 0;
  m_pRequirements = 0;
}


CConfigDatabase::~CConfigDatabase()
{
  delete m_pDevice;
  delete m_pRequirements;

  map <string, CPropertySet*>::iterator it, end;
  it = m_mapNameToPropertySet.begin();
  end = m_mapNameToPropertySet.end();
  while( it != end )
  {
    delete ( *it ).second;
    ++it;
  }
}

bool CConfigDatabase::DoPreApplyToAll()
{
  do
  {
    if( NextStringIs( k_KeywordApplyToAll ) )
    {
      SkipToNextLine();
      if( !DoPropertySet( m_pDevice ) )
      {
        return false;
      }
    }
    else if( NextStringIs( k_KeywordDisplayVendor ) ||
      NextStringIs( k_KeywordAudioVendor ) )
    {
      break;
    }

    SkipToNextLine();

  } while( m_pchCurrent < m_pchEndOfFile );

  return true;
}


bool CConfigDatabase::DoPostApplyToAll()
{
  do
  {
    if( NextStringIs( k_KeywordApplyToAll ) )
    {
      SkipToNextLine();
      if( !DoPropertySet( m_pDevice ) )
      {
        return false;
      }
    }

    SkipToNextLine();

  } while( m_pchCurrent < m_pchEndOfFile );

  return true;
}


bool CConfigDatabase::DoPropertySets()
{
  do
  {
    if( NextStringIs( k_KeywordPropertySet ) )
    {
      m_pchCurrent += 11;

      SkipSpace();

      if( *m_pchCurrent == '=' )
      {
        m_pchCurrent++;

        char* pszName = GetString();
        if( !pszName )
        {
          return false;
        }

        string strName = pszName;

        SkipToNextLine();
        CPropertySet* pSet = new CPropertySet( *this );
        if( !DoPropertySet( pSet ) )
        {
          delete pSet;
          return false;
        }

        m_mapNameToPropertySet[strName] = pSet;

      }
      else
      {
        SyntaxError( "Missing =" );
        return false;
      }
    }
    else if( ( NextStringIs( k_KeywordDisplayVendor ) ) || ( NextStringIs( k_KeywordAudioVendor ) )
      || ( NextStringIs( k_KeywordApplyToAll ) ) )
    {
      break;
    }

    SkipToNextLine();

  } while( m_pchCurrent < m_pchEndOfFile );

  return true;
}


bool CConfigDatabase::DoDisplayVendorAndDevice()
{
  //
  // Find correct VendorID
  //
  DWORD Vendor = -1;
  do
  {
    if( NextStringIs( k_KeywordDisplayVendor ) )
    {
      m_pchCurrent += 13;

      SkipSpace();

      if( *m_pchCurrent == '=' )
      {
        m_pchCurrent++;

        if( NextStringIs( k_KeywordUnknown ) )
        {
          Vendor = m_AdapterId.VendorId;
          break;
        }

        DWORD tempVendor = GetNumber();                       // Will be -1 if error

        if( tempVendor == m_AdapterId.VendorId )
        {
          Vendor = tempVendor;
          break;
        }
      }
    }
    else if( NextStringIs( k_KeywordApplyToAll ) )
    {
      break;
    }

    SkipToNextLine();

  } while( m_pchCurrent < m_pchEndOfFile );
  //
  // Deal with Unknown VendorID
  //
  if( Vendor == -1 )
  {
    return true;
  }
  //
  // Get Vendor Name
  //
  const char* pszVendor = GetString();
  if( !pszVendor )
  {
    return false;
  }
  m_VendorString = pszVendor;

  //
  // Skip over any other vendor names (Some devices have multiple vendors)
  //
  do
  {
    SkipToNextLine();

    if( !NextStringIs( k_KeywordDisplayVendor ) )
    {
      SkipSpace();

      if( *m_pchCurrent >= '0' && *m_pchCurrent <= '9' )
      {
        break;
      }

      if( *m_pchCurrent!=13 && *( WORD* )m_pchCurrent!='//' )       // Ignore comments and blank lines
      {
        //
        // If we find a line that is not a comment or vendor before
        // the first device, it must be the start of a property set.
        //
        if( !DoPropertySet( m_pDevice ) )
        {
          return false;
        }
      }
    }

  } while( m_pchCurrent < m_pchEndOfFile );
  //
  // Now search for DeviceID  (Until next vendor or end of file is found)
  //
  DWORD DeviceID = -1;
  do
  {
    if( NextStringIs( k_KeywordDisplayVendor ) )
    {
      break;
    }

    if( NextStringIs( k_KeywordUnknown ) )
    {
      DeviceID = m_AdapterId.DeviceId;
      m_pchCurrent += strlen( k_KeywordUnknown );
      SkipSpace();
      break;
    }

    SkipSpace();

    if( *m_pchCurrent >= '0' && *m_pchCurrent <= '9' )
    {
      DWORD tempDeviceID = GetNumber();

      if( tempDeviceID == m_AdapterId.DeviceId )
      {
        DeviceID = tempDeviceID;
        break;
      }
    }

    SkipToNextLine();

  } while( m_pchCurrent < m_pchEndOfFile );
  //
  // Deal with unknown DeviceID
  //
  if( DeviceID == -1 )
  {
    return true;
  }
  //
  // Get Device Name
  //
  if( *m_pchCurrent != '=' )
  {
    SyntaxError( "xxx = Device Name expected" );
    return false;
  }
  //
  // Add the device name
  //
  m_pchCurrent++;

  char* pszDevice = GetString();
  if( !pszDevice )
  {
    return false;
  }
  m_DeviceString = pszDevice;

  //
  // Now add flags until break is found
  //
  SkipToNextLine();
  if( !DoPropertySet( m_pDevice ) )
  {
    return false;
  }

  return true;
}


bool CConfigDatabase::DoSoundVendorAndDevice()
{
  //
  // Find correct VendorID
  //
  DWORD Vendor = -1;
  do
  {
    if( NextStringIs( k_KeywordAudioVendor ) )
    {
      m_pchCurrent += 11;

      SkipSpace();

      if( *m_pchCurrent == '=' )
      {
        m_pchCurrent++;

        if( NextStringIs( k_KeywordUnknown ) )
        {
          Vendor = m_SoundDevice.VendorID;
          break;
        }

        DWORD tempVendor = GetNumber();                       // Will be -1 if error

        if( tempVendor == m_SoundDevice.VendorID )
        {
          Vendor = tempVendor;
          break;
        }
      }
    }
    else if( NextStringIs( k_KeywordApplyToAll ) )
    {
      break;
    }

    SkipToNextLine();

  } while( m_pchCurrent < m_pchEndOfFile );
  //
  // Deal with Unknown VendorID
  //
  if( Vendor == -1 )
  {
    return true;
  }
  //
  // Get Vendor Name
  //
  const char* pszVendor = GetString();
  if( !pszVendor )
  {
    return false;
  }
  m_SoundVendorString = pszVendor;

  //
  // Skip over any other vendor names (Some devices have multiple vendors)
  //
  do
  {
    SkipToNextLine();

    if( !NextStringIs( k_KeywordAudioVendor ) )
    {
      SkipSpace();

      if( *m_pchCurrent >= '0' && *m_pchCurrent <= '9' )
      {
        break;
      }

      if( *m_pchCurrent!=13 && *( WORD* )m_pchCurrent!='//' )       // Ignore comments and blank lines
      {
        //
        // If we find a line that is not a comment or vendor before
        // the first device, it must be the start of a property set.
        //
        if( !DoPropertySet( m_pDevice ) )
        {
          return false;
        }
      }
    }

  } while( m_pchCurrent < m_pchEndOfFile );
  //
  // Now search for DeviceID  (Until next vendor or end of file is found)
  //
  DWORD DeviceID = -1;
  do
  {
    if( NextStringIs( k_KeywordAudioVendor ) || NextStringIs( k_KeywordDisplayVendor ) )
    {
      break;
    }

    if( NextStringIs( k_KeywordUnknown ) )
    {
      DeviceID = m_SoundDevice.DeviceID;
      m_pchCurrent += strlen( k_KeywordUnknown );
      SkipSpace();
      break;
    }

    SkipSpace();

    if( *m_pchCurrent >= '0' && *m_pchCurrent <= '9' )
    {
      DWORD tempDeviceID = GetNumber();

      if( tempDeviceID == m_SoundDevice.DeviceID )
      {
        DeviceID = tempDeviceID;
        break;
      }
    }

    SkipToNextLine();

  } while( m_pchCurrent < m_pchEndOfFile );
  //
  // Deal with unknown DeviceID
  //
  if( DeviceID == -1 )
  {
    return true;
  }
  //
  // Get Device Name
  //
  if( *m_pchCurrent != '=' )
  {
    SyntaxError( "xxx = Device Name expected" );
    return false;
  }
  //
  // Add the device name
  //
  m_pchCurrent++;

  char* pszDevice = GetString();
  if( !pszDevice )
  {
    return false;
  }
  m_SoundDeviceString = pszDevice;

  //
  // Now add flags until break is found
  //
  SkipToNextLine();
  if( !DoPropertySet( m_pDevice ) )
  {
    return false;
  }

  return true;
}


bool CConfigDatabase::DoRequirements()
{
  //
  // Find correct Requirements section
  //
  do
  {
    if( NextStringIs( k_KeywordRequirements ) )
    {
      break;
    }
    SkipToNextLine();

  } while( m_pchCurrent < m_pchEndOfFile );
  //
  // No Requirment section?
  //
  if( m_pchCurrent >= m_pchEndOfFile )
  {
    return true;
  }
  //
  // Get Requirements
  //
  SkipToNextLine();
  if( !DoPropertySet( m_pRequirements ) )
  {
    return false;
  }

  return true;
}


bool CConfigDatabase::DoPropertySet( CPropertySet* pPropertySet )
{
  //
  // Now add flags until break is found
  //
  const int k_MaxNestedIf = 256;                              // Max levels of nesting
  int NestedIf[k_MaxNestedIf];
  int IfPointer = 0;                                            // Depth of IF's
  int SkippingIF = 0;                                           // 0=Not in an IF, 1=In True if, 2=In false IF
  bool first = true;

  do
  {
    if( first )
    {
      first = false;
    }
    else
    {
      SkipToNextLine();
    }

    //
    // Check for unexpected keywords
    //
    if( NextStringIs( k_KeywordDisplayVendor ) || NextStringIs( k_KeywordAudioVendor ) ||
      NextStringIs( k_KeywordRequirements ) )
    {
      return true;
    }

    SkipSpace();

    if( *m_pchCurrent!=13 && *( WORD* )m_pchCurrent!='//' )       // Ignore comments and blank lines
    {

      if( *m_pchCurrent >= '0' && *m_pchCurrent <= '9' )      // Or the start of another device
      {
        continue;
      }

      if( NextStringIs( k_KeywordUnknown ) )             // Or unknown device clause
      {
        continue;
      }

      if( NextStringIs( k_KeywordBreak ) )
      {
        break;
      }

      if( NextStringIs( k_KeywordMaxOverallGraphicDetail ) )
      {
        m_pchCurrent += strlen( k_KeywordMaxOverallGraphicDetail );

        //  This should be in the format: MaxOGD = N
        //  Skip spaces, '='s.
        SkipSpace();
        if( *m_pchCurrent == '=' )
        {
          m_pchCurrent++;
        }
        else
        {
          SyntaxError( "Expecting \'=\', didn\'t get it" );
          return false;
        }
        SkipSpace();

        //  We have the value in string format in m_pchCurrent and we need the
        //  value in both string and numeric format. Doing a GetNumber then a
        //  swprintf_s works best because it will keep extra spaces or comments out
        //  of the string version.

        DWORD dwMaxOGD = GetNumber();
        if( dwMaxOGD != ( DWORD )-1 )
        {
          char maxValue[16];
          char curValue[16] = "0";

          sprintf_s( maxValue, 16, "%d", dwMaxOGD );
          if( m_pDevice->Get( k_KeywordOverallGraphicDetail, curValue, sizeof( curValue ) ) )
          {
            DWORD dwOGD = atoi( curValue );
            if( dwOGD > dwMaxOGD )
            {
              //  Check the current graphic detail level. If its
              //  higher than the max, apply the max.
              map <string, CPropertySet*>::iterator it;
              it = m_mapOGDToPropertySet.find( maxValue );
              if( it == m_mapOGDToPropertySet.end() )
              {
                SyntaxError( "Unrecognized graphic detail" );
                return false;
              }
              CPropertySet* pSet = ( *it ).second;
              ApplyPropertySet( m_pDevice, pSet );
            }
          }
        }
        else
        {
          SyntaxError( "MaxOverallGraphicDetail did not specify a number!" );
          return false;
        }

        continue;
      }

      if( NextStringIs( k_KeywordIf ) )
      {
        m_pchCurrent += 2;

        char* condition = GetCondition();

        NestedIf[IfPointer++] = SkippingIF;

        if( IfPointer == 16 )
        {
          SyntaxError( "IF's nested too deep" );
          return false;
        }

        if( condition == ( char* )1 )                       // True?
        {
          if( SkippingIF != 2 )
          {
            SkippingIF = 1;                           // If inside false if, keep skipping
          }
        }
        else
        {
          if( condition == ( char* )0 )                   // False?
          {
            SkippingIF = 2;
          }
          else
          {
            if( condition )                         // m_fError
            {
              SyntaxError( condition );
              return false;
            }
          }
        }
      }
      else
      {
        if( NextStringIs( k_KeywordEndif ) )
        {
          if( IfPointer == 0 )
          {
            SyntaxError( "Unexpected ENDIF" );
            return false;
          }

          SkippingIF = NestedIf[--IfPointer];
        }
        else
        {
          if( 0 == SkippingIF || 1 == SkippingIF )                    // Add flag if not skipping in a IF
          {
            if( NextStringIs( k_KeywordPropertySet ) )
            {
              m_pchCurrent += 11;

              SkipSpace();

              if( *m_pchCurrent == '=' )
              {
                m_pchCurrent++;

                char* pszName = GetString();
                if( !pszName )
                {
                  return false;
                }
                string strName = pszName;

                map <string, CPropertySet*>::iterator it;
                it = m_mapNameToPropertySet.find( strName );
                if( it == m_mapNameToPropertySet.end() )
                {
                  SyntaxError( "Unrecognized property set" );
                  return false;
                }
                CPropertySet* pSet = ( *it ).second;
                ApplyPropertySet( pPropertySet, pSet );
              }
              else
              {
                SyntaxError( "Missing =" );
                return false;
              }
            }
            else
            {
              char* strErr = AddFlag( pPropertySet );  // Add this flag, check for duplicates

              if( strErr )
              {
                SyntaxError( strErr );
                return false;
              }
            }
          }
        }
      }
    }

  } while( m_pchCurrent < m_pchEndOfFile );

  //
  // Check for hanging endif
  //
  if( SkippingIF != 0 || IfPointer != 0 )
  {
    SyntaxError( "Bad IF/ENDIF" );
    return false;
  }

  return true;
}


void CConfigDatabase::ApplyPropertySet( CPropertySet* pSetDst, CPropertySet* pSetSrc )
{
  vector <StringPair>::const_iterator it, end;
  it = pSetSrc->GetProperties().begin();
  end = pSetSrc->GetProperties().end();
  while( it != end )
  {
    const StringPair& pr = *it;
    pSetDst->Set( pr.first.c_str(), pr.second.c_str() );
    ++it;
  }
}


IConfigDatabase* IConfigDatabase::Create()
{
  CConfigDatabase* pRet = new CConfigDatabase();
  return pRet;
}
