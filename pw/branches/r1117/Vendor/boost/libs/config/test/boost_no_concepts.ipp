//  (C) Copyright Beman Dawes 2009

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/config for more information.

//  MACRO:         BOOST_NO_CONCEPTS
//  TITLE:         C++0x concepts feature unavailable
//  DESCRIPTION:   The compiler does not support the C++0x concepts feature

namespace boost_no_concepts {

concept Foo<typename T> { }

int test()
{
  return 0;
}

}
