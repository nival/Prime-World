#ifndef INPUTCOMMANDINSTANCE_H_INCLUDED
#define INPUTCOMMANDINSTANCE_H_INCLUDED

#include "InputEvent.h"

namespace Input
{

_interface IHwInput;
class HwEvent;
class Event;
class ControlsSet;
class Section;


typedef list<CObj<ControlsSet>>  TControlsSet;



_interface ICommandInstanceImplementation : public ICommandInstance
{
public:
  //'events' are not cleared; instead new objects appended to
  virtual void ProcessHwEvent( const HwEvent & hwEvent, vector<Event> & events ) = 0;
  virtual void Update( float deltaTime, vector<Event> & events, bool appFocused ) = 0;
  virtual bool Inverted() const = 0;
  virtual void AddBind( const vector<string> & controlNames, Section * section, float factor, bool factorIsUndefined, bool isRebind = false ) = 0;
  virtual TControlsSet & AccessControlsSet() = 0;
  virtual void ClearControlsSupersets() = 0;
  virtual void UpdateControlsSupersets( TControlsSet & otherSets ) = 0;
  virtual void Reset( vector<Event> &events ) = 0;
};




class CommandInstance : public ICommandInstanceImplementation, public CObjectBase
{
  OBJECT_BASIC_METHODS( CommandInstance );

public:
  CommandInstance();
  CommandInstance( IHwInput * _hwInput, const char * _name, bool _inverted = false );

  //ICommandInstance:
  const string & Name() const { return name; }
  bool IsActiveNow() const { return currentKeysState; }

  //ICommandInstanceImplementation
  virtual void ProcessHwEvent( const HwEvent & hwEvent, vector<Event> & events );
  virtual void Update( float deltaTime, vector<Event> & events, bool appFocused );

  virtual void Reset( vector<Event> &events );
  virtual bool Inverted() const { return inverted; }
  virtual void AddBind( const vector<string> & controlNames, Section * section, float factor, bool factorIsUndefined, bool isRebind = false );
  virtual TControlsSet & AccessControlsSet() { return controls; }
  virtual void ClearControlsSupersets();
  virtual void UpdateControlsSupersets( TControlsSet & otherSets );

private:
  typedef list<CObj<ControlsSet>>  TControlsSet;

  CPtr<IHwInput>    hwInput;
  string            name;
  bool              inverted;
  TControlsSet      controls;
  bool              currentKeysState;
};


} //namespace Input

#endif //INPUTCOMMANDINSTANCE_H_INCLUDED
