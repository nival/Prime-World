using System;

namespace River.Core
{
	public class Scenario : MarshalByRefObject
	{
    public override object InitializeLifetimeService()
    {
      return null;
    }

		/// <summary>
		/// Prepare test for execution (copy all files, patch files etc). Throw an exception if installation fails
		/// </summary>
		public virtual void Install( IContext context ) { }

		/// <summary>
		/// Core test function. Called after installation all tests from scenarion. Throw an exception if execution fails
		/// </summary>
		public virtual void Execute( IContext context ) { }
	}
}
