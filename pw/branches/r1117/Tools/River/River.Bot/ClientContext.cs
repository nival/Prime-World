using System;
using System.Collections.Generic;
using System.Text;
using River.Core;
using System.IO;

namespace River.Bot
{
  public class ClientContext : MarshalByRefObject, IContext
  {
    private const int PutFileBatchLength = 1024 * 1024;

    private ISyncContext syncContext = null;

    public ClientContext( ISyncContext remoteContext, BotDescription myDesc )
    {
      syncContext = remoteContext;
      MyBot = myDesc;
    }

    public override object InitializeLifetimeService()
    {
      return null;
    }

    public BotDescription[] GetBotsWithTest( string typeName )
    {
      return syncContext.GetBotsWithTest( typeName );
    }

    public BotDescription MyBot { get; private set; }

    public void SyncInc( string name )
    {
      syncContext.SyncInc( name );
    }

    public void SyncDec( string name )
    {
      syncContext.SyncDec( name );
    }

    public bool SyncWait( string name, int value, TimeSpan timeout )
    {
      return syncContext.SyncWait( name, value, timeout );
    }

    public void Progress( int progress, string message )
    {
      syncContext.Progress( progress, message );
    }

    public void Progress( int progress ) { Progress( progress, string.Empty ); }
    public void Progress( string format, params object[] args ) { Progress( -1, string.Format( format, args ) ); }
    public void Progress( int progress, string format, params object[] args ) { Progress( progress, string.Format( format, args ) ); }

    public void PutFile( string filePath )
    {
      List<string> fileNamesToPut = new List<string>();

      if ( filePath.Contains( "*" ) || filePath.Contains( "?" ) )
      {
        string path = Path.GetDirectoryName( filePath );
        if ( string.IsNullOrEmpty( path ) )
          path = ".";

        string filePattern = Path.GetFileName( filePath );

        string[] fileNames = Directory.GetFiles( path, filePattern );
        fileNamesToPut.AddRange( fileNames );
      }
      else
      {
        fileNamesToPut.Add( filePath );
      }

      foreach ( string fileName in fileNamesToPut )
      {
        try
        {
          FileStream fs = new FileStream( fileName, FileMode.Open, FileAccess.Read );
          long fileLenRemaining = fs.Length;
          byte[] fileData = new byte[PutFileBatchLength];

          while ( fileLenRemaining > PutFileBatchLength )
          {
            fs.Read( fileData, 0, PutFileBatchLength );

            syncContext.PutFile( MyBot, Path.GetFileName( fileName ), fileData );

            fileLenRemaining -= PutFileBatchLength;
          }
          fileData = new byte[fileLenRemaining];
          fs.Read( fileData, 0, (int)fileLenRemaining );
          syncContext.PutFile( MyBot, Path.GetFileName( fileName ), fileData );
          fs.Close();
        }
        catch
        {
        }
      }
    }
  }
}
