#pragma once

#include "MemoryLib/newdelete.h"
#include "dummy.h"

public ref class ManagedClass
{

public:
  ManagedClass()
  {
    NativeCl* cl = new NativeCl();
    delete cl;
    int* a = new int();
    delete a;
  }
};