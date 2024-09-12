//!Component('NSTL')

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

////////////////////////////////////////////////////////////////////////////////
//
// binary function test object
//
////////////////////////////////////////////////////////////////////////////////
class BinaryFunctest : public CxxTest::TestSuite
{
public:

  void testSortLessSimple()
  {
    nstl::vector<int> vec;
    vec.push_back(8);
    vec.push_back(12);
    vec.push_back(20);

    nstl::sort(vec.begin(),vec.end(),less_pred<int>());

    TS_ASSERT_EQUALS(vec[0],20);
    TS_ASSERT_EQUALS(vec[1],12);
    TS_ASSERT_EQUALS(vec[2],8);
  }

  void testSortLessMixed()
  {
    nstl::vector<int> vec;
    vec.push_back(20);
    vec.push_back(12);
    vec.push_back(18);
    vec.push_back(8);
    vec.push_back(19);

    nstl::sort(vec.begin(),vec.end(),less_pred<int>());

    TS_ASSERT_EQUALS(vec[0],20);
    TS_ASSERT_EQUALS(vec[1],19);
    TS_ASSERT_EQUALS(vec[2],18);
    TS_ASSERT_EQUALS(vec[3],12);
    TS_ASSERT_EQUALS(vec[4],8);
  }

  void testSortLessComplex()
  {
    nstl::vector<int> vec;
    vec.push_back(20);
    vec.push_back(12);
    vec.push_back(18);
    vec.push_back(8);
    vec.push_back(19);
    vec.push_back(8);
    vec.push_back(12);
    vec.push_back(8);

    nstl::sort(vec.begin(),vec.end(),less_pred<int>());

    TS_ASSERT_EQUALS(vec[0],20);
    TS_ASSERT_EQUALS(vec[1],19);
    TS_ASSERT_EQUALS(vec[2],18);
    TS_ASSERT_EQUALS(vec[3],12);
    TS_ASSERT_EQUALS(vec[4],12);
    TS_ASSERT_EQUALS(vec[5],8);
    TS_ASSERT_EQUALS(vec[6],8);
    TS_ASSERT_EQUALS(vec[7],8);
  }

  void testSortGreaterSimple()
  {
    nstl::vector<int> vec;
    vec.push_back(20);
    vec.push_back(12);
    vec.push_back(8);

    nstl::sort(vec.begin(),vec.end(),greater_pred<int>());

    TS_ASSERT_EQUALS(vec[0],8);
    TS_ASSERT_EQUALS(vec[1],12);
    TS_ASSERT_EQUALS(vec[2],20);
  }

  void testSortGreaterMixed()
  {
    nstl::vector<int> vec;
    vec.push_back(20);
    vec.push_back(12);
    vec.push_back(18);
    vec.push_back(8);
    vec.push_back(19);

    nstl::sort(vec.begin(),vec.end(),greater_pred<int>());

    TS_ASSERT_EQUALS(vec[0],8);
    TS_ASSERT_EQUALS(vec[1],12);
    TS_ASSERT_EQUALS(vec[2],18);
    TS_ASSERT_EQUALS(vec[3],19);
    TS_ASSERT_EQUALS(vec[4],20);
  }

  void testSortGreaterComplex()
  {
    nstl::vector<int> vec;
    vec.push_back(20);
    vec.push_back(12);
    vec.push_back(18);
    vec.push_back(8);
    vec.push_back(19);
    vec.push_back(8);
    vec.push_back(12);
    vec.push_back(8);

    nstl::sort(vec.begin(),vec.end(),greater_pred<int>());

    TS_ASSERT_EQUALS(vec[0],8);
    TS_ASSERT_EQUALS(vec[1],8);
    TS_ASSERT_EQUALS(vec[2],8);
    TS_ASSERT_EQUALS(vec[3],12);
    TS_ASSERT_EQUALS(vec[4],12);
    TS_ASSERT_EQUALS(vec[5],18);
    TS_ASSERT_EQUALS(vec[6],19);
    TS_ASSERT_EQUALS(vec[7],20);
  }

};


