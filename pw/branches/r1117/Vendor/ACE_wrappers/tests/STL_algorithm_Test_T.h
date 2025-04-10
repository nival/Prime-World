// -*- C++ -*-

//=============================================================================
/**
 *  @file    STL_algorithm_Test_T.h
 *
 *  Test ACE containers compatibility with STL <algorithm> header.
 *
 *  $Id: STL_algorithm_Test_T.h 80826 2008-03-04 14:51:23Z wotte $
 *
 *  @author  James H. Hill <j.hill@vanderbilt.edu>
 */
//=============================================================================

#ifndef ACE_TESTS_STL_ALGORITHM_TEST_T_H
#define ACE_TESTS_STL_ALGORITHM_TEST_T_H

template <typename T>
int test_STL_algorithm (T & container);

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#include "STL_algorithm_Test_T.cpp"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("STL_algorithm_Test_T.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#endif /* ACE_TESTS_STL_ALGORITHM_TEST_T_H */
