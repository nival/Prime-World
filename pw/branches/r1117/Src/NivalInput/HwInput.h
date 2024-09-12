#ifndef HWINPUT_H_INCLUDED
#define HWINPUT_H_INCLUDED

#include "HwInputInterface.h"

//#undef _interface
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <windowsx.h>

#include "../System/Win32Helper.h"



namespace Input
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EHwControlType
{
  enum Enum { Key, MouseAxis, JoyAxis, PointOfView };
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HwControlId
{
public:
  HwControlId() : deviceId( 0 ), controlId( 0 ) {}
  HwControlId( int _deviceId, int _controlId ) : deviceId( _deviceId ), controlId( _controlId ) {}

  bool operator < ( const HwControlId & other ) const
  {
    if ( deviceId < other.deviceId )
      return true;
    if ( deviceId > other.deviceId )
      return false;
    return controlId < other.controlId;
  }

private:
  int deviceId, controlId;
};




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HwControl : public CObjectBase
{
  OBJECT_BASIC_METHODS( HwControl );

public:
  HwControl() : type( EHwControlType::Key ), deviceId( 0 ), deviceType( 0 ), hwId( -1 ), externalId( 0 ) {}

  HwControl( EHwControlType::Enum _type, int _deviceId, int _deviceType, int _hwId, int _externalId, const char * _name ) :
  type( _type ), deviceId( _deviceId ), deviceType( _deviceType ), hwId( _hwId ), externalId( _externalId ), name( _name )
  {
  }

  EHwControlType::Enum Type() const { return type; }
  int DeviceId() const { return deviceId; }
  int DeviceType() const { return deviceType; }
  int HwId() const { return hwId; }
  int ExternalId() const { return externalId; }
  const string & Name() const { return name; }

  HwControlId FullHwId() const { return HwControlId( deviceId, hwId ); }

private:
  EHwControlType::Enum  type;
  int                   deviceId;
  int                   deviceType;
  int                   hwId;
  int                   externalId;
  string                name;
};




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HwInput : public IHwInput, public CObjectBase
{
  OBJECT_BASIC_METHODS( HwInput );

public:
  HwInput();
  HwInput( HWND hWnd, HINSTANCE hInstance, bool debugMouse, bool nonExclusiveMode );
  void OnDestroyContents();
  ~HwInput();

  //IHwInput
  //TODO: maybe provide interface for HwControl and replace 'int id' with
  virtual int FindControlZ( const char * name ) const;
  virtual int FindControl( const string & name ) const;
  virtual const string & ControlName( int id ) const;
  virtual bool GetReadableControlName( int id, string & name ) const;
  virtual bool ControlIsAKey( int id ) const;
  virtual void Poll( vector<HwEvent> & events );
  virtual void OnApplicationFocus( bool focused );

private:
  struct SDevice
  {
    int     id;
    bool    poll;
    bool    needResync;
    string  name;
    DWORD   dwDevType;
    DWORD   dwFormatSize;
    NWin32Helper::com_ptr<IDirectInputDevice8> device;

    SDevice(): id( 0 ), poll( false ), needResync( false ), dwDevType( 0 ) {}
  };

  struct SInputDataFormat
  {
    LONG    lX;
    LONG    lY;
    LONG    lZ;
    LONG    lRX;
    LONG    lRY;
    LONG    lRZ;
    LONG    lPOV;
    BYTE    bButton[32];
    LONG    lSlider[4];
  };

  struct SDeviceObjectsEnum
  {
    HwInput* thisPtr;
	  int      deviceId;
	  string   name;
	  vector<DIOBJECTDATAFORMAT> objects;

	  SDeviceObjectsEnum( HwInput * _thisPtr = 0, int _deviceId = 0 ) : thisPtr( _thisPtr ), deviceId( _deviceId ) {}
  };

  typedef vector<SDevice> TDevices;

  typedef map<HwControlId, CObj<HwControl>>  TControlsByHwId;
  typedef map<string, CObj<HwControl>>  TControlsByName;
  typedef map<int, CObj<HwControl>>  TControlsByExtId;

  HWND              hWindow;
  bool              nonExclusiveMode;
  NWin32Helper::com_ptr<IDirectInput8>  dinput;
  TDevices          devices;
  bool              focused;
  bool              coopLevelSet;
  int               gamePadsNum, drivingWheelsNum, joysticksNum, gameControlsNum;
  int               currentExternalId;
  TControlsByHwId   controlsByHwId;
  TControlsByName   controlsByName;
  TControlsByExtId  controlsByExtId;

  static HMODULE GetDllModuleHandle();
  static HWND GetTopLevelWindow( HWND hWnd );
  bool SetCoopLevel();
  static bool CheckMouseAvailability( bool debugMouse );
  bool CreateMouseDevice();
  bool CreateKeyboardDevice();

  void AddDevice( IDirectInputDevice8 * pDevice, DWORD dwFormatSize );
  void AddDeviceKey( EHwControlType::Enum type, int deviceId, int deviceType, int controlId, const string & name );
  void AddDeviceKeys( int deviceId, int deviceType );
  
  void AddEnumeratedDevice( IDirectInputDevice8 * pDevice );

  static BOOL CALLBACK EnumDevicesCallback( const DIDEVICEINSTANCE * pInstance, void * pContext );
  BOOL EnumDevicesCallback( const DIDEVICEINSTANCE * pInstance );

  static BOOL CALLBACK EnumDeviceObjectsCallback( const DIDEVICEOBJECTINSTANCE * pObject, void * pContext );
};

} //namespace Input

#endif //HWINPUT_H_INCLUDED
