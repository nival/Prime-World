#ifndef HWINPUTINTERFACE_H_INCLUDED
#define HWINPUTINTERFACE_H_INCLUDED

namespace Input
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EHwEventType
{
  enum Enum { Key, Scalar, Delta };
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HwEvent
{
public:
  HwEvent() : type( EHwEventType::Key ), id( -1 ), activated( false ), value( 0 ) {}
  HwEvent( int _controlId, bool _activated ) : type( EHwEventType::Key ), id( _controlId ), activated( _activated ), value( 0 ) {}
  HwEvent( int _controlId, float _value, bool absoluteValue ) : type( absoluteValue ? EHwEventType::Scalar : EHwEventType::Delta ), id( _controlId ), activated( false ), value( _value ) {}

  int ControlId() const { return id; }
  EHwEventType::Enum Type() const { return type; }
  bool Activated() const { NI_ASSERT( type == EHwEventType::Key, "" ); return activated; }
  float Value() const { NI_ASSERT( type == EHwEventType::Scalar, "" ); return value; }
  float Delta() const { NI_ASSERT( type == EHwEventType::Delta, "" ); return value; }

private:
  EHwEventType::Enum  type;

  int     id;
  bool    activated;
  float   value;
};




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IHwInput : public IObjectBase
{
public:
  virtual int FindControlZ( const char * name ) const = 0;
  virtual int FindControl( const string & name ) const = 0;
  virtual const string & ControlName( int id ) const = 0;
  virtual bool GetReadableControlName( int id, string & name ) const = 0;
  virtual bool ControlIsAKey( int id ) const = 0;
  virtual void Poll( vector<HwEvent> & events ) = 0;
  virtual void OnApplicationFocus( bool focused ) = 0;
};




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IHwInput * CreateHwInput( HWND hWnd, HINSTANCE hInstance, bool debugMouse, bool nonExclusiveMode );

int GetVerbosityLevel();

} //namespace Input

#endif //HWINPUTINTERFACE_H_INCLUDED
