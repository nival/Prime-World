using System;
using System.Collections.Generic;
using System.Xml;
using FixSln.Diagnostics;
using FixSln.Utils;
using SharpSvn;

namespace FixSln.SolutionStruct
{
	public abstract class Project : IEnumerable<Project.File>
	{
		#region public sealed class File

		public sealed class File
		{
			private readonly Project project = null;
			private readonly string initialPath = string.Empty;
			private string filter = string.Empty;
			private string name = string.Empty;
			private string path = string.Empty;

			internal File( string filePath, Project project, string filter )
			{
				this.filter = filter;
				this.project = project;

				name = System.IO.Path.GetFileName( filePath );
				path = System.IO.Path.GetDirectoryName( filePath );

				initialPath = System.IO.Path.GetFullPath( System.IO.Path.Combine( Project.Path, Path ) );
			}

			public void OnProjectPathChanged()
			{
				if ( !Path.StartsWith( ".." ) )
					return;

				path = FileUtils.GetRelativePath( Project.Path, InititalPath );
			}

			public string Name { get { return name; } }
			public Project Project { get { return project; } }
			public string Filter { get { return filter; } set { filter = value; } }
			public string Path { get { return path; } }
			public string InititalPath { get { return initialPath; } }
		}

		#endregion

		private readonly string name = string.Empty;
		private readonly Guid guid = Guid.Empty;
		
		private string filePath = string.Empty;
		private string filter = null;

		private readonly Dictionary<string, File> files = new Dictionary<string, File>();
		private readonly Dictionary<Project, bool> depends = new Dictionary<Project, bool>();

		protected Project( string name, Guid guid, string filePath )
		{
			this.name = name; 
			this.guid = guid;

			this.filePath = FileUtils.FixFileName( filePath );

			if ( !string.IsNullOrEmpty( filePath ) )
				AddFile( System.IO.Path.GetFileName( filePath ), string.Empty );
		}

		public void AddFile( string filePath, string filter )
		{
			string fullFilePath = System.IO.Path.GetFullPath( System.IO.Path.Combine( Path, filePath ) );
			if ( !System.IO.File.Exists( fullFilePath ) )
			{
				Log.TraceError( "\"{0}\": \"{1}\": Reference to unexists file", Name, filePath );
				return;
			}

			File file = new File( filePath, this, filter );
			files.Add( fullFilePath.ToLower(), file );
		}

		protected virtual void ParseXml( XmlElement doc )
		{

		}

		public virtual void Load()
		{
			Log.TraceMessage( "Loading project \"{0}\" (\"{1}\")...", Name, filePath );

			XmlDocument doc = new XmlDocument();

			using ( var file = new System.IO.FileStream( filePath, System.IO.FileMode.Open, System.IO.FileAccess.Read, System.IO.FileShare.ReadWrite ) )
			{
				doc.PreserveWhitespace = true;
				doc.Load( file );
			}

			ParseXml( doc.DocumentElement );
		}

		public void AssignDepends( IEnumerable<Project> depends )
		{
			foreach ( Project p in depends )
				this.depends.Add( p, true );
		}

		public File FindFile( string filePath )
		{
			string invariantFilePath = FileUtils.FixFileName( System.IO.Path.GetFullPath( filePath ) ).ToLower();
			File result = null;
			if ( files.TryGetValue( invariantFilePath, out result ) )
				return result;

			return null;
		}

		private void UpdateFilter()
		{
			if ( filter != null )
				return;

			filter = string.Empty;
			foreach ( var proj in depends.Keys )
			{
				if ( proj is SolutionFolder )
				{
					if ( string.IsNullOrEmpty( proj.Filter ) )
						filter = proj.Name;
					else
						filter = proj.Filter + "\\" + proj.Name;
				}
			}
		}

		public virtual void Move( string path, FileMover mover )
		{
			if ( string.IsNullOrEmpty( filePath ) )
				return;

			Log.TraceMessage( "Move project \"{0}\" to folder \"{1}\"...", Name, path );
			string prevPath = System.IO.Path.GetDirectoryName( filePath );
			mover.Move( prevPath, path );

			filePath = System.IO.Path.Combine( path, System.IO.Path.GetFileName( filePath ) );

			foreach ( var file in this )
				file.OnProjectPathChanged();
		}

		public int FilesCount { get { return files.Count; } }

		public string Name { get { return name; } }
		public Guid Guid { get { return guid; } }
		public string Path { get { return System.IO.Path.GetDirectoryName( System.IO.Path.GetFullPath( filePath ) ); } }
		public abstract Guid TypeGuid { get; }

		public string FilePath { get { return filePath; } }
		public string Filter { get { UpdateFilter(); return filter; } }

		#region IEnumerable... Members

		public IEnumerator<Project.File> GetEnumerator() { return files.Values.GetEnumerator(); }

		System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() { return files.Values.GetEnumerator(); }

		#endregion
	}
}
