#ifndef BINDSCONTAINERIMPL_H_INCLUDED
#define BINDSCONTAINERIMPL_H_INCLUDED

namespace Input
{

namespace ni_detail
{


struct BasicBindObserver : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( BasicBindObserver, BaseObjectST );

  virtual bool Execute( const Event & event, IBaseInterfaceST * pThis ) { return false; }
};



//  bool ::Handler();
class BindObserverBoolStaticFun : public BasicBindObserver
{
  NI_DECLARE_REFCOUNT_CLASS_1( BindObserverBoolStaticFun, BasicBindObserver );

  bool (*handler)();

public:
  BindObserverBoolStaticFun( bool (*_handler)() ) : handler( _handler ) {}

  bool Execute( const Event & event, IBaseInterfaceST * pThis )
  {
    if ( event.Type() == EEventType::Activation )
      return (*handler)();
    return false;
  }
};



//  bool ::Handler( const T & extra );
template <typename T>
class BindObserverBoolStaticFunExtra : public BasicBindObserver
{
  NI_DECLARE_REFCOUNT_CLASS_1( BindObserverBoolStaticFunExtra, BasicBindObserver );

  bool (*handler)( const T & );
  T extra;

public:
  BindObserverBoolStaticFunExtra( bool (*_handler)( const T & ), const T & _extra ) : handler( _handler ), extra( _extra ) {}

  bool Execute( const Event & event, IBaseInterfaceST * pThis )
  {
    if ( event.Type() == EEventType::Activation )
      return (*handler)( extra );
    return false;
  }
};



//  bool TObj::Handler();
template <typename TObj>
class BindObserverBoolMemberFun : public BasicBindObserver
{
  NI_DECLARE_REFCOUNT_CLASS_1( BindObserverBoolMemberFun, BasicBindObserver );

  bool (TObj::*handler)();

public:
  BindObserverBoolMemberFun( bool (TObj::*_handler)() ) : handler( _handler ) {}

  bool Execute( const Event & event, IBaseInterfaceST * pThis ) 
  { 
    if ( event.Type() == EEventType::Activation )
    {
      return ( nival_cast<TObj>( pThis )->*handler )(); 
    }
    return false;
  }
};



//  void TObj::Handler();
template <typename TObj>
class BindObserverVoidMemberFun : public BasicBindObserver
{
  NI_DECLARE_REFCOUNT_CLASS_1( BindObserverVoidMemberFun, BasicBindObserver );

  void (TObj::*handler)();

public:
  BindObserverVoidMemberFun( void (TObj::*_handler)() ) : handler( _handler ) {}

  bool Execute( const Event & event, IBaseInterfaceST * pThis ) 
  { 
    if ( event.Type() == EEventType::Activation )
      ( nival_cast<TObj>( pThis )->*handler )(); 
    return true;
  }
};



//  bool TObj::Handler( const T & extra );
template <typename TObj, typename T>
class BindObserverVoidMemberFunExtra : public BasicBindObserver
{
  NI_DECLARE_REFCOUNT_CLASS_1( BindObserverVoidMemberFunExtra, BasicBindObserver );

  bool (TObj::*handler)( const T & );
  T extra;

public:
  BindObserverVoidMemberFunExtra( bool (TObj::*_handler)( const T & ), const T & _extra ) : handler( _handler ), extra( _extra ) {}

  bool Execute( const Event & event, IBaseInterfaceST * pThis ) 
  { 
    if ( event.Type() == EEventType::Activation )
      ( nival_cast<TObj>( pThis ) ->*handler )( extra );
    return true;
  }
};



//  bool TObj::Handler( float delta, float value )
template <typename TObj>
class BindObserverBoolMemberFunScalars : public BasicBindObserver
{
  NI_DECLARE_REFCOUNT_CLASS_1( BindObserverBoolMemberFunScalars, BasicBindObserver );

  bool (TObj::*handler)( float, float );

public:
  BindObserverBoolMemberFunScalars( bool (TObj::*_handler)( float, float ) ) : handler( _handler ) {}

  bool Execute( const Event & event, IBaseInterfaceST * pThis ) 
  { 
    if ( event.Type() == EEventType::ScalarDelta || event.Type() == EEventType::ScalarValue )
    {
      float delta = ( event.Type() == EEventType::ScalarDelta ) ? event.Delta() : 0;
      float value = ( event.Type() == EEventType::ScalarValue ) ? event.Value() : 0;
      return ( nival_cast<TObj>( pThis ) ->*handler )( delta, value );
    }
    return false;
  }
};



//  bool TObj::Handler( float delta, float value, const T & extra );
template <typename TObj, typename T>
class BindObserverBoolMemberFunScalarsExtra : public BasicBindObserver
{
  NI_DECLARE_REFCOUNT_CLASS_1( BindObserverBoolMemberFunScalarsExtra, BasicBindObserver );

  bool (TObj::*handler)( const SSysParams &, float, float, const T & );
  T extra;

public:
  BindObserverBoolMemberFunScalarsExtra( bool (TObj::*_handler)( float, float, const T & ), const T & _extra ) : handler( _handler ), extra( _extra ) {}

  bool Execute( const Event & event, IBaseInterfaceST * pThis ) 
  { 
    if ( event.Type() == EEventType::ScalarDelta || event.Type() == EEventType::ScalarValue )
    {
      float delta = ( event.Type() == EEventType::ScalarDelta ) ? event.Delta() : 0;
      float value = ( event.Type() == EEventType::ScalarValue ) ? event.Value() : 0;
      return ( nival_cast<TObj>( pThis ) ->*handler )( delta, value, extra );
    }
    return false;
  }
};



//  bool TObj::Handler( const SSysParams & sysParams );
template <typename TObj>
class BindObserverBoolMemberFunSys : public BasicBindObserver
{
  NI_DECLARE_REFCOUNT_CLASS_1( BindObserverBoolMemberFunSys, BasicBindObserver );

  bool (TObj::*handler)( const SSysParams & );

public:
  BindObserverBoolMemberFunSys( bool (TObj::*_handler)( const SSysParams & ) ) : handler( _handler ) {}

  bool Execute( const Event & event, IBaseInterfaceST * pThis ) 
  { 
    NI_VERIFY( event.Type() == EEventType::System, "Wrong event type", return false );
    return ( nival_cast<TObj>( pThis )->*handler )( event.SysParams() );
  }
};



//  bool TObj::Handler( const SSysParams & sysParams, const T & extra );
template <typename TObj, typename T>
class BindObserverBoolMemberFunSysExtra : public BasicBindObserver
{
  NI_DECLARE_REFCOUNT_CLASS_1( BindObserverBoolMemberFunSysExtra, BasicBindObserver );

  bool (TObj::*handler)( const SSysParams &, const T & );
  T extra;

public:
  BindObserverBoolMemberFunSysExtra( bool (TObj::*_handler)( const SSysParams &, const T & ), const T & _extra ) : handler( _handler ), extra( _extra ) {}

  bool Execute( const Event & event, IBaseInterfaceST * pThis ) 
  { 
    NI_VERIFY( event.Type() == EEventType::System, "Wrong event type", return false );
    return ( nival_cast<TObj>( pThis ) ->*handler )( event.SysParams(), extra ); 
  }
};


} //namespace ni_detail

} //namespace Input

#endif //BINDSCONTAINERIMPL_H_INCLUDED
