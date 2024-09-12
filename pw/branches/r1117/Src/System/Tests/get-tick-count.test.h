#include <iostream>
#include <cstdlib>

#include <System/stdafx.h>
#include <System/types.h>
#include <System/sleep.h>
#include <System/get_tick_count.h>
#include <System/sleep.h>
#include "cxxtest/TestSuite.h"

using namespace nival;

/*
	Тест на проверку корректности возвращаемого get_tick_count значения:
	1. Получаем текущее значение get_tick_count (first tick)
	2. Вводим поток в сон на случайный промежуток времени от 1 до 3 секунд (sleep time)
	3. Получаем новое значение (last tick). Разница между first tick + sleep time и last tick не должна превышать 30 мс.
*/
class GetTickCountTest : public CxxTest::TestSuite
{
public:
  void setUp()
  {
    std::srand( time( NULL ) );
  }

  void test_1()
  {
    nival::uint32_t first_tick = get_tick_count();

    int sleep_time = 1000 + std::rand() % 2000;
    nival::sleep( sleep_time );

    nival::uint32_t last_tick = get_tick_count();
    const int diff = last_tick - first_tick;
    TS_ASSERT( abs( diff - sleep_time ) <= 30 );
  }

  /*
    Тест на проверку корректности возвращаемого get_tick_count_64 значения.
    Тест аналогичен тесту test_1, а заисключением того, что вызывается функций get_tick_count_64
  */
  void test_2()
  {
    nival::uint64_t first_tick = get_tick_count_64();

    int sleep_time = 1000 + std::rand() % 2000;
    nival::sleep( sleep_time );

    nival::uint64_t last_tick = get_tick_count();
    const int diff = static_cast< int >( last_tick - first_tick );
    TS_ASSERT( abs( diff - sleep_time ) <= 30 );
  }

  /*
    Тест на наличие реализации функции GetTickCount и схожести возвращаемого ей значения с get_tick_count.
    В случае отсутствия реализации проект не собирается, что само по себе является сигнализирующей ошибкой.
  */
  void test_3()
  {
    TS_ASSERT ( ( GetTickCount() - get_tick_count() ) <= 30 );
  }

};
