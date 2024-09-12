#ifndef SYSTEM_BASEOBJECTST_H_INCLUDED
#define SYSTEM_BASEOBJECTST_H_INCLUDED

#include <System/noncopyable.h>
#include "BaseInterface.h"
#include "PointersDetail.h"


class WeakPointerProxyST;


class BaseObjectST : public IBaseInterfaceST, public SerializableObject, public NonCopyable
{
  NI_DECLARE_CLASS_2( BaseObjectST, IBaseInterfaceST, SerializableObject )
  NI_DECLARE_NONPRODUCIBLE_CLASS( BaseObjectST );

public:
  BaseObjectST() : refCount( 0 ), weakProxy( 0 ) {}

  virtual ~BaseObjectST()
  {
  }

  void StrongAddRef()
  {
    ++refCount;
  }

  void StrongRelease();

  WeakPointerProxyST * AcquireWeakProxyInternal();

private:
  int                     refCount;
  WeakPointerProxyType *  weakProxy;
};





class WeakPointerProxyST
{
public:
  WeakPointerProxyST( BaseObjectST * _object ) : refCount( 0 ), object( _object )
  {
  }

  BaseObjectST * Object() const { return object; }

  void WeakAddRef()
  {
    ++refCount;
  }

  void WeakRelease()
  {
    --refCount;
    if ( refCount <= 0 )
    {
      delete this;
    }
  }

  void Detach() { object = 0; }

private:
  int               refCount;
  BaseObjectST *    object;
};

#endif //SYSTEM_BASEOBJECTST_H_INCLUDED
