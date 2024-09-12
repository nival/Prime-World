#pragma once

struct DummyParent {};
namespace test
{

REMOTE struct HelloWorld : DummyParent
{
  RPC_ID();

  HelloWorld()
  {
    int a =0;
    a++;
  }
  ~HelloWorld()
  {
    int a =0;
    a++;
  }
  REMOTE void Print(const char* message) 
  {
    printf("Server message: %s\n", message);
  }
  REMOTE void Write(const char* message) 
  {
    printf("Write message: %s\n", message);
  }
  REMOTE int GetInt( int val )
  {
    return val*10;
  }
};

}