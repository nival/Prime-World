using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;
using NUnit.ConsoleRunner;
using NUnit.Framework;
using NativeTest;

namespace Test
{
  [TestFixture]
  public class ManagedTestComponent
  {
    [Test, Description( "Managed test" )]
    public void Test()
    {
      NativeClass lc = new NativeClass();
      Assert.IsTrue( lc.a == 4 );
    }
  }
}