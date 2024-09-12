using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;
using NUnit.ConsoleRunner;
using NUnit.Framework;
using LofNS;

namespace Test
{
  [TestFixture]
  public class ClassTestComponent
  {
    [Test, Description( "Simpliest test" )]
    public void Test()
    {
      LofClass lc = new LofClass();
      Assert.IsTrue( lc.a == 4 );
    }
  }
}