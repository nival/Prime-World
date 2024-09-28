using System;
using System.IO;
using System.Threading;
using River.Core;

public class ScenarioCurrentDirectory : Scenario
{
  private bool throwInstallException = false;
  private bool throwExecuteException = false;
  private bool waitInInstall = false;
  private bool waitInExecute = false;

  public ScenarioCurrentDirectory()
  {
  }

  public override void Install( IContext context )
  {
    using ( StreamWriter writer = new StreamWriter( "<FILE1>" ) )
    {
      writer.Write( Environment.CurrentDirectory );
      writer.Flush();
      writer.Close();
    }

    if ( waitInInstall )
      Thread.Sleep( 10000 );

    if ( throwInstallException )
      throw new Exception();
 }

  public override void Execute( IContext context )
  {
    using ( StreamWriter writer = new StreamWriter( "<FILE2>" ) )
    {
      writer.Write( Environment.CurrentDirectory );
      writer.Flush();
      writer.Close();
    }

    if ( waitInExecute )
      Thread.Sleep( 10000 );

    if ( throwExecuteException )
      throw new Exception();
  }
}
