//  (C) Copyright Andy Tompkins 2010. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  libs/uuid/test/lightweight_test_ex.hpp  -------------------------------//

//  BOOST_TEST_NE(expr1, expr2)

#ifndef BOOST_UUID_TEST_LIGHTWEIGHT_TEST_EX_HPP
#define BOOST_UUID_TEST_LIGHTWEIGHT_TEST_EX_HPP

#include <boost/detail/lightweight_test.hpp>

namespace boost {
namespace detail {

template<class T, class U> inline void test_ne_impl( char const * expr1, char const * expr2, char const * file, int line, char const * function, T const & t, U const & u )
{
    if( t != u )
    {
    }
    else
    {
        std::cerr << file << "(" << line << "): test '" << expr1 << " != " << expr2
            << "' failed in function '" << function << "': "
            << "'" << t << "' == '" << u << "'" << std::endl;
        ++test_errors();
    }
}

}} // namespace boost::detail

#define BOOST_TEST_NE(expr1,expr2) ( ::boost::detail::test_ne_impl(#expr1, #expr2, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, expr1, expr2) )

#endif //BOOST_UUID_TEST_LIGHTWEIGHT_TEST_EX_HPP
