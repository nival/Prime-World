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

// -*- C++ -*-

//==========================================================================
/**
 *
 *  @file    Asynch_Allocator_T.h
 *  $Id: $
 * 
 *  @author Alexander Libman <alibman@terabit.com.au>
 */
//==========================================================================

#ifndef TRB_ASYNCH_ALLOCATOR_T_H 
#define TRB_ASYNCH_ALLOCATOR_T_H 
#include "ace/pre.h"

#include "TProactor/TPROACTOR_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Synch.h"
#include "ace/Malloc_T.h"               /* Need ACE_Control_Block */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 * @class TRB_Asynch_Allocator_T
 *
 * @brief A fixed-size allocator that caches items for quicker access.
 *
 * This class enables caching of dynamically allocated,
 * fixed-sized classes.  Notice that the <code>sizeof (TYPE)</code>
 * must be greater than or equal to <code> sizeof (void*) </code> for
 * this to work properly.
 *
 */
template <class ACE_LOCK>
class TRB_Asynch_Allocator_T :
    public ACE_New_Allocator
{
  union MIN_CHUNK
    {
      void *any_ptr_;
      char  c_data_ [1];
    };

  enum 
   {
      MIN_CHUNK_SIZE = sizeof(MIN_CHUNK)
   };


public:
  TRB_Asynch_Allocator_T (size_t chunk_size);

  /// Clear things up.
  ~TRB_Asynch_Allocator_T (void);

  /**
   * Get a chunk of memory from free list cache.  Note that @a nbytes is
   * only checked to make sure that it's less or equal to sizeof T, and is
   * otherwise ignored since @c malloc() always returns a pointer to an
   * item of sizeof (T).
   */
  void *malloc (size_t nbytes);

  /**
   * Get a chunk of memory from free list cache, giving them
   * @a initial_value.  Note that @a nbytes is only checked to make sure
   * that it's less or equal to sizeof T, and is otherwise ignored since
   * calloc() always returns a pointer to an item of sizeof (T).
   */
  virtual void *calloc (size_t nbytes,
                        char initial_value = '\0');

  /// This method is a no-op and just returns 0 since the free list
  /// only works with fixed sized entities.
  virtual void *calloc (size_t n_elem,
                        size_t elem_size,
                        char initial_value = '\0');

  /// Return a chunk of memory back to free list cache.
  void free (void *);

private:

  /// Maintain a cached memory free list.
  ACE_Locked_Free_List<ACE_Cached_Mem_Pool_Node<MIN_CHUNK>, ACE_LOCK> free_list_;

  size_t chunk_size_;
};

ACE_END_VERSIONED_NAMESPACE_DECL

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#include "TProactor/Asynch_Allocator_T.cpp"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Asynch_Allocator_T.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#include "ace/post.h"
#endif // TRB_ASYNCH_ALLOCATOR_H 
