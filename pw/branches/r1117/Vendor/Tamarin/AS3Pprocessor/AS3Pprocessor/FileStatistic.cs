using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AS3Pprocessor
{
  class FileStatistic
  {
    public FileStatistic()
    {
      StaticNativeMethodsCount = NativeMethodsCount = 0;
    }
    public int StaticNativeMethodsCount;
    public int NativeMethodsCount;
  }
}
