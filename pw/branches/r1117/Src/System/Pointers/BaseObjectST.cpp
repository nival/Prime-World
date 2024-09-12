#include "stdafx.h"
#include "BaseObjectST.h"


void BaseObjectST::StrongRelease()
{
  --refCount;
  if ( refCount <= 0 )
  {
    if ( weakProxy )
    {
      weakProxy->Detach();
      weakProxy->WeakRelease();
      weakProxy = 0;
    }

    delete this;
  }
}




BaseObjectST::WeakPointerProxyType * BaseObjectST::AcquireWeakProxyInternal()
{
  if ( !weakProxy )
  {
    WeakPointerProxyST * newProxy = new WeakPointerProxyST( this );
    newProxy->WeakAddRef();
    weakProxy = newProxy;
  }

  return weakProxy;
}
