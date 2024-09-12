//!Component('NSTL')

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class CircullarBuffertest : public CxxTest::TestSuite
{
public:

  void testPushingAndPopping()
  {
    nstl::circular_buffer<int> cb(5);
    TS_ASSERT_EQUALS(cb.size(), 0);
    TS_ASSERT_EQUALS(cb.capacity(), 5);
    TS_ASSERT(cb.empty());
    TS_ASSERT(cb.max_size() > 0);

    TS_ASSERT(cb.push_back(1));
    TS_ASSERT_EQUALS(cb.size() , 1);
    TS_ASSERT_EQUALS(cb.capacity() , 5);
    TS_ASSERT(!cb.empty());
    TS_ASSERT_EQUALS(cb.front() , 1);
    TS_ASSERT_EQUALS(cb.back()  , 1);

    TS_ASSERT(cb.push_back(2));
    TS_ASSERT_EQUALS(cb.size() , 2);
    TS_ASSERT_EQUALS(cb.capacity() , 5);
    TS_ASSERT(!cb.empty());
    TS_ASSERT_EQUALS(cb.front() , 1);
    TS_ASSERT_EQUALS(cb.back()  , 2);

    TS_ASSERT(cb.push_back(3));
    TS_ASSERT(cb.push_back(4));
    TS_ASSERT(cb.push_back(5));
    TS_ASSERT_EQUALS(cb.size() , 5);
    TS_ASSERT_EQUALS(cb.capacity() , 5);
    TS_ASSERT(!cb.empty());
    TS_ASSERT_EQUALS(cb.front() , 1);
    TS_ASSERT_EQUALS(cb.back()  , 5);

    TS_ASSERT(!cb.push_back(6));
    TS_ASSERT_EQUALS(cb.size() , 5);
    TS_ASSERT_EQUALS(cb.capacity() , 5);
    TS_ASSERT(!cb.empty());
    TS_ASSERT_EQUALS(cb.front() , 2);
    TS_ASSERT_EQUALS(cb.back()  , 6);

    cb.pop_front();
    TS_ASSERT_EQUALS(cb.size() , 4);
    TS_ASSERT_EQUALS(cb.capacity() , 5);
    TS_ASSERT(!cb.empty());
    TS_ASSERT_EQUALS(cb.front() , 3);
    TS_ASSERT_EQUALS(cb.back()  , 6);

    cb.pop_front();
    TS_ASSERT_EQUALS(cb.size() , 3);
    TS_ASSERT_EQUALS(cb.front() , 4);
    TS_ASSERT_EQUALS(cb.back()  , 6);

    cb.pop_front();
    TS_ASSERT_EQUALS(cb.size() , 2);
    TS_ASSERT_EQUALS(cb.front() , 5);
    TS_ASSERT_EQUALS(cb.back()  , 6);

    cb.pop_front();
    TS_ASSERT_EQUALS(cb.size() , 1);
    TS_ASSERT_EQUALS(cb.front() , 6);
    TS_ASSERT_EQUALS(cb.back()  , 6);

    cb.pop_front();
    TS_ASSERT_EQUALS(cb.size() , 0);
    TS_ASSERT_EQUALS(cb.capacity() , 5);
    TS_ASSERT(cb.empty());

    // empty again

    TS_ASSERT(cb.push_back(7));
    TS_ASSERT_EQUALS(cb.size() , 1);
    TS_ASSERT_EQUALS(cb.capacity() , 5);
    TS_ASSERT(!cb.empty());
    TS_ASSERT_EQUALS(cb.front() , 7);
    TS_ASSERT_EQUALS(cb.back()  , 7);

    TS_ASSERT(cb.push_back(8));
    TS_ASSERT(cb.push_back(9));
    TS_ASSERT_EQUALS(cb.size() , 3);
    TS_ASSERT(!cb.empty());
    TS_ASSERT_EQUALS(cb.front() , 7);
    TS_ASSERT_EQUALS(cb.back()  , 9);

    cb.clear();
    TS_ASSERT_EQUALS(cb.size() , 0);
    TS_ASSERT_EQUALS(cb.capacity() , 5);
    TS_ASSERT(cb.empty());
  }
  void testIndexing()
  {
    circular_buffer<int> cb(5);

#define assert_throws(a,b) \
    {\
    try { a; throw "Failed to throw"; } \
    catch (const b&) { /*OK*/ } \
    catch (...) { throw "Threw wrong thing"; } \
    }
    // We loop round this test several times so our data wraps around the
    // internal m_buffer array a few times.
    for (size_t n = 0; n < 10; ++n)
    {
      TS_ASSERT(cb.empty());

      const nstl::circular_buffer<int> &const_cb(cb);
 
      TS_ASSERT(cb.push_back(0));
      TS_ASSERT(cb.push_back(1));
      TS_ASSERT(cb.push_back(2));
      TS_ASSERT_EQUALS(cb.at(0) , 0); TS_ASSERT_EQUALS(const_cb.at(0) , 0);
      TS_ASSERT_EQUALS(cb.at(1) , 1); TS_ASSERT_EQUALS(const_cb.at(1) , 1);
      TS_ASSERT_EQUALS(cb.at(2) , 2); TS_ASSERT_EQUALS(const_cb.at(2) , 2);
      TS_ASSERT_EQUALS(cb[0] , 0);    TS_ASSERT_EQUALS(const_cb[0] , 0);
      TS_ASSERT_EQUALS(cb[1] , 1);    TS_ASSERT_EQUALS(const_cb[1] , 1);
      TS_ASSERT_EQUALS(cb[2] , 2);    TS_ASSERT_EQUALS(const_cb[2] , 2);

      TS_ASSERT_EQUALS(cb.front() , 0);
      cb[0] = 3;
      TS_ASSERT_EQUALS(cb.front() , 3);
      TS_ASSERT_EQUALS(cb.at(0) , 3); TS_ASSERT_EQUALS(const_cb.at(0) , 3);
      TS_ASSERT_EQUALS(cb.at(1) , 1); TS_ASSERT_EQUALS(const_cb.at(1) , 1);
      TS_ASSERT_EQUALS(cb.at(2) , 2); TS_ASSERT_EQUALS(const_cb.at(2) , 2);
      TS_ASSERT_EQUALS(cb[0] , 3);    TS_ASSERT_EQUALS(const_cb[0] , 3);
      TS_ASSERT_EQUALS(cb[1] , 1);    TS_ASSERT_EQUALS(const_cb[1] , 1);
      TS_ASSERT_EQUALS(cb[2] , 2);    TS_ASSERT_EQUALS(const_cb[2] , 2);

      cb[1] = 4;
      TS_ASSERT_EQUALS(cb.at(0) , 3); TS_ASSERT_EQUALS(const_cb.at(0) , 3);
      TS_ASSERT_EQUALS(cb.at(1) , 4); TS_ASSERT_EQUALS(const_cb.at(1) , 4);
      TS_ASSERT_EQUALS(cb.at(2) , 2); TS_ASSERT_EQUALS(const_cb.at(2) , 2);
      TS_ASSERT_EQUALS(cb[0] , 3);    TS_ASSERT_EQUALS(const_cb[0] , 3);
      TS_ASSERT_EQUALS(cb[1] , 4);    TS_ASSERT_EQUALS(const_cb[1] , 4);
      TS_ASSERT_EQUALS(cb[2] , 2);    TS_ASSERT_EQUALS(const_cb[2] , 2);

      cb.pop_front();
      TS_ASSERT_EQUALS(cb[0] , 4);    TS_ASSERT_EQUALS(const_cb[0] , 4);
      TS_ASSERT_EQUALS(cb[1] , 2);    TS_ASSERT_EQUALS(const_cb[1] , 2);

      cb.pop_front();
      TS_ASSERT_EQUALS(cb[0] , 2);    TS_ASSERT_EQUALS(const_cb[0] , 2);

      cb.pop_front();
    }
  }
};


