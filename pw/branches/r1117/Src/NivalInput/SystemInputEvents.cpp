#include "stdafx.h"
#include "SystemInputEvents.h"

#include "InputCommandInstance.h"
#include "Binds.h"

#include "../System/MainFrame.h"

namespace Input
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SystemCommandMock : public ICommandInstanceImplementation, public CObjectBase
{
  OBJECT_BASIC_METHODS( SystemCommandMock );

public:
  SystemCommandMock( const char * _name ) : name( _name ) {}

  //ICommandInstance:
  virtual const string & Name() const { return name; }
  virtual bool IsActiveNow() const { return false; }

  //ICommandInstanceImplementation
  virtual void ProcessHwEvent( const HwEvent & hwEvent, vector<Event> & events ) {}
  virtual void Update( float deltaTime, vector<Event> & events, bool appFocused ) {}
  virtual bool Inverted() const { return false; }
  virtual void AddBind( const vector<string> & controlNames, Section * section, float factor, bool factorIsUndefined, bool isRebind = false ) {}
  virtual TControlsSet & AccessControlsSet() { return empty; }
  virtual void ClearControlsSupersets() {}
  virtual void UpdateControlsSupersets( TControlsSet & otherSets ) {}
  virtual void Reset( vector<Event> &events ) {}

private:
  string  name;
  TControlsSet  empty;

  SystemCommandMock() {}
};






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SystemEvents::SystemEvents( Binds * binds )
{
  cmdChar     = DefineCommandMock( binds, "win_char" );
  cmdKeyDown  = DefineCommandMock( binds, "win_key_down" );
  cmdKeyUp    = DefineCommandMock( binds, "win_key_up" );

  cmdMouseMove  = DefineCommandMock( binds, "win_mouse_move" );
  cmdMouseOut   = DefineCommandMock( binds, "win_mouse_out" );
  cmdMouseDisabled = DefineCommandMock( binds, "win_mouse_disabled" );
  cmdWheelDown  = DefineCommandMock( binds, "win_mouse_wheel_down" );
  cmdWheelUp    = DefineCommandMock( binds, "win_mouse_wheel_up" );

  cmdMouseLeftDblClick  = DefineCommandMock( binds, "win_left_button_dblclk" );
  cmdMouseRightDblClick = DefineCommandMock( binds, "win_right_button_dblclk" );

  cmdMouseLeftDown    = DefineCommandMock( binds, "win_left_button_down" );
  cmdMouseLeftUp      = DefineCommandMock( binds, "win_left_button_up" );
  cmdMouseRightDown   = DefineCommandMock( binds, "win_right_button_down" );
  cmdMouseRightUp     = DefineCommandMock( binds, "win_right_button_up" );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SystemEvents::Pump( vector<Input::Event> & events )
{
  NMainFrame::SWindowsMsg winMsg;
	while ( NMainFrame::GetMessage( &winMsg ) )
	{
    //keyboard section
    switch ( winMsg.msg )
    {
      default:
        break;

      case NMainFrame::SWindowsMsg::KEY_CHAR:
      {

        if (winMsg.nKey < 256)
        {
          char sz[2] = { (char)winMsg.nKey, 0 };
          wstring wcharBuffer;
          NStr::ToUnicode( &wcharBuffer, string( sz ) );
          if ( wcharBuffer.size() == 1 )
            events.push_back( Event( cmdChar, SSysParams( wcharBuffer[0], winMsg.nRep ) ) );
        }
        else
          events.push_back( Event( cmdChar, SSysParams( winMsg.nKey < 0xD800 ? winMsg.nKey : L'?', winMsg.nRep ) ) );
        continue;
      }

      case NMainFrame::SWindowsMsg::KEY_DOWN:
        events.push_back( Event( cmdKeyDown, SSysParams( winMsg.nKey, winMsg.nRep ) ) );
        continue;

      case NMainFrame::SWindowsMsg::KEY_UP:
        events.push_back( Event( cmdKeyUp, SSysParams( winMsg.nKey, winMsg.nRep ) ) );
        continue;
    }

    //mouse section
    CPtr<ICommandInstance> cmd;
    switch ( winMsg.msg )
    {
      default:
        NI_ALWAYS_ASSERT( "Unknown main frame message" );
        break;

      case NMainFrame::SWindowsMsg::MOUSE_MOVE:
        cmd = cmdMouseMove;
        break;

      case NMainFrame::SWindowsMsg::MOUSE_OUT:
        cmd = cmdMouseOut;
        break;
        
      case NMainFrame::SWindowsMsg::MOUSE_DISABLED:
       cmd = cmdMouseDisabled;
       break;
       
      case NMainFrame::SWindowsMsg::MOUSE_WHEEL: 
        cmd = ( GET_WHEEL_DELTA_WPARAM( winMsg.dwFlags ) < 0 ) ? cmdWheelDown : cmdWheelUp;
        break;

      case NMainFrame::SWindowsMsg::MOUSE_RB_DBLCLK: 
        cmd = cmdMouseRightDblClick;
        break;

      case NMainFrame::SWindowsMsg::MOUSE_LB_DBLCLK: 
        cmd = cmdMouseLeftDblClick;
        break;

      case NMainFrame::SWindowsMsg::MOUSE_RB_DOWN: 
        cmd = cmdMouseRightDown;
        break;

      case NMainFrame::SWindowsMsg::MOUSE_LB_DOWN: 
        cmd = cmdMouseLeftDown;
        break;

      case NMainFrame::SWindowsMsg::MOUSE_RB_UP: 
        cmd = cmdMouseRightUp;
        break;

      case NMainFrame::SWindowsMsg::MOUSE_LB_UP: 
        cmd = cmdMouseLeftUp;
        break;
    }

    if ( IsValid( cmd ) )
      events.push_back( Event( cmd, SSysParams( winMsg.x, winMsg.y, winMsg.dwFlags ) ) );
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ICommandInstance * SystemEvents::DefineCommandMock( Binds * binds, const char * name )
{
  SystemCommandMock * cmd = new SystemCommandMock( name );
  binds->DefineCustomCommand( name, cmd );
  return cmd;
}

} //namespace Input
