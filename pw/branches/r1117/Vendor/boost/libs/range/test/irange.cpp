// Boost.Range library
//
//  Copyright Neil Groves 2010. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>

namespace boost
{
    // Test an integer range with a step size of 1.
    template<typename Integer>
    void test_irange_impl(Integer first, Integer last)
    {
        std::vector<Integer> reference;
        for (Integer i = first; i < last; ++i)
        {
            reference.push_back(i);
        }

        std::vector<Integer> test;
        boost::push_back(test, boost::irange(first, last));

        BOOST_CHECK_EQUAL_COLLECTIONS( test.begin(), test.end(),
                                       reference.begin(), reference.end() );
    }

    // Test an integer range with a runtime specified step size.
    template<typename Integer>
    void test_irange_impl(Integer first, Integer last, int step)
    {
        BOOST_ASSERT( step != 0 );
        std::vector<Integer> reference;
        if (step > 0)
        {
            for (Integer i = first; i < last; i += step)
                reference.push_back(i);
        }
        else
        {
            for (Integer i = first; i > last; i += step)
                reference.push_back(i);
        }

        std::vector<Integer> test;
        boost::push_back(test, boost::irange(first, last, step));

        BOOST_CHECK_EQUAL_COLLECTIONS( test.begin(), test.end(),
                                       reference.begin(), reference.end() );
    }

    // Test driver function that for an integer range [first, last)
    // drives the test implementation through various integer
    // types.
    void test_irange(int first, int last)
    {
        test_irange_impl<signed char>(first,last);
        test_irange_impl<unsigned char>(first, last);
        test_irange_impl<signed short>(first, last);
        test_irange_impl<unsigned short>(first, last);
        test_irange_impl<signed int>(first, last);
        test_irange_impl<unsigned int>(first, last);
        test_irange_impl<signed long>(first, last);
        test_irange_impl<unsigned long>(first, last);
    }

    // Test driver function that for an integer range [first, last)
    // drives the test implementation through various integer
    // types step_size items at a time.
    void test_irange(int first, int last, int step_size)
    {
        BOOST_ASSERT( step_size != 0 );
        BOOST_ASSERT( (last - first) % step_size == 0 );
        test_irange_impl<signed char>(first, last, step_size);
        test_irange_impl<unsigned char>(first, last, step_size);
        test_irange_impl<signed short>(first, last, step_size);
        test_irange_impl<unsigned short>(first, last, step_size);
        test_irange_impl<signed int>(first, last, step_size);
        test_irange_impl<unsigned int>(first, last, step_size);
        test_irange_impl<signed long>(first, last, step_size);
        test_irange_impl<unsigned long>(first, last, step_size);
    }

    // Implementation of the unit test for the integer range
    // function.
    // This starts the test drivers to drive a set of integer types
    // for a combination of range values chosen to exercise a large
    // number of implementation branches.
    void irange_unit_test()
    {
        // Test the single-step version of irange(first, last)
        test_irange(0, 0);
        test_irange(0, 1);
        test_irange(0, 10);
        test_irange(1, 1);
        test_irange(1, 2);
        test_irange(1, 11);

        // Test the n-step version of irange(first, last, step-size)
        test_irange(0, 0, 1);
        test_irange(0, 0, -1);
        test_irange(0, 10, 1);
        test_irange(10, 0, -1);
        test_irange(0, 2, 2);
        test_irange(2, 0, -2);
        test_irange(10, 20, 5);
        test_irange(20, 10, -5);
    }
} // namespace boost

boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* test
        = BOOST_TEST_SUITE( "RangeTestSuite.irange" );

    test->add(BOOST_TEST_CASE( &boost::irange_unit_test ));

    return test;
}
