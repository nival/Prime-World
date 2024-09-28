#include "stdafx.h"
#include "HwInput.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Input
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IHwInput * CreateHwInput( HWND hWnd, HINSTANCE hInstance, bool debugMouse, bool nonExclusiveMode )
{
  return new HwInput( hWnd, hInstance, debugMouse, nonExclusiveMode );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int DEFAULT_SAMPLE_BUFFER_SIZE = 1024;
static const int AXIS_RANGE_VALUE = 10000;
static const int POV_NUETRAL_VALUE = 0xffffffff;

static const int DBLCLK_MODIFIER = 0x4000;



//Debug verbosity
static int s_verbosity = 0;
REGISTER_DEV_VAR( "input_verbosity", s_verbosity, STORAGE_NONE );

int GetVerbosityLevel() { return s_verbosity; }

static const int VERBOSITY_HW = 2;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SControlInfo
{
  const char *          name;
  int                   diDevType;
  int                   diDevAction;
  EHwControlType::Enum  type;
};

#include "HwInputKeys.inl"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const static int s_controlsTableSize = sizeof( s_controlsTable ) / sizeof( SControlInfo );

/*
//For browser plugin:
(c) Vladik Aranoff
static void* GetAddressOfThisFunction()
{
  return (void *)((ULONG_PTR)GetAddressOfThisFunction);
}


HMODULE HwInput::GetDllModuleHandle()
{
  //drumdance
  HMODULE hThis = NULL;
  GetModuleHandleEx( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)(void *)GetAddressOfThisFunction, &hThis );
  return hThis;
}
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HWND HwInput::GetTopLevelWindow( HWND hWnd )
{
  HWND hCur = hWnd;
  while( 1 )
  {
    if ( GetWindowStyle( hCur ) & WS_THICKFRAME )
      return hCur;

    HWND h = GetParent(hCur);
    if( !h )
      return hCur;
    hCur = h;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HwInput::HwInput() :
hWindow( NULL ),
nonExclusiveMode( false ),
focused( false ),
coopLevelSet( false ),
gamePadsNum( 0 ), drivingWheelsNum( 0 ), joysticksNum( 0 ), gameControlsNum( 0 ),
currentExternalId( 0 )
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HwInput::HwInput( HWND hWnd, HINSTANCE hInstance, bool debugMouse, bool _nonExclusiveMode ) :
hWindow( NULL ),
nonExclusiveMode( _nonExclusiveMode ),
focused( false ),
coopLevelSet( false ),
gamePadsNum( 0 ), drivingWheelsNum( 0 ), joysticksNum( 0 ), gameControlsNum( 0 ),
currentExternalId( 0 )
{
	hWindow = GetTopLevelWindow( hWnd );

	HRESULT res = DirectInput8Create( hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)dinput.GetAddr(), 0 );
	if( FAILED( res ) )
		return;

	if ( CheckMouseAvailability( debugMouse ) )
    if ( !CreateMouseDevice() )
      return;

  if ( !CreateKeyboardDevice() )
    return;

	dinput->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumDevicesCallback, this, DIEDFL_ATTACHEDONLY );

  SetCoopLevel();

  focused = false;
}


HwInput::~HwInput()
{
  DebugTrace("Start HwInput::~HwInput");

  for ( int i = 0; i < devices.size(); ++i )
  {
    SDevice & device = devices[i];
    device.device->Unacquire();
  }

  for ( int i = 0; i < devices.size(); ++i )
  {
    SDevice & device = devices[i];
    device.device = 0;
  }

  devices.clear();

  dinput = 0;

  DebugTrace("Start HwInput::~HwInput OK");
}


void HwInput::OnDestroyContents()
{
}


bool HwInput::SetCoopLevel()
{
  if ( coopLevelSet )
		return true;
	
  for ( int i = 0; i < devices.size(); ++i )
  {
    SDevice & device = devices[i];

		HRESULT res = 0;

    if ( ( IsDebuggerPresent() && ( GET_DIDEVICE_TYPE( device.dwDevType ) != DI8DEVTYPE_MOUSE ) ) || nonExclusiveMode )
      res = device.device->SetCooperativeLevel( hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
		else
		{
			int nDeviceID = GET_DIDEVICE_TYPE( device.dwDevType );
			if ( nDeviceID == DI8DEVTYPE_KEYBOARD || nDeviceID == DI8DEVTYPE_MOUSE )
				res = device.device->SetCooperativeLevel( hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
			else
				res = device.device->SetCooperativeLevel( hWindow, DISCL_EXCLUSIVE | DISCL_FOREGROUND );
		}

		if( FAILED( res ) )
			return false;
	}
	
	coopLevelSet = true;
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool HwInput::CheckMouseAvailability( bool debugMouse )
{
  // disable mouse in debugger for win2k and earlier versions
	if ( IsDebuggerPresent() && !debugMouse )
	{
		// Figure out which OS we are on.
		OSVERSIONINFO stOSVI;
		memset( &stOSVI , NULL , sizeof(OSVERSIONINFO) );
		stOSVI.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
		if ( !GetVersionEx( &stOSVI ) )
			return false;
		else
		{
			if ( stOSVI.dwMajorVersion < 5 || ( stOSVI.dwMajorVersion == 5 && stOSVI.dwMinorVersion == 0 ) )
				return false;
		}
	}

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool HwInput::CreateMouseDevice()
{
  NWin32Helper::com_ptr<IDirectInputDevice8> tmpDevice;

  HRESULT res = dinput->CreateDevice( GUID_SysMouse, tmpDevice.GetAddr(), 0 );
  if ( FAILED( res ) )
    return false;

  res = tmpDevice->SetDataFormat( &c_dfDIMouse2 );
  if( FAILED( res ) )
    return false;

  DIPROPDWORD sProp;
  sProp.diph.dwSize = sizeof(DIPROPDWORD);
  sProp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  sProp.diph.dwObj = 0;
  sProp.diph.dwHow = DIPH_DEVICE;
  sProp.dwData = DIPROPAXISMODE_REL;
  res = tmpDevice->SetProperty( DIPROP_AXISMODE, &sProp.diph );
  if( FAILED( res ) )
    return false;

  sProp.diph.dwSize = sizeof(DIPROPDWORD);
  sProp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  sProp.diph.dwObj = 0;
  sProp.diph.dwHow = DIPH_DEVICE;
  sProp.dwData = DEFAULT_SAMPLE_BUFFER_SIZE;
  res = tmpDevice->SetProperty( DIPROP_BUFFERSIZE, &sProp.diph );
  if( FAILED( res ) )
    return false;

  AddDevice( tmpDevice, c_dfDIMouse2.dwDataSize );
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool HwInput::CreateKeyboardDevice()
{
  NWin32Helper::com_ptr<IDirectInputDevice8> tmpDevice;

  HRESULT res = dinput->CreateDevice( GUID_SysKeyboard, tmpDevice.GetAddr(), 0 );
  if ( FAILED( res ) )
    return false;

  res = tmpDevice->SetDataFormat( &c_dfDIKeyboard );
  if ( FAILED( res ) )
    return false;

  DIPROPDWORD sProp;
  sProp.diph.dwSize = sizeof(DIPROPDWORD);
  sProp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  sProp.diph.dwObj = 0;
  sProp.diph.dwHow = DIPH_DEVICE;
  sProp.dwData = DEFAULT_SAMPLE_BUFFER_SIZE;
  res = tmpDevice->SetProperty( DIPROP_BUFFERSIZE, &sProp.diph );
  if( FAILED(res) )
    return false;

  AddDevice( tmpDevice, c_dfDIKeyboard.dwDataSize );
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HwInput::AddDevice( IDirectInputDevice8 * pDevice, DWORD dwFormatSize )
{
  HRESULT res;
  DIDEVCAPS didCaps;
  DIDEVICEINSTANCE devInst;

  ZeroMemory( &devInst, sizeof( DIDEVICEINSTANCE ) );
  devInst.dwSize = sizeof( DIDEVICEINSTANCE );
  res = pDevice->GetDeviceInfo( &devInst );
  if ( FAILED( res ) )
    return;

  ZeroMemory( &didCaps, sizeof( DIDEVCAPS ) );
  didCaps.dwSize = sizeof( DIDEVCAPS );
  res = pDevice->GetCapabilities( &didCaps );
  if ( FAILED( res ) )
    return;

  SDevice descr;
  descr.id = devices.size();
  descr.poll = ( didCaps.dwFlags & DIDC_POLLEDDATAFORMAT ) ? true : false;
  descr.name = devInst.tszProductName;
  descr.dwDevType = devInst.dwDevType;
  descr.dwFormatSize = dwFormatSize;
  descr.device = pDevice;

  if ( s_verbosity >= VERBOSITY_HW )
    DebugTrace( "Standard input device added: %s",  devInst.tszInstanceName );

  AddDeviceKeys( descr.id, GET_DIDEVICE_TYPE( devInst.dwDevType ) );

  devices.push_back( descr );

  return;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HwInput::AddDeviceKey( EHwControlType::Enum type, int deviceId, int deviceType, int controlId, const string & name )
{
  CObj<HwControl> control = new HwControl( type, deviceId, deviceType, controlId, currentExternalId, name.c_str() );
  ++currentExternalId;

  controlsByHwId[control->FullHwId()] = control;
  controlsByExtId[control->ExternalId()] = control;
  controlsByName[name] = control;

  if ( s_verbosity >= VERBOSITY_HW )
    DebugTrace( "    Control '%s' added with id %d", name.c_str(), controlId );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HwInput::AddDeviceKeys( int deviceId, int deviceType )
{
  for ( int i = 0; i < s_controlsTableSize; ++i )
  {
    SControlInfo & info = s_controlsTable[i];
    if ( info.diDevType == deviceType )
    {
      AddDeviceKey( info.type, deviceId, deviceType, info.diDevAction, info.name );
      if ( info.type == EHwControlType::Key )
      {
        string name = string( info.name ) + "_DBLCLK";
        AddDeviceKey( info.type, deviceId, deviceType, info.diDevAction | DBLCLK_MODIFIER,	name );
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HwInput::AddEnumeratedDevice( IDirectInputDevice8 * pDevice )
{
  DIDEVICEINSTANCE devInst;
  ZeroMemory( &devInst, sizeof( DIDEVICEINSTANCE ) );
  devInst.dwSize = sizeof( DIDEVICEINSTANCE );
  HRESULT res = pDevice->GetDeviceInfo( &devInst );
  if ( FAILED( res ) )
    return;

  if ( s_verbosity >= VERBOSITY_HW )
    DebugTrace( "Input device found: %s",  devInst.tszInstanceName );

  DIDEVCAPS didCaps;
  ZeroMemory( &didCaps, sizeof( DIDEVCAPS ) );
  didCaps.dwSize = sizeof( DIDEVCAPS );
  res = pDevice->GetCapabilities( &didCaps );
  if ( FAILED( res ) )
    return;

  SDevice device;
  device.id = devices.size();
  device.poll = ( didCaps.dwFlags & DIDC_POLLEDDATAFORMAT ) || ( didCaps.dwFlags & DIDC_POLLEDDEVICE	);
  device.name = devInst.tszProductName;
  device.dwDevType = devInst.dwDevType;
  device.dwFormatSize = sizeof( SInputDataFormat );
  device.device = pDevice;

  SDeviceObjectsEnum objectsEnum( this, device.id );
  switch( GET_DIDEVICE_TYPE( devInst.dwDevType ) )
  {
    case DI8DEVTYPE_GAMEPAD:
      objectsEnum.name = NStr::StrFmt( "GAMEPAD%d", gamePadsNum++ );
      break;

    case DI8DEVTYPE_DRIVING:
      objectsEnum.name = NStr::StrFmt( "DRIVING%d", drivingWheelsNum++ );
      break;

    case DI8DEVTYPE_JOYSTICK:
      objectsEnum.name = NStr::StrFmt( "JOYSTICK%d", joysticksNum++ );
      break;

    default:
      objectsEnum.name = NStr::StrFmt( "GAMECTRL%d", gameControlsNum++ );
      break;
  }

  res = pDevice->EnumObjects( EnumDeviceObjectsCallback, &objectsEnum, DIDFT_ALL );
  if ( FAILED( res ) )
    return;

  DIDATAFORMAT dataFormat;
  dataFormat.dwSize = sizeof(DIDATAFORMAT);
  dataFormat.dwObjSize = sizeof(DIOBJECTDATAFORMAT);
  dataFormat.dwDataSize = device.dwFormatSize;
  dataFormat.dwFlags = DIDF_ABSAXIS;
  dataFormat.dwNumObjs = objectsEnum.objects.size();
  dataFormat.rgodf = &( objectsEnum.objects[0] );
  res = pDevice->SetDataFormat( &dataFormat );
  if( FAILED(res) )
    return;

  DIPROPDWORD dipdw;
  dipdw.diph.dwSize = sizeof(DIPROPDWORD);
  dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  dipdw.diph.dwObj = 0;
  dipdw.diph.dwHow = DIPH_DEVICE;
  dipdw.dwData = DEFAULT_SAMPLE_BUFFER_SIZE;
  res = pDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
  if( FAILED( res ) )
    return;

  for ( int i = 0; i < objectsEnum.objects.size(); ++i )
  {
    if ( ( objectsEnum.objects[i].dwType & DIDFT_AXIS ) == 0 )
      continue;

    DIPROPRANGE dipRange;
    dipRange.diph.dwSize = sizeof(DIPROPRANGE); 
    dipRange.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
    dipRange.diph.dwHow = DIPH_BYID; 
    dipRange.diph.dwObj = objectsEnum.objects[i].dwType;
    dipRange.lMin = -AXIS_RANGE_VALUE;
    dipRange.lMax = AXIS_RANGE_VALUE;

    pDevice->SetProperty( DIPROP_RANGE, &dipRange.diph );
  }

  devices.push_back( device );

  return;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK HwInput::EnumDevicesCallback( const DIDEVICEINSTANCE * pInstance, void * pContext )
{
  HwInput * This = (HwInput *)pContext;
  return This->EnumDevicesCallback( pInstance );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL HwInput::EnumDevicesCallback( const DIDEVICEINSTANCE * pInstance )
{
  NWin32Helper::com_ptr<IDirectInputDevice8> tmpDevice;
  HRESULT res = dinput->CreateDevice( pInstance->guidInstance, tmpDevice.GetAddr(), NULL );
  if( FAILED( res ) ) 
    return DIENUM_CONTINUE;

  AddEnumeratedDevice( tmpDevice );

  return DIENUM_CONTINUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK HwInput::EnumDeviceObjectsCallback( const DIDEVICEOBJECTINSTANCE * pObject, void * pContext )
{
  SDeviceObjectsEnum & objectsEnum = *(SDeviceObjectsEnum *)pContext;

  string controlName;
  EHwControlType::Enum type = EHwControlType::Key;

  DIOBJECTDATAFORMAT objectFormat;

  if ( pObject->guidType == GUID_XAxis )
  {
    type = EHwControlType::JoyAxis;
    controlName = objectsEnum.name;
    controlName += "_AXIS_X";
    objectFormat.pguid = &GUID_XAxis;
    objectFormat.dwOfs = FIELD_OFFSET( SInputDataFormat, lX );
  }
  else if ( pObject->guidType == GUID_YAxis )
  {
    type = EHwControlType::JoyAxis;
    controlName = objectsEnum.name;
    controlName += "_AXIS_Y";
    objectFormat.pguid = &GUID_YAxis;
    objectFormat.dwOfs = FIELD_OFFSET( SInputDataFormat, lY );
  }
  else if ( pObject->guidType == GUID_ZAxis )
  {
    type = EHwControlType::JoyAxis;
    controlName = objectsEnum.name;
    controlName += "_AXIS_Z";
    objectFormat.pguid = &GUID_ZAxis;
    objectFormat.dwOfs = FIELD_OFFSET( SInputDataFormat, lZ );
  }
  else if ( pObject->guidType == GUID_RxAxis )
  {
    type = EHwControlType::JoyAxis;
    controlName = objectsEnum.name;
    controlName += "_AXIS_RX";
    objectFormat.pguid = &GUID_RxAxis;
    objectFormat.dwOfs = FIELD_OFFSET( SInputDataFormat, lRX );
  }
  else if ( pObject->guidType == GUID_RyAxis )
  {
    type = EHwControlType::JoyAxis;
    controlName = objectsEnum.name;
    controlName += "_AXIS_RY";
    objectFormat.pguid = &GUID_RyAxis;
    objectFormat.dwOfs = FIELD_OFFSET( SInputDataFormat, lRY );
  }
  else if ( pObject->guidType == GUID_RzAxis )
  {
    type = EHwControlType::JoyAxis;
    controlName = objectsEnum.name;
    controlName += "_AXIS_RZ";
    objectFormat.pguid = &GUID_RzAxis;
    objectFormat.dwOfs = FIELD_OFFSET( SInputDataFormat, lRZ );
  }
  else if ( pObject->guidType == GUID_POV )
  {
    type = EHwControlType::PointOfView;
    controlName = objectsEnum.name;
    controlName += "_POV";
    objectFormat.pguid = &GUID_POV;
    objectFormat.dwOfs = FIELD_OFFSET( SInputDataFormat, lPOV );
  } 
  else if ( pObject->guidType == GUID_Slider )
  {
    type = EHwControlType::JoyAxis;
    controlName = objectsEnum.name;
    int nIndex = DIDFT_GETINSTANCE( pObject->dwType );
    if ( nIndex < 0 || nIndex > 3 )
      return DIENUM_CONTINUE;
    controlName += NStr::StrFmt( "_SLIDER%d", nIndex );
    objectFormat.pguid = &GUID_Slider;
    objectFormat.dwOfs = FIELD_OFFSET( SInputDataFormat, lSlider[nIndex] );
  }
  else if ( pObject->guidType == GUID_Button )
  {
    type = EHwControlType::Key;
    controlName = objectsEnum.name;
    controlName += NStr::StrFmt( "_BUTTON%d", DIDFT_GETINSTANCE( pObject->dwType ) );
    objectFormat.pguid = &GUID_Button;

    if( DIDFT_GETINSTANCE( pObject->dwType ) > 32 )
      return DIENUM_CONTINUE;

    objectFormat.dwOfs = FIELD_OFFSET( SInputDataFormat, bButton[ DIDFT_GETINSTANCE( pObject->dwType ) ] );
  }
  else if ( pObject->guidType == GUID_Key )
  {
    type = EHwControlType::Key;
    controlName = objectsEnum.name;
    controlName += NStr::StrFmt( "_KEY%d", DIDFT_GETINSTANCE( pObject->dwType ) );
    objectFormat.pguid = &GUID_Key;

    return DIENUM_CONTINUE;
  }
  else if ( pObject->guidType == GUID_Unknown )
  {
    type = EHwControlType::Key;
    controlName = objectsEnum.name;
    controlName += NStr::StrFmt( "_UNKNOWN%d", DIDFT_GETINSTANCE( pObject->dwType ) );
    objectFormat.pguid = &GUID_Unknown;

    return DIENUM_CONTINUE;
  }

  objectFormat.dwType = pObject->dwType;
  objectFormat.dwFlags = 0;
  objectsEnum.objects.push_back( objectFormat );

  objectsEnum.thisPtr->AddDeviceKey( type, objectsEnum.deviceId, GET_DIDEVICE_TYPE( objectFormat.dwType ), objectFormat.dwOfs, controlName );
  return DIENUM_CONTINUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HwInput::FindControlZ( const char * name ) const
{
  TControlsByName::iterator it = controlsByName.find( name );

  if ( it != controlsByName.end() )
    return it->second->ExternalId();

  return -1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HwInput::FindControl( const string & name ) const
{
  TControlsByName::iterator it = controlsByName.find( name );

  if ( it != controlsByName.end() )
    return it->second->ExternalId();

  return -1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string & HwInput::ControlName( int id ) const
{
  TControlsByExtId::iterator it = controlsByExtId.find( id );

  if ( it != controlsByExtId.end() )
    return it->second->Name();

  static string empty;
  return empty;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool HwInput::GetReadableControlName( int id, string & name ) const
{
  TControlsByExtId::iterator it = controlsByExtId.find( id );

  if ( it != controlsByExtId.end() )
  {
    HwControl * control = it->second;

    for ( int i = 0; i < devices.size(); ++i )
	  {
      const SDevice & device = devices[i];
		  if ( GET_DIDEVICE_TYPE( device.dwDevType ) != control->DeviceType() )
			  continue;

		  DIDEVICEOBJECTINSTANCE obj;
		  ZeroMemory( &obj, sizeof(obj) );
		  obj.dwSize = sizeof( obj );

		  if ( SUCCEEDED( device.device->GetObjectInfo( &obj, control->HwId(), DIPH_BYOFFSET ) ) )
      {
        name = obj.tszName;
        return true;
      }
      return false;
	  }
  }

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool HwInput::ControlIsAKey( int id ) const
{
  TControlsByExtId::iterator it = controlsByExtId.find( id );

  if ( it != controlsByExtId.end() )
    return it->second->Type() == EHwControlType::Key;

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HwInput::Poll( vector<HwEvent> & events )
{
  if ( !focused )
    return;

  for ( int i = 0; i < devices.size(); ++i )
  {
    SDevice & device = devices[i];

    if ( device.poll )
    {
      HRESULT res = device.device->Poll();
      if ( FAILED( res ) )
      {
        device.device->Acquire();
        //device.device->Poll();
      }
    }

    DWORD samplesNumber = DEFAULT_SAMPLE_BUFFER_SIZE;
    DIDEVICEOBJECTDATA objects[DEFAULT_SAMPLE_BUFFER_SIZE];
    HRESULT res = device.device->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), objects, &samplesNumber, 0 );

    if ( FAILED( res ) ) 
    {
      DebugTrace( "Re-acquiring input device '%s'...", device.name.c_str() );
      device.device->Acquire();
      continue;
    }

    for ( DWORD j = 0; j < samplesNumber; ++j )
    {
      const DIDEVICEOBJECTDATA & dod = objects[j];

      TControlsByHwId::iterator it = controlsByHwId.find( HwControlId( device.id, dod.dwOfs ) );
      NI_VERIFY( it != controlsByHwId.end(), NStr::StrFmt("Unknown input control 0x%lx", dod.dwOfs), continue );
      HwControl * control = it->second.GetPtr();

      if ( control->Type() == EHwControlType::Key )
      {
        bool activated = dod.dwData & 0x80 ? true : false;
        events.push_back( HwEvent( control->ExternalId(), activated ) );
        if ( s_verbosity >= VERBOSITY_HW )
          DebugTrace( "Key %s/%d data: %s", control->Name().c_str(), control->ExternalId(), activated ? "down" : "up" );
      }
      else if ( control->Type() == EHwControlType::MouseAxis )
      {
        float delta = (int)dod.dwData;
        events.push_back( HwEvent( control->ExternalId(), delta, false ) );
        if ( s_verbosity >= VERBOSITY_HW )
          DebugTrace( "Mouse axis %s/%d data: %.3f", control->Name().c_str(), control->ExternalId(), delta );
      }
      else if ( control->Type() == EHwControlType::JoyAxis )
      {
        float axis = (float)(int)dod.dwData / (float)AXIS_RANGE_VALUE;
        events.push_back( HwEvent( control->ExternalId(), axis, true ) );
        if ( s_verbosity >= VERBOSITY_HW )
          DebugTrace( "Joystick %s/%d data: %.3f", control->Name().c_str(), control->ExternalId(), axis );
      }
      else if ( control->Type() == EHwControlType::PointOfView )
      {
        float pov = ( dod.dwData == POV_NUETRAL_VALUE ) ? -1.0f : ( (float)dod.dwData / 100.0f ); // 0.0f...360.0f
        events.push_back( HwEvent( control->ExternalId(), pov, true ) );
        if ( s_verbosity >= VERBOSITY_HW )
          DebugTrace( "POV control %s/%d data: %.2f", control->Name().c_str(), control->ExternalId(), pov );
      }
      else
      {
        if ( s_verbosity >= VERBOSITY_HW )
          DebugTrace( "Unknown input control %s/%d data: 0x%08x (%d)", control->Name().c_str(), control->ExternalId(), dod.dwData, dod.dwData );
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HwInput::OnApplicationFocus( bool _focused )
{
  if ( focused == _focused )
    return;

  if ( _focused )
	{
		if ( !SetCoopLevel() )
			return;

    for ( int i = 0; i < devices.size(); ++i )
			if( FAILED( devices[i].device->Acquire() ) )
				return;
	}
	else
	{
		for ( int i = 0; i < devices.size(); ++i )
			if ( FAILED( devices[i].device->Unacquire() ) )
				return;
	}

  focused = _focused;
}

} //namespace Input
