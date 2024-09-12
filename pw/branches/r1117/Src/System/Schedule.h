#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED

#include "System/SyncPrimitives.h"
#include "System/JobThread.h"


typedef void * TScheduleAuxParam;

class IScheduleCallback : public IBaseInterfaceMT
{
public:
  virtual void AsyncEvent( TScheduleAuxParam _aux ) = 0;
};



class Schedule : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( Schedule, BaseObjectMT );
public:
  Schedule( bool _syncMode = false );

  void Add( IScheduleCallback * _evt, TScheduleAuxParam _aux );
  void Add( IScheduleCallback * _evt, timer::Time _when, TScheduleAuxParam _aux );

  template <class T>
  void Add( T * _object, void (T::*_func)( TScheduleAuxParam ), TScheduleAuxParam _aux ) {
    Add( new FunctionCallback<T>( _object, _func ), _aux );
  }

  template <class T>
  void Add( T * _object, void (T::*_func)( TScheduleAuxParam ), timer::Time _when, TScheduleAuxParam _aux ) {
    Add( new FunctionCallback<T>( _object, _func ), _when, _aux );
  }

  void SyncPoll( timer::Time _now );

private:
  class Worker;
  StrongMT<Worker> worker;
  StrongMT<threading::JobThread> thread;


  template <class T>
  class FunctionCallback : public IScheduleCallback, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( FunctionCallback, IScheduleCallback, BaseObjectMT );
  public:
    FunctionCallback( T * _object, void (T::*_func)( TScheduleAuxParam ) ) :
    object( _object ),
    func( _func )
    {
    }

    virtual void AsyncEvent( TScheduleAuxParam _aux )
    {
      if ( StrongMT<T> locked = object.Lock() )
        (locked.Get()->*func)( _aux );
    }

  private:
    WeakMT<T> object;
    void (T::*func)( TScheduleAuxParam );
  };
};

#endif //SCHEDULE_H_INCLUDED
