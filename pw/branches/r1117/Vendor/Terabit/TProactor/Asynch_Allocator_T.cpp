/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   
**
**
**
**
**
**********************************************************************/

// POSIX_AIO_Allocator.cpp
// POSIX_AIO_Allocator.cpp,v 4.90 2002/12/28 03:06:31 nanbor Exp

#ifndef TRB_POSIX_AIO_ALLOCATOR_T_C 
#define TRB_POSIX_AIO_ALLOCATOR_T_C 

#include "TProactor/Asynch_Allocator_T.h"

# include "ace/OS_NS_string.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

template <class ACE_LOCK>
TRB_Asynch_Allocator_T<ACE_LOCK>::TRB_Asynch_Allocator_T (size_t chunk_size)
  : free_list_  (ACE_PURE_FREE_LIST)
  , chunk_size_ (chunk_size)
{
  if (this->chunk_size_ < MIN_CHUNK_SIZE)
    {
      this->chunk_size_ = MIN_CHUNK_SIZE;
    }

  this->chunk_size_ = ACE_MALLOC_ROUNDUP (this->chunk_size_, ACE_MALLOC_ALIGN);
  
  ACE_DEBUG((LM_DEBUG,
             ACE_LIB_TEXT("ALLOCATOR Chunk size=%u\n"),
             this->chunk_size_           
            )); 
             
}

template <class ACE_LOCK>
TRB_Asynch_Allocator_T<ACE_LOCK>::~TRB_Asynch_Allocator_T (void)
{
  int i=0;
  for (;;++i)
    {
      ACE_Cached_Mem_Pool_Node<MIN_CHUNK> * ptr = this->free_list_.remove ();

      if (ptr == 0)
        break;

      ACE_OS::free(ptr);
    }

  ACE_DEBUG((LM_DEBUG,
             ACE_LIB_TEXT("ALLOCATOR Cache size size=%d\n"),
             i           
            )); 
}

template <class ACE_LOCK> ACE_INLINE void *
TRB_Asynch_Allocator_T<ACE_LOCK>::malloc (size_t nbytes)
{
  // Check if size requested fits within pre-determined size.
  if (nbytes > this->chunk_size_)
    return 0;

  // addr() call is really not absolutely necessary because of the way
  // ACE_Cached_Mem_Pool_Node's internal structure arranged.

  ACE_Cached_Mem_Pool_Node<MIN_CHUNK> * ptr = this->free_list_.remove ();

  if (ptr != 0)
    return static_cast<void *> (ptr);

  return ACE_OS::malloc (this->chunk_size_);

  //ACE_DEBUG((LM_DEBUG,"+++Malloc size=%d ret=%@ free_chunk=%@\n", 
  //          (int) nbytes, p, ptr));
  //return p;     
}

template <class ACE_LOCK> ACE_INLINE void *
TRB_Asynch_Allocator_T<ACE_LOCK>::calloc (size_t nbytes,
                                          char initial_value)
{
  void * ptr = this->malloc (nbytes);

  if (ptr != 0)
    ACE_OS::memset (ptr, initial_value, this->chunk_size_);

  return ptr;
}

template <class ACE_LOCK> ACE_INLINE void *
TRB_Asynch_Allocator_T<ACE_LOCK>::calloc (size_t,
                                           size_t,
                                           char)
{
  ACE_NOTSUP_RETURN (0);
}

template <class ACE_LOCK> ACE_INLINE void
TRB_Asynch_Allocator_T<ACE_LOCK>::free (void * ptr)
{
  //ACE_DEBUG((LM_DEBUG,"---Free ptr=%@\n",  ptr));

  if (ptr != 0)
   {
     this->free_list_.add (
         static_cast<ACE_Cached_Mem_Pool_Node<MIN_CHUNK>*> (ptr));
   }
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif //TRB_POSIX_AIO_ALLOCATOR_T_C 
