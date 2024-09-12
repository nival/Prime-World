using System.IO;
using River.Core;

public class ScenarioCheckContext : Scenario
{
  public ScenarioCheckContext()
  {
  }

  public override void Install( IContext context )
  {
    context.SyncInc( "var1" );
  }

  public override void Execute( IContext context )
  {
    context.SyncDec( "var2" );
  }
}