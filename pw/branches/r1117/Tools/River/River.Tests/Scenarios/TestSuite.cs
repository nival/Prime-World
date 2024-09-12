using River.Core;
using System.IO;
using System.Diagnostics;

[DistributeAttribute]
class TestScenario : Scenario
{
  public override void Install( IContext context )
	{
		File.Copy( @"c:\Home\foo_cs2\foo_cs2\bin\Debug\foo_cs2.exe", @".\foo_cs.exe" );
	}

  public override void Execute( IContext context )
	{
		Process p = Process.Start( @".\foo_cs.exe", context.GetBotsWithTest( GetType().Name )[0].Name );
		p.WaitForExit();
	}
}
