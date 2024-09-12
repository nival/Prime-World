#include "systemStdAfx.h"
#include "AsyncInvoker.h"
#include <iostream>
#include <conio.h>


static int g_count;


int someWork()
{
  std::cout << "Start " << GetCurrentThreadId() 
  << std::endl;
  Sleep(2000);
  std::cout << "Finish" << std::endl;
  
  return ++g_count;
}

int main(int argc, char* argv[])
{
  threading::AsyncInvoker< int (*) (), int > invoker;
  
  invoker.Sync();
  invoker.FakeInvoke( -1000 );
  invoker.Sync();
  
  while( !_kbhit() )
  {
    std::cout << "Result: " << invoker.EndInvoke() << std::endl;
    invoker.BeginInvoke(someWork);
    invoker.Sync();
    invoker.FakeInvoke( invoker.EndInvoke() );
    invoker.Sync();
    
    invoker.BeginInvoke(someWork);
  }

  return 0;
}