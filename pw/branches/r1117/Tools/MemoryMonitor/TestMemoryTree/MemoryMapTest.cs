using MemoryMonitor.Memory;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using MemoryMonitor.EventLog;
using System.Collections.Generic;

namespace TestMemoryTree
{
    
    
    /// <summary>
    ///This is a test class for MemoryMapTest and is intended
    ///to contain all MemoryMapTest Unit Tests
    ///</summary>
  [TestClass()]
  public class MemoryMapTest
  {


    private TestContext testContextInstance;

    /// <summary>
    ///Gets or sets the test context which provides
    ///information about and functionality for the current test run.
    ///</summary>
    public TestContext TestContext
    {
      get
      {
        return testContextInstance;
      }
      set
      {
        testContextInstance = value;
      }
    }

    #region Additional test attributes
    // 
    //You can use the following additional attributes as you write your tests:
    //
    //Use ClassInitialize to run code before running the first test in the class
    //[ClassInitialize()]
    //public static void MyClassInitialize(TestContext testContext)
    //{
    //}
    //
    //Use ClassCleanup to run code after all tests in a class have run
    //[ClassCleanup()]
    //public static void MyClassCleanup()
    //{
    //}
    //

    //Use TestInitialize to run code before running each test
    [TestInitialize()]
    public void MyTestInitialize()
    {
    }
    
    //Use TestCleanup to run code after each test has run
    [TestCleanup()]
    public void MyTestCleanup()
    {
    }
    
    #endregion

    [TestMethod()]
    public void BasicSizeTest()
    {
      Node target = new Node( 0, 0x80000000 );
      Assert.AreEqual( 0u, target.MemoryUsed );
      Assert.AreEqual( 0x80000000, target.MemoryFree );

      EventFree ef = new EventFree( 1, 0 );
      EventAlloc ea = new EventAlloc( 0, 0, 16 );
      target.ProcessAlloc( ea );
      Assert.AreEqual( 16u, target.MemoryUsed );
      Assert.AreEqual( 0x80000000 - 16, target.MemoryFree );

      target.ProcessFree( ef );
      Assert.AreEqual( 0u, target.MemoryUsed );
      Assert.AreEqual( 0x80000000, target.MemoryFree );

      EventAlloc ea2 = new EventAlloc( 0, 0x100, 32 );
      target.ProcessAlloc( ea );
      target.ProcessAlloc( ea2 );
      Assert.AreEqual( 48u, target.MemoryUsed );
      Assert.AreEqual( 0x80000000 - 48, target.MemoryFree );
    }

    [TestMethod()]
    public void MemorySizeTest2()
    {
      Node target = new Node( 0, 0x80000000 );

      EventAlloc ea1 = new EventAlloc( 0, 0x00, 16 );
      EventFree ef1 = new EventFree( 1, 0x00 );
      EventAlloc ea2 = new EventAlloc( 0, 0x100, 32 );
      EventFree ef2 = new EventFree( 1, 0x100 );

      target.ProcessAlloc( ea1 );
      target.ProcessAlloc( ea2 );
      Assert.AreEqual( 48u, target.MemoryUsed );
      Assert.AreEqual( 0x80000000 - 48, target.MemoryFree );
      
      target.ProcessFree( ef1 );
      Assert.AreEqual( 32u, target.MemoryUsed );
      Assert.AreEqual( 0x80000000 - 32, target.MemoryFree );

      target.ProcessFree( ef2 );
      Assert.AreEqual( 0u, target.MemoryUsed );
      Assert.AreEqual( 0x80000000, target.MemoryFree );

      target.ProcessAlloc( ea1 );
      target.ProcessAlloc( ea2 );
      Assert.AreEqual( 48u, target.MemoryUsed );
      Assert.AreEqual( 0x80000000 - 48, target.MemoryFree );

      target.ProcessFree( ef2 );
      Assert.AreEqual( 16u, target.MemoryUsed );
      Assert.AreEqual( 0x80000000 - 16, target.MemoryFree );

      target.ProcessFree( ef1 );
      Assert.AreEqual( 0u, target.MemoryUsed );
      Assert.AreEqual( 0x80000000, target.MemoryFree );
    }

    [TestMethod()]
    public void MemoryInfoTest()
    {
      Node target = new Node( 0, 0x80000000 );

      EventAlloc ea1 = new EventAlloc( 0, 0x00, 16 );
      EventFree ef1 = new EventFree( 1, 0x00 );
      EventAlloc ea2 = new EventAlloc( 0, 0x100, 32 );
      EventFree ef2 = new EventFree( 1, 0x100 );

      Assert.IsNull( target.GetInfo( 0x00 ) );
      Assert.IsNull( target.GetInfo( 0x05 ) );
      Assert.IsNull( target.GetInfo( 0x100 ) );
      Assert.IsNull( target.GetInfo( 0x103 ) );

      target.ProcessAlloc( ea1 );
      Assert.AreEqual( ea1, target.GetInfo( 0x00 ) );
      Assert.AreEqual( ea1, target.GetInfo( 0x05 ) );
      Assert.IsNull( target.GetInfo( 0x10 ) );
      Assert.IsNull( target.GetInfo( 0x100 ) );
      Assert.IsNull( target.GetInfo( 0x103 ) );

      target.ProcessAlloc( ea2 );
      Assert.AreEqual( ea1, target.GetInfo( 0x00 ) );
      Assert.AreEqual( ea1, target.GetInfo( 0x05 ) );
      Assert.IsNull( target.GetInfo( 0x10 ) );
      Assert.AreEqual( ea2, target.GetInfo( 0x100 ) );
      Assert.AreEqual( ea2, target.GetInfo( 0x103 ) );
      Assert.IsNull( target.GetInfo( 0x120 ) );

      target.ProcessFree( ef1 );
      Assert.IsNull( target.GetInfo( 0x00 ) );
      Assert.IsNull( target.GetInfo( 0x05 ) );
      Assert.IsNull( target.GetInfo( 0x10 ) );
      Assert.AreEqual( ea2, target.GetInfo( 0x100 ) );
      Assert.AreEqual( ea2, target.GetInfo( 0x103 ) );
      Assert.IsNull( target.GetInfo( 0x120 ) );

      target.ProcessFree( ef2 );
      Assert.IsNull( target.GetInfo( 0x00 ) );
      Assert.IsNull( target.GetInfo( 0x05 ) );
      Assert.IsNull( target.GetInfo( 0x10 ) );
      Assert.IsNull( target.GetInfo( 0x100 ) );
      Assert.IsNull( target.GetInfo( 0x103 ) );
      Assert.IsNull( target.GetInfo( 0x120 ) );

      target = new Node( 0, 0x80000000 );
      target.ProcessAlloc( new EventAlloc( 0, 0x100, 0x10000 ) );
      Assert.IsNull( target.GetInfo( 0xff ) );
      Assert.IsNull( target.GetInfo( 0x10100 ) );
      Assert.IsNotNull( target.GetInfo( 0x100 ) );
      Assert.IsNotNull( target.GetInfo( 0x100ff ) );
    }

    [TestMethod()]
    public void MemoryRangeInfoTest()
    {
      Node target = new Node( 0, 0x80000000 );

      EventAlloc ea1 = new EventAlloc( 0, 0x00, 16 );
      EventFree ef1 = new EventFree( 1, 0x00 );
      EventAlloc ea2 = new EventAlloc( 0, 0x10, 32 );
      EventFree ef2 = new EventFree( 1, 0x10 );

      List<EventAlloc> allocs = new List<EventAlloc>();
      Assert.AreEqual( 0u, target.GetFastRegionInfo( 0x00, 256, allocs ) );
      Assert.AreEqual( 0, allocs.Count );

      target.ProcessAlloc( ea1 );
      Assert.AreEqual( 16u, target.GetFastRegionInfo( 0x00, 256, allocs ) );
      Assert.AreEqual( 1, allocs.Count );
      Assert.AreEqual( ea1, allocs[0] );

      target.ProcessAlloc( ea2 );
      Assert.AreEqual( 15u, target.GetFastRegionInfo( 0x05, 15, allocs ) );
      Assert.AreEqual( 2, allocs.Count );
      Assert.IsTrue( allocs.Contains( ea1 ) );
      Assert.IsTrue( allocs.Contains( ea2 ) );

      target.ProcessFree( ef1 );
      Assert.AreEqual( 32u, target.GetFastRegionInfo( 0x00, 256, allocs ) );
      Assert.AreEqual( 1, allocs.Count );
      Assert.AreEqual( ea2, allocs[0] );

      target.ProcessFree( ef2 );
      Assert.AreEqual( 0u, target.GetFastRegionInfo( 0x00, 256, allocs ) );
      Assert.AreEqual( 0, allocs.Count );


      target.ProcessAlloc( new EventAlloc( 0, 0x00, 1 ) );
      target.ProcessAlloc( new EventAlloc( 0, 0x01, 1 ) );
      target.ProcessAlloc( new EventAlloc( 0, 0x02, 1 ) );
      target.ProcessAlloc( new EventAlloc( 0, 0x03, 1 ) );
      target.ProcessAlloc( new EventAlloc( 0, 0x04, 1 ) );
      target.ProcessAlloc( new EventAlloc( 0, 0x05, 1 ) );
      target.ProcessAlloc( new EventAlloc( 0, 0x06, 1 ) );
      Assert.AreEqual( 7u, target.GetFastRegionInfo( 0x00, 256, allocs ) );
      Assert.AreEqual( 6, allocs.Count );
      Assert.IsTrue( allocs.Contains( null ) );
      Assert.AreEqual( 7u, target.GetFullRegionInfo( 0x00, 256, allocs ) );
      Assert.AreEqual( 7, allocs.Count );
      Assert.IsFalse( allocs.Contains( null ) );

      target = new Node( 0, 0x80000000 );
      target.ProcessAlloc( new EventAlloc( 0, 0x100, 0x10000 ) );
      Assert.AreEqual( 0x10000u, target.GetFastRegionInfo( 0x00, 0x20000, allocs ) );
      Assert.AreEqual( 1, allocs.Count );
    }

    [TestMethod()]
    public void SnapshotCloningTest()
    {
      Node root1 = new Node( 0, 0x80000000 );
      EventAlloc ea1 = new EventAlloc( 0, 0x00, 16 );
      EventAlloc ea2 = new EventAlloc( 0, 0x10, 32 );
      root1.ProcessAlloc( ea1 );
      root1.ProcessAlloc( ea2 );

      Snapshot ss = new Snapshot( root1, 123, 456, 0 );
      Assert.AreEqual( 123u, ss.Time );
      Assert.AreEqual( 456u, ss.FilePosition );

      // Test that the copy contains the same allocs
      Node root2 = ss.Restore();
      List<EventAlloc> allocs = new List<EventAlloc>();
      Assert.AreEqual( 48u, root2.GetFastRegionInfo( 0x00, 0x10000, allocs ) );
      Assert.AreEqual( 2, allocs.Count );
      Assert.IsTrue( allocs.Contains( ea1 ) );
      Assert.IsTrue( allocs.Contains( ea2 ) );

      // Test that it's a copy, not the same object
      root1.ProcessAlloc( new EventAlloc( 0, 0x100, 256 ) );
      Assert.AreEqual( 48u, root2.GetFastRegionInfo( 0x00, 0x10000, allocs ) );
      Assert.AreEqual( 2, allocs.Count );
      Assert.IsTrue( allocs.Contains( ea1 ) );
      Assert.IsTrue( allocs.Contains( ea2 ) );
    }
  }
}
