
#include "stdafx.h"
#include "LockFreeQueue.h"
#include "cxxtest/TestSuite.h"

namespace test
{
struct Allocator 
{
  Allocator():allocatedSize(0) {}
  template <typename T> T* Allocate() 
  { 
    void* memory = _Allocate(sizeof(T));
    allocatedSize += sizeof(T);
    return new (memory) T(); 
  }

  template <typename T> 
  void Deallocate(T* instance)
  {
    allocatedSize -= sizeof(T);
    instance->~T();
    _Deallocate(instance);
  }

  void* _Allocate(uint size)
  {
    return new byte[size];
  }

  void _Deallocate(void* address)
  {
    delete [] (byte*)address;
  }
  int allocatedSize;
};

}

class Test_LockFreeQueue :  public CxxTest::TestSuite
{
public:
  void test_Simple()
  {
    nstl::LockFreeQueue< int > q;

    q.enqueue(0);
    q.enqueue(1);
    q.enqueue(2);

    int n;
    bool result;

    result = q.dequeue(n);
    TS_ASSERT_EQUALS(true, result);
    TS_ASSERT_EQUALS(0, n);

    result = q.dequeue(n);
    TS_ASSERT_EQUALS(true, result);
    TS_ASSERT_EQUALS(1, n);

    result = q.dequeue(n);
    TS_ASSERT_EQUALS(true, result);
    TS_ASSERT_EQUALS(2, n);

    result = q.dequeue(n);
    TS_ASSERT_EQUALS(false, result);
  }

  void test_Allocator()
  {
    test::Allocator a;
    {
      nstl::LockFreeQueue< int, test::Allocator > q(&a);

      q.enqueue(0);
      q.enqueue(1);
      q.enqueue(2);

      int n;
      bool result;

      result = q.dequeue(n);
      TS_ASSERT_EQUALS(true, result);
      TS_ASSERT_EQUALS(0, n);

      result = q.dequeue(n);
      TS_ASSERT_EQUALS(true, result);
      TS_ASSERT_EQUALS(1, n);

      result = q.dequeue(n);
      TS_ASSERT_EQUALS(true, result);
      TS_ASSERT_EQUALS(2, n);

      result = q.dequeue(n);
      TS_ASSERT_EQUALS(false, result);
    }
    TS_ASSERT_EQUALS(0, a.allocatedSize);
  }

  void test_MemoryLeaks()
  {
    test::Allocator a;
    {
      nstl::LockFreeQueue< int, test::Allocator > q(&a);

      q.enqueue(0);
      q.enqueue(1);
      q.enqueue(2);
    }
    TS_ASSERT_EQUALS(0, a.allocatedSize);
  }

};