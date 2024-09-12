using System.IO;
using River.Core;

public class ScenarioInstallAndExecute : Scenario
{
  public ScenarioInstallAndExecute()
  {
  }

  public override void Install( IContext context )
  {
    using ( StreamWriter writer = new StreamWriter( "<FILE1>" ) )
    {
      writer.Write( 'I' );
      writer.Flush();
      writer.Close();
    }
 }

  public override void Execute( IContext context )
  {
    using ( StreamWriter writer = new StreamWriter( "<FILE2>" ) )
    {
      writer.Write( 'E' );
      writer.Flush();
      writer.Close();
    }
  }
}
