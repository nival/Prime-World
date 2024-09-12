#ifndef JOBTHREAD_H_INCLUDED
#define JOBTHREAD_H_INCLUDED

#include "Pointers/BaseInterface.h"
#include "Pointers/Pointers.h"

//Java-style job thread

namespace threading
{

_interface IThreadJob : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IThreadJob, IBaseInterfaceMT );

public:
  virtual void Work( volatile bool & isRunning ) = 0;
};


class JobThreadImplementation;

class JobThread : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( JobThread, BaseObjectMT )

public:
  JobThread( IThreadJob * _job, const char * _debugName, unsigned _waitMs = 3000, unsigned stackSize = 0 );

  ~JobThread() { StopImpl(); }

  unsigned int Id() const;

  //bool Wait( unsigned timeout = INFINITE );
  bool Wait( unsigned timeout = (unsigned)-1 );
  void SetPriority( int _delta );
  void AsyncStop();

private:
  void StopImpl();

  JobThreadImplementation * thread;
};

}; //namespace threading

#endif //JOBTHREAD_H_INCLUDED
