#include "stdafx.h"
#include "RandomInterfaceImpl.h"
#include "RandomGenerator.h"

NI_DEFINE_REFCOUNT( ni_rnd::IGenerator );

namespace ni_rnd
{

class Generator : public IGenerator, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( Generator, IGenerator, BaseObjectST );

public:
  Generator() : gen() {}
  Generator( unsigned _seed ) : gen( _seed ) {}

  virtual unsigned Next() { return gen.Next(); }

private:
  NRandom::RandomGenerator  gen;
};




class ThreadSafeGenerator : public IGenerator, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( ThreadSafeGenerator, IGenerator, BaseObjectST );

public:
  ThreadSafeGenerator() : gen() {}
  ThreadSafeGenerator( unsigned _seed ) : gen( _seed ) {}

  virtual unsigned Next()
  {
    threading::SpinLockGuard lock( spinlock );
    return gen.Next();
  }

private:
  NRandom::RandomGenerator  gen;
  threading::SpinLock       spinlock;
};



IGenerator * Factory::Produce( unsigned _seed )
{
  if ( threadsafe )
    return new ThreadSafeGenerator( _seed );
  else
    return new Generator( _seed );
}



IGenerator * Factory::Produce()
{
  if ( threadsafe )
    return new ThreadSafeGenerator;
  else
    return new Generator;
}

} //namespace ni_rnd
