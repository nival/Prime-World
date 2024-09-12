using System;
using NUnit.Framework;

namespace MemoryLib.Tests
{
  [TestFixture]
  public class MemoryTest
  {
    [Test, Description( "Test memory" )]
    public void TestMemory()
    {
      ManagedClass a = new ManagedClass();
    }
  }
}