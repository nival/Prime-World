using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;
using NUnit.ConsoleRunner;
using NUnit.Framework;

namespace Test
{
  [TestFixture]
  public class ClassTest
  {
    [Test, Description( "Simpliest test" )]
    public void Test()
    {
      Assert.IsTrue( true );
    }
  }
}