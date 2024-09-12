using System;
using System.Collections.Generic;
using System.Text;
using FixSln.Diagnostics;
using System.IO;
using System.Text.RegularExpressions;
using FixSln.Utils;

namespace FixSln.SolutionStruct
{
	public sealed class Solution : IEnumerable<Project>
	{
		private const string projectRegExp = "Project\\(\"\\{([0-9A-Za-z]{8}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{12})}\"\\)\\s*=\\s*\"([a-zA-Z_0-9\\.\\\\\\/]+)\"\\s*,\\s*\"([a-zA-Z_0-9\\.\\\\\\/]*)\"\\s*,\\s*\"\\{([0-9A-Za-z]{8}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{12})}";
		private const string sectionRegExp = "[ \t]*(.*)\\((.*)\\)\\s*=\\s*(.*)";
		private const string dependenciesRegExp = "{([0-9A-Za-z]{8}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{12})}\\s*=\\s*{([0-9A-Za-z]{8}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{12})}";
		private const string slnFileSignature = "Microsoft Visual Studio Solution File, Format Version 10.00";

		#region private struct ProjectInfo

		private struct ProjectInfo
		{
			private readonly string name;
			private readonly string fileName;
			private readonly Guid projectGuid;
			private readonly Guid projectType;

			public ProjectInfo( string name, string fileName, Guid projectType, Guid projectGuid )
			{
				this.name = name;
				this.fileName = fileName;
				this.projectGuid = projectGuid;
				this.projectType = projectType;
			}

			public string Name { get { return name; } }
			public string FileName { get { return fileName; } }
			public Guid ProjectGuid { get { return projectGuid; } }
			public Guid ProjectType { get { return projectType; } }
		};

		#endregion

		private readonly Dictionary<Guid, Project> projects = new Dictionary<Guid, Project>();
		private readonly string filePath = string.Empty;

		private static Project CreateProject( ProjectInfo project )
		{
			if ( project.ProjectType == VCProject.VCProjectTypeGuid )
				return new VCProject( project.Name, project.ProjectGuid, project.FileName );

			if ( project.ProjectType == CSProject.CSProjectTypeGuid )
				return new CSProject( project.Name, project.ProjectGuid, project.FileName );

			if ( project.ProjectType == SolutionFolder.SolutionFolderTypeGuid )
				return new SolutionFolder( project.Name, project.ProjectGuid );

			return new UnknownProject( project.Name, project.ProjectGuid, project.FileName, project.ProjectType );
		}

		public Solution( string filePath ) { this.filePath = FileUtils.FixFileName( System.IO.Path.GetFullPath( filePath ) ); Load(); }

		private void Load()
		{
			Log.TraceMessage( "Loading projects and dependencies from solution \"{0}\"...", filePath );

			List<ProjectInfo> projectsToLoad = new List<ProjectInfo>();
			Dictionary<Guid, List<Guid>> dependencies = new Dictionary<Guid, List<Guid>>();

			using ( StreamReader file = new StreamReader( new FileStream( filePath, System.IO.FileMode.Open, System.IO.FileAccess.Read, System.IO.FileShare.ReadWrite ) ) )
			{
				string solutionPath = System.IO.Path.GetDirectoryName( System.IO.Path.GetFullPath( filePath ) );

				bool signatureFound = false;
				bool inDependencies = false;
				bool inNestedSection = false;

				Guid activeProject = Guid.Empty;

				string line = null;

				while ( ( line = file.ReadLine() ) != null )
				{
					if ( !signatureFound )
						signatureFound = line.IndexOf( slnFileSignature ) != -1;
					else if ( activeProject == Guid.Empty )
					{
						Match match = Regex.Match( line, projectRegExp );
						if ( match.Success )
						{
							activeProject = new Guid( match.Groups[4].Value );
							projectsToLoad.Add( new ProjectInfo( match.Groups[2].Value, System.IO.Path.Combine( solutionPath, match.Groups[3].Value ), new Guid( match.Groups[1].Value ), activeProject ) );
						}
						else
						{
							match = Regex.Match( line, sectionRegExp );
							if ( match.Success && match.Groups[1].Value == "GlobalSection" && match.Groups[2].Value == "NestedProjects" )
								inNestedSection = true;
							else if ( line.IndexOf( "EndGlobalSection" ) != -1 && inNestedSection )
								inNestedSection = false;
							else if ( inNestedSection )
							{
								Match dependence = Regex.Match( line, dependenciesRegExp );
								if ( dependence.Success )
									Utils.Utils.AddToDictionaryList( dependencies, new Guid( dependence.Groups[1].Value ), new Guid( dependence.Groups[2].Value ) );
							}
						}
					}
					else if ( line.IndexOf( "EndProject" ) != -1 )
						activeProject = Guid.Empty;
					else
					{
						Match match = Regex.Match( line, sectionRegExp );
						if ( match.Success && match.Groups[1].Value == "ProjectSection" && match.Groups[2].Value == "ProjectDependencies" )
							inDependencies = true;
						else if ( line.IndexOf( "EndProjectSection" ) != -1 && inDependencies )
							inDependencies = false;
						else if ( inDependencies )
						{
							Match dependence = Regex.Match( line, dependenciesRegExp );
							if ( dependence.Success )
								Utils.Utils.AddToDictionaryList( dependencies, activeProject, new Guid( dependence.Groups[1].Value ) );
						}
					}
				}
			}

			foreach ( var projectInfo in projectsToLoad )
			{
				Project project = CreateProject( projectInfo );
				project.Load();

				projects.Add( project.Guid, project );
			}

			foreach ( var depend in dependencies )
			{
				List<Project> projs = new List<Project>();
				foreach ( var guid in depend.Value )
					projs.Add( projects[guid] );
				projects[depend.Key].AssignDepends( projs );
			}
		}

		public string Path { get { return System.IO.Path.GetDirectoryName( System.IO.Path.GetFullPath( filePath ) ); } }
		public string FilePath { get { return filePath; } }

		#region IEnumerable... Members

		public IEnumerator<Project> GetEnumerator() { return projects.Values.GetEnumerator(); }

		System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() { return projects.Values.GetEnumerator(); }

		#endregion
	}
}
