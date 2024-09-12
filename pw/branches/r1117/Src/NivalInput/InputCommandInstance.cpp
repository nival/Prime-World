#include "stdafx.h"
#include "InputCommandInstance.h"

#include "HwInputInterface.h"
#include "ControlsSet.h"

namespace Input
{


CommandInstance::CommandInstance() :
inverted( false ),
currentKeysState( false )
{
}



CommandInstance::CommandInstance( IHwInput * _hwInput, const char * _name, bool _inverted ) :
hwInput( _hwInput ),
name( _name ),
inverted( _inverted ),
currentKeysState( false )
{
}



void CommandInstance::ProcessHwEvent( const HwEvent & hwEvent, vector<Event> & events )
{
  //let's detect state change according to 'inverted' flag
  if ( hwEvent.Type() == EHwEventType::Key )
  {
    bool keysPressed = false;
    for ( TControlsSet::iterator it = controls.begin(); it != controls.end(); ++it )
      (*it)->ProcessHwKeyEvent( hwEvent, keysPressed );

    if ( !inverted && ( keysPressed && !currentKeysState ) )
    {
      events.push_back( Event( this ) );
    }
    else if ( inverted && ( !keysPressed && currentKeysState ) )
    {
      events.push_back( Event( this ) );
    }
    currentKeysState = keysPressed;
    return;
  }

  //not a key
  float delta = 0;
  float value = 0;
  bool deltaUpd = false;
  bool valueUpd = false;

  for ( TControlsSet::iterator it = controls.begin(); it != controls.end(); ++it )
      (*it)->ProcessHwMouseEvent( hwEvent, delta, value, deltaUpd, valueUpd );

  if ( deltaUpd )
    events.push_back( Event( this, delta, true ) );

  if ( valueUpd )
    events.push_back( Event( this, value, false ) );
}



void CommandInstance::Update( float deltaTime, vector<Event> & events, bool appFocused )
{
  if ( appFocused )
  {
    float delta = 0;
    for ( TControlsSet::iterator it = controls.begin(); it != controls.end(); ++it )
      if ( (*it)->Pressed() )
        delta += (*it)->Factor() * deltaTime;

    if ( delta )
      events.push_back( Event( this, delta, true ) );
  }
  else
  {
    Reset(events);
  }
}



void CommandInstance::AddBind( const vector<string> & controlNames, Section * section, float factor, bool factorIsUndefined, bool isRebind )
{
  NI_ASSERT( IsValid( hwInput ), "" );

  if (isRebind)
  {
    // сохраняем контролы с другим фактором
    TControlsSet savedControls;
    if (!factorIsUndefined)
    {
      for ( TControlsSet::iterator it = controls.begin(); it != controls.end(); ++it )
      {
        if ((*it)->Factor() != factor)
          savedControls.push_back((*it));
      }
    }

    ClearControlsSupersets();
    controls.clear();

    for ( TControlsSet::iterator it = savedControls.begin(); it != savedControls.end(); ++it )
    {
      controls.push_back((*it));
    }
  }

  controls.push_back( new ControlsSet( section ) );
  CObj<ControlsSet> ctrl = controls.back();

  for ( int i = 0; i < controlNames.size(); ++i )
  {
    int ctrlId = hwInput->FindControl( controlNames[i] );
    NI_DATA_VERIFY( ctrlId >= 0, NStr::StrFmt( "Unknown input control '%s' for bind '%s'", controlNames[i].c_str(), name.c_str() ), return );

    if ( hwInput->ControlIsAKey( ctrlId ) )
      ctrl->AddKey( ctrlId );
    else
    {
      NI_DATA_VERIFY( !ctrl->GotAxis(), NStr::StrFmt( "Multiple axes defined for bind '%s'", name.c_str() ), return );
      ctrl->SetAxis( ctrlId );
    }
  }

  if ( factorIsUndefined )
  {
    if ( ctrl->GotAxis() )
      ctrl->SetFactor( 1.0 );
    else
      ctrl->SetFactor( 0 );
  }
  else
    ctrl->SetFactor( factor );
}



void CommandInstance::ClearControlsSupersets()
{
  for ( TControlsSet::iterator it = controls.begin(); it != controls.end(); ++it )
    (*it)->ClearSupersets();
}



void CommandInstance::UpdateControlsSupersets( TControlsSet & otherSets )
{
  for ( TControlsSet::iterator meIt = controls.begin(); meIt != controls.end(); ++meIt )
  {
    CObj<ControlsSet> me = *meIt;
    for ( TControlsSet::const_iterator otherIt = otherSets.begin(); otherIt != otherSets.end(); ++otherIt )
    {
      CObj<ControlsSet> other = *otherIt;
      //FIXME: inefficient but obvious
      me->Include( other );
      other->Include( me );
    }
  }
}

void CommandInstance::Reset( vector<Event> &events )
{
  //Reset all keys if app is not focused
  for ( TControlsSet::iterator it = controls.begin(); it != controls.end(); ++it )
    (*it)->Reset();

  if ( inverted && currentKeysState )
  {
    events.push_back( Event( this ) );
    currentKeysState = false;
  }
}
} //namespace Input
