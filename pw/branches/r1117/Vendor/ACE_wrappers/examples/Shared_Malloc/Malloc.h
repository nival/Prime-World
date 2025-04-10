/* -*- C++ -*- */
// $Id: Malloc.h 80826 2008-03-04 14:51:23Z wotte $

#ifndef MY_MALLOC_H
#define MY_MALLOC_H

#include "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL
class ACE_Allocator;
ACE_END_VERSIONED_NAMESPACE_DECL

class Malloc
  // = TITLE
  //      Allocator Singleton.
{
public:
  static ACE_Allocator *instance (void);
  // Returns static instance.

private:
  Malloc (void);
  // Ensure Singleton.

  static ACE_Allocator *instance_;
  // Malloc Singleton.
};

#endif /* MY_MALLOC_H */
