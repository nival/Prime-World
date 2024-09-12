#include "stdafx.h"
#include "ControlsSet.h"

#include "HwInputInterface.h"
#include "Section.h"

BASIC_REGISTER_CLASS( Input::ControlsSet );

namespace Input
{


void ControlsSet::AddKey( int hwKeyId )
{
  for ( int i = 0; i < keys.size(); ++i )
    if ( keys[i].controlId == hwKeyId )
      return;

  keys.push_back( SKey( hwKeyId ) );
}



void ControlsSet::SetAxis( int hwAxisId )
{
  axisHwCtrlId = hwAxisId;
}



void ControlsSet::ProcessHwKeyEvent( const HwEvent & hwEvent, bool & _allKeysPressed )
{
  NI_ASSERT( !keys.empty() || GotAxis(), "Empty controls combination" );
  NI_ASSERT( hwEvent.Type() == EHwEventType::Key, "" );

  if ( IsValid( section ) && !section->Enabled() )
    return;

  //first check superset controls set
  //NOTE: as a rusult, 'ProcessHwKeyEvent' may be called _multiple_ times for some combinations and for SINGLE hw-event
  bool supersetPressed = false;
  for ( TCombinations::iterator it = supersets.begin(); it != supersets.end(); ++it )
  {
    NI_ASSERT( IsValid( * it ), "" );
    bool result = false;
    (*it)->ProcessHwKeyEvent( hwEvent, result );
    supersetPressed |= (*it)->allKeysPressed;
  }

  //then check own controls
  bool state = true;
  for ( int i = 0; i < keys.size(); ++i )
  {
    if ( !supersetPressed )
      if ( keys[i].controlId == hwEvent.ControlId() )
        keys[i].pressed = hwEvent.Activated();
    state = state && keys[i].pressed;
  }

  allKeysPressed = state;

  if ( allKeysPressed && !GotAxis() )
    _allKeysPressed = true;
}



void ControlsSet::ProcessHwMouseEvent( const HwEvent & hwEvent, float & delta, float & value, bool & _deltaUpdated, bool & _valueUpdated )
{
  NI_ASSERT( hwEvent.Type() == EHwEventType::Delta || hwEvent.Type() == EHwEventType::Scalar, "" );

  if ( IsValid( section ) && !section->Enabled() )
    return;

  //If keys are defined, axis are working only when all keys are pressed
  if ( !keys.empty() && !allKeysPressed )
    return;

  if ( GotAxis() )
    if ( hwEvent.ControlId() == axisHwCtrlId )
    {
      if ( hwEvent.Type() == EHwEventType::Delta )
      {
        delta += factor * hwEvent.Delta();
        _deltaUpdated = true;
      }
      else if ( hwEvent.Type() == EHwEventType::Scalar )
      {
        delta = factor * hwEvent.Value();
        _valueUpdated = true;
      }
    }
}



void ControlsSet::Reset()
{
  for ( int i = 0; i < keys.size(); ++i )
    keys[i].pressed = false;
  allKeysPressed = false;
}



bool ControlsSet::Include( ControlsSet * other )
{
  //Important: we require _strong_ operation:
  if ( keys.size() == other->keys.size() )
    return false;

  //FIXME: it could be optimized with pre-sorted arrays
  for ( int i = 0; i < other->keys.size(); ++i )
  {
    const int id = other->keys[i].controlId;
    int j = 0;
    for ( ; j < keys.size(); ++j )
      if ( keys[j].controlId == id )
        break;
    if ( j == keys.size() ) //control 'id' not found
      return false;
  }

  //Add superset controls set
  for ( TCombinations::iterator it = other->supersets.begin(); it != other->supersets.end(); ++it )
    if ( *it == this )
      return true;
  other->supersets.push_back( this );
  return true;
}

void ControlsSet::GetControls(vector<int>& controls) const
{
  controls.resize(keys.size());

  for (int i = keys.size(); i > 0; )
  {
    --i;
    controls[i] = keys[i].controlId;
  }
}

} //namespace Input
