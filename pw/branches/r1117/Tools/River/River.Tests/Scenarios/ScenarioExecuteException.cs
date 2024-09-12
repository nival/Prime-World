using System;
using River.Core;

public class ScenarioExecuteException : Scenario
{
  public ScenarioExecuteException()
  {
  }

  public override void Execute( IContext context )
  {
    throw new Exception( "ExecuteException" );
  }
}
