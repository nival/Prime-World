#include "stdafx.h"
#include "BaseObjectMT.h"
#include "../interlocked.h"

BaseObjectMT::WeakPointerProxyType * BaseObjectMT::CreatingProxyMagic = (BaseObjectMT::WeakPointerProxyType *)(static_cast< char* >( 0 ) + 1);

void BaseObjectMT::StrongRelease()
{
  LONG count = nival::interlocked_decrement( refCount );
  if ( count <= 0 )
  {
    NI_ASSERT( 0 == count, "Counter MUST be 0" );
    if ( 0 == count )
    {
      if ( weakProxy )
      {
        WeakPointerProxyMT * proxy = (WeakPointerProxyMT * )weakProxy;
        //Destruction may be blocked by someone requesting strong pointer from weak
        {
          threading::SpinLockGuard lock( proxy->AccessLock() );

          //Someone else managed to re-capture object via Weak::Lock()
          if ( refCount > 0 )
            return;

          proxy->Detach();
        }

        proxy->WeakRelease();
        weakProxy = 0;
      }

      delete this;
    }
  }
}



BaseObjectMT::WeakPointerProxyType * BaseObjectMT::AcquireWeakProxyInternal()
{
  while ( true )
  {
    //NOTE: prevent atomic operation
    if ( (volatile void *)weakProxy > (volatile void *)CreatingProxyMagic )
      return (WeakPointerProxyMT *)weakProxy;

    void * prev = nival::interlocked_compare_exchange_pointer< BaseObjectMT::WeakPointerProxyType >( weakProxy, CreatingProxyMagic, (BaseObjectMT::WeakPointerProxyType *)0 );
    if ( prev == 0 )
    {
      WeakPointerProxyMT * newProxy = new WeakPointerProxyMT( this );
      newProxy->WeakAddRef();
      assert( weakProxy == (void *)CreatingProxyMagic );
      weakProxy = newProxy; //NOTE: non atomic operation
      return newProxy;
    }
    else if ( prev != (void *)CreatingProxyMagic )
      return (WeakPointerProxyMT *)prev;
  }
}
