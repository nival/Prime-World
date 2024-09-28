using System.Threading;
using River.Core;

public class ScenarioVeryLongExecute : Scenario
{
  public ScenarioVeryLongExecute()
  {
  }

  public override void Execute( IContext context )
  {
    Thread.Sleep( 10000 );
  }
}
