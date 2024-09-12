#ifndef SYSTEM_BASEOBJECTMT_H_INCLUDED
#define SYSTEM_BASEOBJECTMT_H_INCLUDED

#include "System/Pointers/BasicType.h"
#include <System/noncopyable.h>
#include <System/interlocked.h>
#include "BaseInterface.h"
#include "PointersDetail.h"
#include "System/SpinLock.h"

class WeakPointerProxyMT;


class BaseObjectMT : public IBaseInterfaceMT, public SerializableObject, public NonCopyable
{
  NI_DECLARE_CLASS_2( BaseObjectMT, IBaseInterfaceMT, SerializableObject )
  NI_DECLARE_NONPRODUCIBLE_CLASS( BaseObjectMT );

public:
  BaseObjectMT() : refCount( 0 ), weakProxy( 0 ) {}

  virtual ~BaseObjectMT()
  {
  }

  void StrongAddRef()
  {
    nival::interlocked_increment( refCount );
  }

  void StrongRelease();

  LONG volatile * RefCountPtr() { return &refCount; }

  WeakPointerProxyType * AcquireWeakProxyInternal();

private:
  //static const int CreatingProxyMagic = 1;
  static WeakPointerProxyType * CreatingProxyMagic;

  volatile LONG                   refCount;
  WeakPointerProxyType * volatile weakProxy;
};





class WeakPointerProxyMT : public NonCopyable
{
public:
  WeakPointerProxyMT( BaseObjectMT * _object ) : refCount( 0 ), object( _object )
  {
  }

  BaseObjectMT * Object() const { return object; }

  void WeakAddRef()
  {
    nival::interlocked_increment( refCount );
  }

  void WeakRelease()
  {
    LONG count = nival::interlocked_decrement( refCount );
    if ( count <= 0 )
    {
      NI_ASSERT( 0 == count, "Counter MUST be 0" );
      if (0 == count)
        delete this;
    }
  }

  threading::SpinLock & AccessLock() { return spinlock; }

  void Detach() { object = 0; }

private:
  volatile LONG           refCount; //Weak ref count
  threading::SpinLock     spinlock;
  BaseObjectMT *          object;
};

#endif //SYSTEM_BASEOBJECTMT_H_INCLUDED
