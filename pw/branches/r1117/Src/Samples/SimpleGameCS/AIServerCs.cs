using System.Collections.Generic;
using System.Text;
using ManagedRPC;
using ServerRunner;
using System.Runtime.InteropServices;
using System.Threading;

namespace CsRPC
{
  class RLocationServer
  {
    uint ID;
    uint CRC32;
    RClassCallInfo info = null;
    Environment env = null;

    public RLocationServer()
    {
    }

    public RLocationServer( Environment _env )
    {
      ID = 0x1e8ac7bd;
      CRC32 = 0x326ac1fd;
      env = _env;
    }

    public void RegisterRClass()
    {
      info = EntitiesContainer.RegisterRClass( env, ID, CRC32 );
    }

    public void QueryRClass( string name )
    {
      EntitiesContainer.Query( SetRClassCallInfo, env, ID, CRC32, name );
    }

    private void SetRClassCallInfo( RClassCallInfo _info )
    {
      info = _info;
    }

    public void RegisterPlayer( System.UInt16 userId, System.Byte cellx, System.Byte celly )
    {
      object[] pars = new object[3] { userId, cellx, celly };
      if ( info != null )
        EntitiesContainer.CallRClassMethod( info, 0, pars );
    }

    public void MovePlayer( System.UInt16 userId, float fromx, float fromy, float tox, float toy, double time )
    {
      object[] pars = new object[6] { userId, fromx, fromy, tox, toy, time };
      if ( info != null )
        EntitiesContainer.CallRClassMethod( info, 1, pars );
    }

    public void TouchObject( System.UInt16 userId )
    {
      object[] pars = new object[1] { userId };
      if ( info != null )
        EntitiesContainer.CallRClassMethod( info, 2, pars );
    }
  }

  class AIServerRunner : CSServerRunner
  {
    public override void SetUp()
    {

    }
    public override void Start()
    {

    }
    public override void Stop()
    {

    }
    public override string GetId()
    {
      return "aiserver";
    }
  }

  class Program
  {
    static void Main( string[] args )
    {
      CSServerFactory factory = new CSServerFactory();
      AIServerRunner aiserver = new AIServerRunner();
      factory.RegisterServerRunner( "aiserver", aiserver );
      factory.Start();
      Environment env = factory.GetEnvironment();
      RLocationServer server = new RLocationServer( env );
      server.QueryRClass( "location_server" );
      System.Random rand = new System.Random();
      while ( true )
      {
        factory.Pool();
        Thread.Sleep( 1000 );
        server.MovePlayer( 0, 300, 200, 300.0f + (float)rand.NextDouble() * 50.0f, 200.0f + (float)rand.NextDouble() * 50.0f, 10 );
      }
    }
  }
}
