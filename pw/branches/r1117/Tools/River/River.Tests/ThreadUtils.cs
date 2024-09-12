using System.Threading;
using NUnit.Framework;

namespace River.Tests
{
  public static class ThreadUtils
  {
    private const int TIME_OUT = 5000;
    private const int SLEEP_TIME = 10;

    public delegate bool WaitingAction();

    public static void WaitFor( WaitingAction actionTrueToBreak )
    {
      for ( int i = 0; i < TIME_OUT; i += SLEEP_TIME )
      {
        if ( actionTrueToBreak() )
          return;

        Thread.Sleep( SLEEP_TIME );
      }

      Assert.Fail( "Timeout in {0} ms exceded", TIME_OUT );
    }
  }
}
