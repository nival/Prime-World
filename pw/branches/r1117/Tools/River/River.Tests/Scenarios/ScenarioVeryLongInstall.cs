using System.Threading;
using River.Core;

public class ScenarioVeryLongInstall : Scenario
{
  public ScenarioVeryLongInstall()
  {
  }

  public override void Install( IContext context )
  {
    Thread.Sleep( 10000 );
  }
}
