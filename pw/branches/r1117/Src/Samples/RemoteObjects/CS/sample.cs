using System.Collections.Generic;
using System.Text;
using ManagedRPC;
using System.Runtime.InteropServices;
using System.Threading;

namespace CsRPC
{
  class Program
  {
    static void GetInt( System.Int32 result )
    {
      System.Console.WriteLine( result );
    }

    static void Main( string[] args )
    {
      Environment env = new Environment();

      System.ConsoleKeyInfo keyinfo = System.Console.ReadKey();

      if ( keyinfo.KeyChar == 's' || keyinfo.KeyChar == 'S' )
      {
        System.Console.WriteLine();
        env.Server();
        EntitiesContainer.RegisterType( test.LHelloWorld.ID, typeof( test.LHelloWorld ) );
        while ( true )
        {
          env.Poll();
          Thread.Sleep( 10 );
        }
      }
      else if ( keyinfo.KeyChar == 'c' || keyinfo.KeyChar == 'C' )
      {
        System.Console.WriteLine();
        if ( env.Connect() )
        {
          System.Console.WriteLine( "Connetced" );
        }
        else
        {
          System.Console.WriteLine( "Fail" );
        }

        test.RHelloWorld hw = new test.RHelloWorld( env );
        hw.RegisterRClass();
        hw.Print( "From C#" );
        Thread.Sleep( 100 );
        env.Poll();
        hw.GetInt( 10, GetInt );
        Thread.Sleep( 100 );
        env.Poll();
        Thread.Sleep( 100 );
        env.Poll();
        Thread.Sleep( 100 );
        env.Poll();
      }
    }
  }
}
