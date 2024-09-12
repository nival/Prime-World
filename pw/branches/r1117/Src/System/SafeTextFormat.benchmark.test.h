//!Component("System/SafeTextFormat")
//!Component("System/Commands")

#include "stdafx.h"
#include "SafeTextFormat.h"
#include "SafeTextFormatBuffers.h"
#include "get_tick_count.h"
#include "cxxtest/TestSuite.h"

class BenchmarkSafeFormat : public CxxTest::TestSuite
{
public:
  static void bench_printf_raw( char * buffer, size_t size ) {
    NStr::Printf( buffer, size, "Quick brown fox jumped over the lazy dog" );
  }

  static void bench_safe_raw( char * buffer, size_t size ) {
    text::ExternalBuffer B( buffer, size );
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Quick brown fox jumped over the lazy dog" );
  }  

  static void bench_printf_3args( char * buffer, size_t size ) {
    int i = 1024;
    float f = 3.14159f;
    const char * s = "Nickname";
    NStr::Printf( buffer, size, "Arg0: %d, arg1: %.6f, arg2: %s", i, f, s );
  }

  static void bench_safe_3args( char * buffer, size_t size ) {
    text::ExternalBuffer B( buffer, size );
    int i = 1024;
    float f = 3.14159f;
    const char * s = "Nickname";
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace( "Arg0: %d, arg1: %.6f, arg2: %s", i, f, s );
  }

  static void bench_printf_9args( char * buffer, size_t size ) {
    int i0 = 1024, i1 = -100500, i2 = 0;
    float f0 = 3.14159f, f1 = 2.7f, f2 = 0.5f;
    const char * s0 = "Nickname",  *s1 = "Second arg", *s2 = "Third arg";
    NStr::Printf( buffer, size,
      "Int0: %d, Int1: %d, Int2: %d\n"
      "Float0: %f, float1: %f, float2: %f\n"
      "String0: %s, String1: %s, String2: %s\n", i0, i1, i2, f0, f1, f2, s0, s1, s2 );
  }

  static void bench_safe_9args( char * buffer, size_t size ) {
    text::ExternalBuffer B( buffer, size );
    int i0 = 1024, i1 = -100500, i2 = 0;
    float f0 = 3.14159f, f1 = 2.7f, f2 = 0.5f;
    const char * s0 = "Nickname",  *s1 = "Second arg", *s2 = "Third arg";
    text::PrintfFormatterBufferPtr fmtr( &B );
    fmtr.Trace(
      "Int0: %d, Int1: %d, Int2: %d\n"
      "Float0: %f, float1: %f, float2: %f\n"
      "String0: %s, String1: %s, String2: %s\n", i0, i1, i2, f0, f1, f2, s0, s1, s2 );
  }

  double measure_func( void (*func) ( char * buffer, size_t size ) ) {
    const size_t size = 1024;
    char buffer[size];

    DWORD t0 = GetTickCount();
    int counter = 0;
    while ( GetTickCount() < t0 + 1000 ) {
      for ( int i = 0; i < 100; ++i )
        (*func)( buffer, size );
      ++counter;
    }
    double t_ms = nival::get_tick_count() - t0;
    return (double)counter / t_ms;
  }

  void test_benchmark()
  {
    printf( "\n" );

    double printf_raw = measure_func( &BenchmarkSafeFormat::bench_printf_raw );
    printf( "Printf raw text rate: %.2fk\n", printf_raw );

    double printf_3arg = measure_func( &BenchmarkSafeFormat::bench_printf_3args );
    printf( "Printf 3 arguments rate: %.2fk\n", printf_3arg );

    double printf_9arg = measure_func( &BenchmarkSafeFormat::bench_printf_9args );
    printf( "Printf 9 arguments rate: %.2fk\n", printf_9arg );

    double safe_raw = measure_func( &BenchmarkSafeFormat::bench_safe_raw );
    printf( "Safe raw text rate: %.2fk\n", safe_raw );

    double safe_3arg = measure_func( &BenchmarkSafeFormat::bench_safe_3args );
    printf( "Safe 3 arguments rate: %.2fk\n", safe_3arg );

    double safe_9arg = measure_func( &BenchmarkSafeFormat::bench_safe_9args );
    printf( "Safe 9 arguments rate: %.2fk\n", safe_9arg );

    printf( "Safe speed ratios:\n" );
    printf( "Raw text: %.2fx\n", safe_raw / printf_raw );
    printf( "3 args: %.2fx\n", safe_3arg / printf_3arg );
    printf( "9 args: %.2fx\n", safe_9arg / printf_9arg );
  }
};
