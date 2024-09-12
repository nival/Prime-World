//--------------------------------------------------------------------------------------
// File: ConfigDatabase.h
//
// Header file for configuration database object.
//
// Based on Microsoft DX SDK ConfigDatabase sample.
//--------------------------------------------------------------------------------------
#pragma once
#ifndef __CONFIGDATABASE_H__
#define __CONFIGDATABASE_H__

//#include <d3d9.h>

typedef pair <string, string>    StringPair;


typedef struct
{
    WCHAR name[64];
    DWORD DriverVersionLowPart;
    DWORD DriverVersionHighPart;
    DWORD VendorID;
    DWORD DeviceID;
    DWORD SubSysID;
    DWORD Revision;
} SOUND_DEVICE;


//HRESULT InitSoundInformation( REFGUID DsoundGuid, SOUND_DEVICE* pSndDev );


//-----------------------------------------------------------------------------
// IConfigDatabase
//
class IConfigDatabase
{
public:

    // Create an instance of the interface
    static IConfigDatabase* Create();

    // Load the config information in the text file given.  See below for information
    // on the format of the text file.  SystemMemory and VideoMemory are in MB.
    // CPU Speed is in MHz
    virtual bool            Load( LPCTSTR FileName,
                                  const SOUND_DEVICE& soundDevice,
                                  const D3DADAPTER_IDENTIFIER9& DDid,
                                  const D3DCAPS9&,
                                  DWORD SystemMemory,
                                  DWORD VideoMemory,
                                  DWORD CPUSpeed ) = 0;

    // Release the object.  Call this when done with the interface.
    virtual void            Release() = 0;

    // Get a vector of the resulting property set.  The first member of the string
    // pair is the name and the second is the value.
    virtual const vector <StringPair>& GetAggregateProperties() const = 0;
    virtual const vector <StringPair>* GetNamedProperties( const char* ) const = 0;

    // The following provide non-STL access to the device property set.
    virtual unsigned int    GetDevicePropertyCount() const = 0;
    virtual const char* GetDeviceProperty( unsigned int ) const = 0;
    virtual const char* GetDeviceValue( unsigned int ) const = 0;

    // The following provide non-STL access to the requirements
    virtual unsigned int    GetRequirementsPropertyCount() const = 0;
    virtual const char* GetRequirementsProperty( unsigned int ) const = 0;
    virtual const char* GetRequirementsValue( unsigned int ) const = 0;

    // The graphics device and vendor strings as given by the config file.
    virtual const char* GetGfxDeviceString() const = 0;
    virtual const char* GetGfxVendorString() const = 0;

    // The sound device and vendor strings as given by the config file.
    virtual const char* GetSoundDeviceString() const = 0;
    virtual const char* GetSoundVendorString() const = 0;

    //
    // If an error has occurred, more details can be found here.
    //
    virtual bool            IsError() const = 0;
    virtual const char* GetErrorString() const = 0;

};

//-------------------------------------------------------------------------------------
// EXAMPLE USAGE
//
// IConfigDatabase* pCDB = IConfigDatabase::Create();
// if (!pCDB->Load("config.txt", d3dAdId, d3dCaps, SysMem, VidMem))
// {
//   ... error ...
// }
//
//  ... use properties ...
//
// pCDB->Release();
//

//-------------------------------------------------------------------------------------
//  SYNTAX OF CONFIG FILE
//
//
// First section is a list of PropertySets.  A PropertySet is a set of name/value pairs.
// Each set must end with a "Break" line.  PropertySets can refer to other property sets
// that preceed it in the file.
//
// Second section is an ApplyToAll block that is processed on all cards.  It is typically
// used to setup defaults based on caps.
//
// Next section is the vendor list.  This provides a way to make card specific changes.
//
// The program first searches for DisplayVendor = 0xXXXX (for display hardware) or
// AudioVendor = 0xXXXX (for audio hardware) that matches the current card.
// It then skips any other *Vendor = lines to skip over duplicate vendors for identical devices
// Any properties found after the 'Vendor =' lines and before the first device ID will be properties
// for all devices from that vendor.  This properties list must end with a break.
//
// The program will then search for a device ID that matches, the device ID is the first hex number on a line.
// Any properties found after a device ID and before the next "break" will be returned.
// Any device IDs found before the next break are ignored.  This allows multiple device IDs to
// share a property list.
//
// Each list of device IDs may end with the unknown keyword.  Unrecognized devices will use the set found
// here.
//
// The Vendor list may end with a "Vendor = unknown" section that functions much like the unknown device.
//
// Note on property lists --
// If a property is found twice, or overrides a unknown property, only the last one specified will be returned.
// Properties can consist of 'property=value'
// Properties can consist of single keywords (like Disable1024*768)
// Properties cannot start with numbers (they may be confused with devices otherwise)
// Properties are case insensitive and are converted to lower case.
// Values are also converted to lower case, unless surround by quotes. Values can only contain spaces inside quotes ie: "Bad Card"
//
// Other Logic:
//
// IF condition
//  xxx
//  xxx
// ENDIF
//
// IF/ENDIF can only occur in any property set. They cannot surround multiple devices. IF/ENDIF can be nested.
//
// condition can be any of the following:
//
// ram = value                             (ie:  if ram > 64 )
// videoram = value                        (ie:  if videoram < 16 )
// SubSysID = value                        (ie:  if SubSysID = 2345 )
// Revision = value                        (ie:  if Revision = 1 )
// driver = value.value.value.value        (ie:  if driver = 4.1.25.1111 )
// guid = hex-hex-hex-hex-hex              (ie:  if guid = D7B71F83-6340-11CF-4C73-0100A7C2C935 )
// os = value                              (ie:  if os > win98 )
//
// Other conditions include all the DWORD memebers of the D3DCAPS8 structure.  For example,
//
// DevCaps & Flag
//
// You can use '=' '==' '<>' '!=' '>=' '<=' '>' '<' or '&' in comparissions
// Value can be a decimal or hex number (starting with 0x)
//
// Ram is system memory
// VideoRam is video memory
// Driver is the driver version number
// SubSysID is the driver subsystem ID number
// Revision is the driver revision number
// GUID is the single identified for hardware and driver this can only be compared as '=' '==' '!=' or '<>'
// os is a value Win95=0, Win98=1, Win98SE=2, WinME=3, Win2K=4, WinXP=5
//

#endif // __CONFIGDATABASE_H__
