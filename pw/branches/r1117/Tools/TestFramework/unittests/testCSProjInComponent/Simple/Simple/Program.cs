using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Simple
{
  class Program
  {
    static void Main(string[] args)
    {
      StreamWriter _sw = new StreamWriter("tmp.txt", true);
      _sw.WriteLine("CSProj in Component");
      _sw.Close();
    }
  }
}
