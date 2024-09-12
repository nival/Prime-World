#ifndef STARFORCE_H_B49639B9_D704_4F6D_B
#define STARFORCE_H_B49639B9_D704_4F6D_B

#include "System/HPTimer.h"
#include "System/SystemLog.h"

#pragma code_seg(push, "~")

#ifdef STARFORCE_PROTECTED
  #define STARFORCE_EXPORT __declspec(dllexport) __declspec(noinline)
  #define STARFORCE_FORCE_INLINE __forceinline
  #define STARFORCE_FORCE_NOINLINE __declspec(noinline)
#else
  #define STARFORCE_EXPORT
  #define STARFORCE_FORCE_INLINE inline
  #define STARFORCE_FORCE_NOINLINE
#endif

#if defined( STARFORCE_PROTECTED ) && 0
  #define STARFORCE_STOPWATCH() Protection::Stopwatch stopwatchImpl( __FUNCTION__ )
  #define STARFORCE_LOG( ... ) DebugTrace( __VA_ARGS__ )
#else
  #define STARFORCE_STOPWATCH() ((void)0)
  #define STARFORCE_LOG( ... ) ((void)0)
#endif

namespace Protection
{
  typedef void (*SeparateThreadFuncPtr)( const void *pData );

  //Проверить сегменты памяти помеченные флагами ReadOnly и Executable на то, 
  //что они не были изменены в процессе работы программы. Т.е. не изменился код 
  //и данные во время работы приложения. Нужно вызвать периодически.
  STARFORCE_EXPORT void CheckReadOnlyAndExecutable();

  STARFORCE_EXPORT bool CheckReadOnlyAndExecutableImmediate();
  
  //Проверить то что системные dll используются в неизменном виде. Защищает от атак 
  //типа SpeedHack и ему подобным. Нужно вызвать периодически.
  STARFORCE_EXPORT void CheckSystemDlls();
  
  //Функцию нужно вызвать периодически и передавать указатель funcPtr на функцию, 
  //вызов которой, необходим для корректного функционирования игры. Эта функция 
  //будет вызвана в отдельном потоке, но при этом основной поток будет поставлен 
  //на пауза до того, как вызов функции funcPtr завершиться. То есть вызов функции
  //обычным образом и через CallFunctionInProtectedSpace, семантически не отличаются.
  // 
  //Этот метод стал необходим в связи с тем, что вызов PSA_CheckProtectedModulesReadOnlyMem
  //продолжается 3 секунды и мы не можем позволить себе вызывать его в основном потоке. 
  //Поэтому все обращения к функциям защиты запускают задачу в специально выделенном 
  //потоке и сразу возвращают управление. Для того чтобы исключить возможность 
  //простого блокирования потока защиты этот поток должен выполнять кроме функций 
  //защиты ещё и какую-нибудь работу необходимую приложению, для чего и существует 
  //данная функция. 
  STARFORCE_EXPORT void CallFunctionInProtectedSpace( SeparateThreadFuncPtr funcPtr, const void *pData );
  
  //Простое измерение времени выполнения функции
  class Stopwatch
  {
  public:
    explicit Stopwatch( const char * funcName ): funcName(funcName) 
    {
      DebugTrace( "Function %s begin. Thread: 0x%08X.", 
#if defined( NV_WIN_PLATFORM )
        funcName, GetCurrentThreadId()
#elif defined( NV_LINUX_PLATFORM )
        funcName, pthread_self()
#endif
      );
      
      NHPTimer::GetTime(startTime);
    }
    
    ~Stopwatch()
    {
      NHPTimer::STime curTime;
      NHPTimer::GetTime(curTime);
      
      curTime = curTime - startTime;

      DebugTrace( "Function %s execution time: %g sec. Thread: 0x%08X.", 
#if defined( NV_WIN_PLATFORM )
        funcName, NHPTimer::Time2Seconds(curTime), GetCurrentThreadId()
#elif defined( NV_LINUX_PLATFORM )
        funcName, NHPTimer::Time2Seconds(curTime), pthread_self()
#endif
      );
    }

  private:
    NHPTimer::STime startTime;
    const char *funcName;
  };
}

#pragma code_seg(pop)

#endif //#define STARFORCE_H_B49639B9_D704_4F6D_B