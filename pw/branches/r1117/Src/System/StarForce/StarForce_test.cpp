#include "stdafx.h"
#include "StarForce_test.h"
#include "StarForce.h"
#include "HiddenVars.h"
#include "StarForce/PsaApi.h"


namespace
{
template<class T>
struct Accum: std::iterator<std::output_iterator_tag, void, void, void, void>
{          
public:
  Accum(): count(), sum(0) {}

	Accum& operator=(const T& val)
	{	
	  ++count;
	  sum += val;
	  return (*this);
	}

  Accum& operator*(){ return *this; }
  Accum& operator++(){ return *this; }
  Accum& operator++(int){ return *this; }
  
  size_t count;
  T sum;
};   

struct RandProxy
{
  float operator()() const
  {
    return float(rand() % 1000);
  }                  
};

template<class T>
Accum<T> TestStarForceVarsImpl1(size_t VarsCount)
{
  vector<T> data(VarsCount);
  
  srand(1234567);
  
  std::generate( data.begin(), data.end(), RandProxy() ); 

  Protection::Stopwatch stopwatch( __FUNCSIG__ );
  std::sort( data.begin(), data.end() );
  return std::unique_copy( data.begin(), data.end(), Accum<T>() );
}

template<class T>
Accum<T> TestStarForceVarsImpl2(size_t VarsCount)
{
  vector<T> data(VarsCount);
  
  srand(1234567);
  
  std::generate( data.begin(), data.end(), RandProxy() ); 

  Protection::Stopwatch stopwatch( __FUNCSIG__ );
  return std::copy( data.begin(), data.end(), Accum<T>() );
}
}

void TestStarForceVars()
{ 
#ifdef STARFORCE_PROTECTED
  {
    typedef PsProtFloat64_1 SFType;
    typedef double OrigType;
    const size_t VarsCount = 1000;
    const Accum<OrigType> flRes = TestStarForceVarsImpl1<OrigType>(VarsCount); 
    const Accum<SFType> sfRes = TestStarForceVarsImpl1<SFType>(VarsCount);

    DebugTrace( "TestStarForceVarsImpl1 %u == %u, %g == %g", 
        flRes.count, sfRes.count, flRes.sum, const_cast<SFType &>(sfRes.sum).Value() );
  }
  
  {
    typedef PsProtFloat32_1 SFType;
    typedef float OrigType;
    const size_t VarsCount = 15000;
    const Accum<OrigType> flRes = TestStarForceVarsImpl2<OrigType>(VarsCount); 
    const Accum<SFType> sfRes = TestStarForceVarsImpl2<SFType>(VarsCount);

    DebugTrace( "TestStarForceVarsImpl2 %u == %u, %g == %g", 
        flRes.count, sfRes.count, flRes.sum, const_cast<SFType &>(sfRes.sum).Value() );
  }
#endif 
  
  {
    typedef Protection::Detail::HiddenVarImpl<float, unsigned int, 0> SFType;
    typedef float OrigType;
    const size_t VarsCount = 1000;
    Accum<OrigType> flRes = TestStarForceVarsImpl1<OrigType>(VarsCount); 
    Accum<SFType> sfRes = TestStarForceVarsImpl1<SFType>(VarsCount);

    Recrypt(sfRes.sum);

    DebugTrace( "TestStarForceVarsImpl1 HidenValue %u == %u, %g == %g", 
        flRes.count, sfRes.count, flRes.sum, GetValue(sfRes.sum) );
  }
  
  {
    typedef Protection::Detail::HiddenVarImpl<float, unsigned int, 1> SFType;
    typedef float OrigType;
    const size_t VarsCount = 15000;
    const Accum<OrigType> flRes = TestStarForceVarsImpl2<OrigType>(VarsCount); 
    const Accum<SFType> sfRes = TestStarForceVarsImpl2<SFType>(VarsCount);

    DebugTrace( "TestStarForceVarsImpl2 HidenValue %u == %u, %g == %g", 
        flRes.count, sfRes.count, flRes.sum, GetValue(sfRes.sum) );
  }
}
