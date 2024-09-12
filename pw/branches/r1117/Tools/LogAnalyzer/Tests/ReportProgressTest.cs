using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using Zzima;
using System.IO;

namespace Tests
{
  [TestFixture]
  public class ReportProgressTest
  {
    //[TestFixtureSetUp]
    //public void Init()
    //{
    //}
    
    //правильность разбора по формату 
    //@"\((?<thread>\d{1,10})\) (?<time>\d{2}:\d{2}:\d{2}.\d{3,6})(?<channel> \[[a-z0-9 ]+\])? (?<level>d:|m:|w:|e:|a:|c:)? (?<message>.*)";
    //несоотвествие формату - вся строка попадает в message
    [Test]
    public void Test_Parser()
    {
      const string testFile = "testFormat.txt";
      Assert.That( File.Exists( testFile ), "файл для теста " + testFile + "  не найден" );
      PWLogPlugin plugin = new PWLogPlugin( Guid.NewGuid() );
      plugin.OpenInput( testFile );
      int fieldCount = plugin.GetFieldCount();
      int takeLines = 100;
      LogResult result = new LogResult();
      for ( int line = 0; line < takeLines; line++ )
      {
        result.Clear();
        bool moreLines = plugin.ReadRecord();
        if ( !moreLines )
          break;
        for ( int i = 0; i < fieldCount; i++ )
        {
          object val = plugin.GetValue( i );
          if ( i == 0 ) if (val != null) result.Thread = val.ToString();
          if ( i == 1 ) if (val != null) result.Time = val.ToString();
          if ( i == 2 ) if (val != null) result.Channel = val.ToString();
          if ( i == 3 ) if (val != null) result.Level = val.ToString();
          if ( i == 4 ) if (val != null) result.Message = val.ToString();
        }
        if ( line == 0 ) //первая строка проверяем что получил все поля
        {
          Assert.AreEqual( "15345", result.Thread );
          Assert.AreEqual( "00:01:08.117", result.Time );
          Assert.AreEqual( "[CHANNEL S PROBELAMI]", result.Channel );
          Assert.AreEqual( "d:", result.Level );
          Assert.That( result.Message.StartsWith( "GateKeeperPoller instances:1" ) ); 
        }
        if ( line == 1 ) //thread не в скобках - все сообщение в message
        {
          Assert.IsNull( result.Thread );
          Assert.That( result.Message.StartsWith( "15345 12:12:12.123456 [CHANNEL S PROBELAMI] d: GateKeeperPoller instances:1 min:0 average:0 max:0 calls:1112" ) ); 
        }
        if ( line == 2 ) //channel отсутствует
        {
          Assert.AreEqual( "3548", result.Thread );
          Assert.AreEqual( "00:00:08.055", result.Time );
          Assert.IsNull( result.Channel );
          Assert.AreEqual( "d:", result.Level );
          Assert.That( result.Message.StartsWith( "GateKeeperPoller instances:1" ) ); 
        }
        if ( line == 3 ) // отсутствует обязательный level
        {
          Assert.IsNull( result.Thread );
          Assert.That( result.Message.StartsWith( "(3548) 00:00:18.074 GateKeeperPoller instances:1" ) );
        }
        if ( line == 4 ) //несуществующий level
        {
          Assert.IsNull( result.Thread );
          Assert.That( result.Message.StartsWith( "(3548) 00:00:28.083 [CHANNEL S PROBELAMI] z: GateKeeperPoller" ) );
        }
      }
      plugin.CloseInput( true );
    }
    public class LogResult
    {
      public string Thread;
      public string Time;
      public string Channel;
      public string Level;
      public string Message;
      public void Clear()
      {
        Thread = null;
        Time = null;
        Channel = null;
        Level = null;
        Message = null;
      }
    }
  }
}
