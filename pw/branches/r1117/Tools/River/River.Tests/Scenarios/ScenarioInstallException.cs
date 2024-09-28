using System;
using River.Core;

public class ScenarioInstallException : Scenario
{
  public ScenarioInstallException()
  {
  }

  public override void Install( IContext context )
  {
    throw new Exception( "InstallException" );
  }
}
