using System;
using System.Collections.Generic;
using System.Text;
using River.Core;
using System.Text.RegularExpressions;
using System.Threading;
using System.IO;

namespace River.Master
{
	public class SyncContext : MarshalByRefObject, ISyncContext
	{
    private Dictionary<string, int> syncVars = new Dictionary<string, int>();

    private RunningSuite suite = null;
    private Dictionary<string, List<BotDescription>> bots = new Dictionary<string,List<BotDescription>>();

    public override object InitializeLifetimeService()
    {
      return null;
    }

    public SyncContext( RunningSuite suite )
    {
      this.suite = suite;
    }

    public void RegisterBot( BotDescription bot, string typeName )
    {
      if ( !bots.ContainsKey( typeName ) )
        bots[typeName] = new List<BotDescription>();

      bots[typeName].Add( bot );
    }

    public BotDescription[] GetBotsWithTest( string type )
    {
      if ( !bots.ContainsKey( type ) )
        return null;

      return bots[type].ToArray();
    }

    private void CheckVarName( string name )
    {
      if ( null == name )
        throw new ArgumentNullException();

      if ( !syncVars.ContainsKey( name ) )
      {
        if ( !Regex.IsMatch( name, "^[A-Za-z_][A-Za-z0-9_]*$" ) )
          throw new ArgumentException();

        syncVars.Add( name, 0 );
      }
    }

    public void SyncInc( string name )
    {
      lock ( syncVars )
      {
        CheckVarName( name );

        ++syncVars[name];
      }
    }

    public void SyncDec( string name )
    {
      lock ( syncVars )
      {
        CheckVarName( name );

        --syncVars[name];
      }
    }

    public bool SyncWait( string name, int value, TimeSpan timeout )
    {
      lock ( syncVars )
      {
        CheckVarName( name );
      }

      int msec = (int)timeout.TotalMilliseconds;
      Random rng = new Random();
      int step = rng.Next( 10 ) + 5;
      do
      {
        lock ( syncVars )
        {
          if ( syncVars[name] == value )
            return true;
        }

        msec -= step;
        Thread.Sleep( step );
      } while ( msec > 0 );

      return false;
    }

    public void Progress( int progress, string message )
    {
    }

    public void PutFile( BotDescription bot, string filePath, byte[] fileData )
    {
      string dirName = string.Format( "{0}_{1}", bot.ID, bot.Name );
      string subDir = Path.Combine( suite.OutputPath, dirName );
      lock ( suite )
      {
        if ( !Directory.Exists( subDir ) )
          Directory.CreateDirectory( subDir );

        try
        {
          string finalFileName = Path.Combine( subDir, filePath );
          if ( !File.Exists( finalFileName ) )
          {
            File.WriteAllBytes( finalFileName, fileData );
          }
          else
          {
            FileStream fs = new FileStream( finalFileName, FileMode.Append );
            fs.Write( fileData, 0, fileData.Length );
            fs.Close();
          }
        }
        catch
        {
        }
      }
    }
  }
}
