// -*- C++ -*-

// $Id: Collection_Test.h 80826 2008-03-04 14:51:23Z wotte $

// ============================================================================
//
// = LIBRARY
//    tests
//
// = FILENAME
//    Collection_Test.h
//
// = DESCRIPTION
//    Define class needed for generating templates. IBM C++ requires this to
//    be in its own file for auto template instantiation.
//
// = AUTHOR
//    Irfan Pyarali <irfan@cs.wustl.edu>
//
// ============================================================================

#ifndef ACE_TESTS_COLLECTION_TEST_H
#define ACE_TESTS_COLLECTION_TEST_H

typedef void (*deletion_func)(void* p);

struct UglyThing
{
  void *alloc_;
  deletion_func dfunc_;

  UglyThing (void* alloc = 0, deletion_func dfunc = 0);
  bool operator== (const UglyThing& r) const;
};

#endif /* ACE_TESTS_COLLECTION_TEST_H */
