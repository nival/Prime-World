using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

namespace DBCodeGen.VisualStudioSupport
{
	public sealed class Solution : IEnumerable<Project>
	{
		private static string projectRegExp = "Project\\(\"\\{([0-9A-Za-z]{8}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{12})}\"\\)\\s*=\\s*\"([a-zA-Z_0-9-\\.\\\\\\/]+)\"\\s*,\\s*\"([a-zA-Z_0-9-:\\.\\\\\\/]*)\"\\s*,\\s*\"\\{([0-9A-Za-z]{8}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{12})}";
		private static Guid vcProjectGuid = new Guid( "8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942" );
		private static Guid vcsProjectGuid = new Guid( "FAE04EC0-301F-11D3-BF4B-00C04F79EFBC" );

		private static Solution empty = new Solution();
		public static Solution Empty { get { return empty; } }

		public static bool IsNullOrEmpty( Solution solution ) { return solution == null || solution.IsEmpty; }

		private Dictionary<string, Project> projects = new Dictionary<string, Project>();
		private string solutionPath = string.Empty;

		private Solution()
		{

		}

		public Solution( string fileName )
		{
			string fullFileName = Path.GetFullPath( fileName );
			solutionPath = Path.GetDirectoryName( fullFileName );

			FileStream file = new FileStream( fileName, FileMode.Open, FileAccess.Read, FileShare.ReadWrite );
			StreamReader reader = new StreamReader( file );
			string line = null;

			while ( (line = reader.ReadLine()) != null )
			{
				Match match = Regex.Match( line, projectRegExp );
				if ( match.Success )
				{
          Guid projectTypeGuid = new Guid(match.Groups[1].Value);
					string projectFileName = match.Groups[3].Value;
					Project project = null;
					if ( projectTypeGuid == vcProjectGuid )
						project = new VCProject( Path.Combine( solutionPath, projectFileName ) );
					else if ( projectTypeGuid == vcsProjectGuid )
						project = new VCSProject( Path.Combine( solutionPath, projectFileName ) );

          if (project != null)
          {
            projects.Add(project.ProjectName, project);
          }
				}
			}
			reader.Close();
			file.Close();
		}

		public Project GetProject( string name )
		{
			Project result = null;
			if ( !projects.TryGetValue( name, out result ) )
				return null;

			return result;
		}

		public void Store( bool dryRun )
		{
			foreach ( Project project in projects.Values )
				project.Store( dryRun );
		}

		public string SolutionPath { get { return solutionPath; } }

		public bool IsEmpty { get { return projects.Count == 0; } }

		public IEnumerator<Project> GetEnumerator()
		{
			return projects.Values.GetEnumerator();
		}

		System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
		{
			return projects.Values.GetEnumerator();
		}
	}
}
