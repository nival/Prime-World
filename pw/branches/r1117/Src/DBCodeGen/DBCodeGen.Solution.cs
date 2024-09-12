using DBCodeGen.VisualStudioSupport;
using System.Diagnostics;

namespace DBCodeGen
{
	internal sealed partial class DBCodeGen
	{
		private static Solution solution = Solution.Empty;

		private static void LoadSolution()
		{
			if ( !string.IsNullOrEmpty( solutionFileName ) )
			{
				Trace.TraceInformation( "Loading solution from \"{0}\"... ", solutionFileName );
				solution = new Solution( solutionFileName );
			}
		}

		private static void StoreSolution()
		{
			if ( solution != null && !solution.IsEmpty )
			{
				Trace.TraceInformation( "Storing projects from solution \"{0}\"... ", solutionFileName );
				solution.Store( dryRun );
			}
		}
	}
}
