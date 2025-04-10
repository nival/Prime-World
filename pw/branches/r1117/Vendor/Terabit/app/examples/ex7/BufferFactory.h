#ifndef BUFFER_FACTORY_H
#define BUFFER_FACTORY_H

#include "TProactor/Asynch_Allocator_T.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "ace/Synch.h"
#include "ace/Lock_Adapter_T.h"
#include "IOTerabit/MessageBlockFactory.h"

class BufferFactory :
    public Terabit::MessageBlockFactory
{
public:
    BufferFactory(size_t chunk_size);
    virtual ~BufferFactory(void);

    virtual ACE_Message_Block *alloc_msg (size_t length);
    virtual void free_msg (ACE_Message_Block * mb);

private:

  typedef TRB_Asynch_Allocator_T<ACE_SYNCH_MUTEX> Allocator;

  ACE_SYNCH_MUTEX  mtx_;
  ACE_Lock_Adapter<ACE_SYNCH_MUTEX>  lock_;
  Allocator  mb_allocator_;
  Allocator  db_allocator_;
  Allocator  buf_allocator_;



};

#endif // BUFFER_FACTORY_H

