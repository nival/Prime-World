#ifndef BINDSCONTAINER_H_INCLUDED
#define BINDSCONTAINER_H_INCLUDED

#include "InputCommandRef.h"
#include "InputEvent.h"

#include "BindsContainerImpl.hpp"

namespace Input
{


///// Possible handlers /////
//AddActivationHandler:
//  bool ::Handler();
//  bool ::Handler( const T & extra );
//  bool TObj::Handler();
//  void TObj::Handler();
//  bool TObj::Handler( const T & extra );
//AddScalarHandler:
//  bool TObj::Handler( float delta, float value );
//  bool TObj::Handler( float delta, float value, const T & extra );
//AddSystemHandler:
//  bool TObj::Handler( const SSysParams & sysParams );
//  bool TObj::Handler( const SSysParams & sysParams, const T & extra );

namespace ni_detail
{

//Helper class
class BindObserverHelper
{
  CommandReference  bind;
  Strong<ni_detail::BasicBindObserver>  observer;
public:
  BindObserverHelper( const char * commandName, ni_detail::BasicBindObserver * _observer ) : bind( commandName ), observer( _observer ) {}

  bool ProcessEvent( const Event & event, BaseObjectST * pThis )
  {
    if ( bind.ProcessEvent( event ) )
      return observer->Execute( event, pThis );
    return false;
  }
};

} //namespace ni_detail


//ex. CGMORegContainer
class BindsContainer
{
public:
  // bool ::Handler();
  void AddActivationHandler( const char * commandName, bool (*handler)() )
  {
    AddRawObserver( commandName, new ni_detail::BindObserverBoolStaticFun( handler ) );
  }

  // bool ::Handler( const T & extra );
  template <typename T>
  void AddActivationHandler( const char * commandName, bool (*handler)( const T & ), const T & extra )
  {
    AddRawObserver( commandName, new ni_detail::BindObserverBoolStaticFunExtra<T>( handler, extra ) );
  }

  // bool TObj::Handler();
  template <typename TObj>
  void AddActivationHandler( const char * commandName, bool (TObj::*handler)() )
  {
    AddRawObserver( commandName, new ni_detail::BindObserverBoolMemberFun<TObj>( handler ) );
  }

  // void TObj::Handler();
  template <typename TObj>
  void AddActivationHandler( const char * commandName, void (TObj::*handler)() )
  {
    AddRawObserver( commandName, new ni_detail::BindObserverVoidMemberFun<TObj>( handler ) );
  }

  // bool TObj::Handler( const T & extra );
  template <typename TObj, typename T>
  void AddActivationHandler( const char * commandName, bool (TObj::*handler)( const T & ), const T & extra )
  {
    AddRawObserver( commandName, new ni_detail::BindObserverVoidMemberFunExtra<TObj, T>( handler, extra ) );
  }

  // bool TObj::Handler( float delta, float value );
  template <typename TObj>
  void AddScalarHandler( const char * commandName, bool (TObj::*handler)( float, float ) )
  {
    AddRawObserver( commandName, new ni_detail::BindObserverBoolMemberFunScalars<TObj>( handler ) );
  }

  // bool TObj::Handler( float delta, float value, const T & extra );
  template <typename TObj, typename T>
  void AddScalarHandler( const char * commandName, bool (TObj::*handler)( float, float, const T & ), const T & extra )
  {
    AddRawObserver( commandName, new ni_detail::BindObserverBoolMemberFunScalarsExtra<TObj, T>( handler, extra ) );
  }

  // bool TObj::Handler( const SSysParams & );
  template <typename TObj>
  void AddSystemHandler( const char * commandName, bool (TObj::*handler)( const SSysParams & ) )
  {
    AddRawObserver( commandName, new ni_detail::BindObserverBoolMemberFunSys<TObj>( handler ) );
  }

  // bool TObj::Handler( const SSysParams & sysParams, const T & extra );
  template <typename TObj, typename T>
  void AddSystemHandler( const char * commandName, bool (TObj::*handler)( const SSysParams &, const T & ), const T & extra )
  {
    AddRawObserver( commandName, new ni_detail::BindObserverBoolMemberFunSysExtra<TObj, T>( handler, extra ) );
  }



  //common callback registration
  virtual void AddRawObserver( const char * commandName, ni_detail::BasicBindObserver * observer )
  {
    eventRegisters.push_back( ni_detail::BindObserverHelper( commandName, observer ) );
  }

  bool ProcessEvent( const Event & event, BaseObjectST * pThis )
  {
    for ( TBindObservers::iterator it = eventRegisters.begin(); it != eventRegisters.end(); ++it )
      if ( it->ProcessEvent( event, pThis) )
        return true;

    return false;
  }

  bool Empty() const { return eventRegisters.empty(); }

private:
  typedef vector<ni_detail::BindObserverHelper> TBindObservers;
  TBindObservers eventRegisters;
};

} //namespace Input

#endif //BINDSCONTAINER_H_INCLUDED
