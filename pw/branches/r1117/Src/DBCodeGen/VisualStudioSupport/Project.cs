using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;
using DBCodeGen.Utils;
using System.Diagnostics;

namespace DBCodeGen.VisualStudioSupport
{
	public abstract class Project
	{
		private Dictionary<string, string> files = new Dictionary<string, string>();
		private List<string> addedFiles = new List<string>();
		private string projectName = string.Empty;
		private readonly string projectFileName = string.Empty;
		private readonly string projectPath = string.Empty;

		protected void SetProjectName( string name )
		{
			projectName = name;
		}

		protected Project( string fileName )
		{
			string fullProjectFileName = Path.GetFullPath( fileName );
			projectFileName = Path.GetFileName( fullProjectFileName );
			projectPath = Path.GetDirectoryName( fullProjectFileName );
		}

		protected virtual string GetFileNameInProject( string fileName )
		{
			string fullFileName = Path.GetFullPath( fileName );
			if ( fullFileName.StartsWith( projectPath, StringComparison.InvariantCultureIgnoreCase ) )
			{
				fullFileName = fullFileName.Substring( projectPath.Length );
				if ( fullFileName.Length > 0 && ( fullFileName[0] == '\\' || fullFileName[0] == '/' ) )
					fullFileName = fullFileName.Substring( 1 );
				return Path.Combine( ProjectPath, fullFileName );
			}

			return Path.Combine( ProjectPath, fileName );
		}

		protected void RegisterFile( string fileName )
		{
			string fullFilePath = GetFileNameInProject( fileName );
			if ( files.ContainsKey( fullFilePath.ToLower() ) )
				Trace.TraceError( "File \"{0}\" defined twice for project \"{1}\"", fileName, projectName );
			files.Add( fullFilePath.ToLower(), fileName );
		}

		protected XmlDocument LoadProject()
		{
			XmlDocument result = new XmlDocument();
			FileStream file = new FileStream( GetFileNameInProject( ProjectFileName ), FileMode.Open, FileAccess.Read, FileShare.ReadWrite );
			result.Load( file );
			file.Close();

			return result;
		}

		protected static FileStream CreateFileInternal( string fileName )
		{
			string backupFileName = fileName + ".backup";
			if ( System.IO.File.Exists( backupFileName ) )
			{
				System.IO.File.SetAttributes( backupFileName, FileAttributes.Normal );
				System.IO.File.Delete( backupFileName );
			}
			if ( System.IO.File.Exists( fileName ) )
				System.IO.File.Move( fileName, fileName + ".backup" );

			return new FileStream( fileName, System.IO.FileMode.CreateNew, System.IO.FileAccess.Write, System.IO.FileShare.Read );
		}

		protected abstract XmlDocument StoreProject();
		public void Store( bool dryRun )
		{
			if ( !IsModified )
				return;

			XmlDocument project = StoreProject();
			if ( project == null )
				return;

			if ( !dryRun )
			{
				XmlWriterSettings settings = new XmlWriterSettings();
				settings.Indent = true;
				settings.IndentChars = "\t";
				settings.NewLineOnAttributes = true;
				settings.CloseOutput = true;

				FileStream file = CreateFileInternal( GetFileNameInProject( ProjectFileName ) );
				XmlWriter writer = XmlWriter.Create( file, settings );
				project.Save( writer );
				writer.Close();
			}
		}

		public bool IsFileInProject( string fileName )
		{
			string fullFilePath = GetFileNameInProject( fileName );
			return files.ContainsKey( fullFilePath.ToLower() );
		}

		public void AddFile( string fileName )
		{
			if ( !IsFileInProject( fileName ) )
			{
				string fullFilePath = GetFileNameInProject( fileName );
				addedFiles.Add( fileName );
				files.Add( fullFilePath.ToLower(), fileName );
			}
		}

		public CodeWriter CreateFile( string fileName )
		{
			if ( !IsFileInProject( fileName ) )
				AddFile( fileName );

			return new CodeWriter( GetFileNameInProject( fileName ) );
		}

		protected IEnumerable<string> AddedFiles { get { return addedFiles; } }

		public string ProjectName { get { return projectName; } }
		public string ProjectFileName { get { return projectFileName; } }
		public string ProjectPath { get { return projectPath; } }

		public bool IsModified { get { return addedFiles.Count > 0; } }

		public IEnumerable<string> Files { get { return files.Values; } }
	}
}
