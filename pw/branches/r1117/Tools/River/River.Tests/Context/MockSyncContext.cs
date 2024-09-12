using System;
using System.Collections.Generic;
using System.Text;
using River.Core;

namespace River.Tests.Context
{
  internal class MockSyncContext : ISyncContext
  {

    public int GetBotsCalled = 0;
    public string GetBotsParam = null;
    public BotDescription[] GetBotsResult = null;
    public BotDescription[] GetBotsWithTest( string type )
    {
      ++GetBotsCalled;
      GetBotsParam = type;
      return GetBotsResult;
    }

    public int SyncIncCalled = 0;
    public string SyncIncParam = string.Empty;
    public void SyncInc( string name )
    {
      ++SyncIncCalled;
      SyncIncParam = name;
    }

    public int SyncDecCalled = 0;
    public string SyncDecParam = string.Empty;
    public void SyncDec( string name )
    {
      ++SyncDecCalled;
      SyncDecParam = name;
    }

    public int SyncCheckCalled = 0;
    public string SyncCheckParam1 = string.Empty;
    public int SyncCheckParam2 = 0;
    public TimeSpan SyncCheckParam3 = TimeSpan.MinValue;
    public bool SyncWait( string name, int value, TimeSpan timeout )
    {
      ++SyncCheckCalled;
      SyncCheckParam1 = name;
      SyncCheckParam2 = value;
      SyncCheckParam3 = timeout;
      return false;
    }

    public int ProgressCalled = 0;
    public int ProgressParam1 = 0;
    public string ProgressParam2 = string.Empty;
    public void Progress( int progress, string message )
    {
      ++ProgressCalled;
      ProgressParam1 = progress;
      ProgressParam2 = message;
    }

    public int PutFileCalled = 0;
    public List<string> PutFileParam1 = new List<string>();
    public List<byte[]> PutFileParam2 = new List<byte[]>();
    public void PutFile( BotDescription bot, string filePath, byte[] fileData )
    {
      ++PutFileCalled;
      PutFileParam1.Add( filePath );
      PutFileParam2.Add( fileData );
    }
  }
}
