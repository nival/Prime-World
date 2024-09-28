#pragma once

#include "MemoryLib/newdelete.h"

class NativeCl
{
public:
  NativeCl()
  {
    int* a = new int();
    delete a;
  }
};
