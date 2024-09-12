using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
using System.Text.RegularExpressions;
using FixSln.Diagnostics;

namespace FixSln.SolutionStruct
{
	public sealed class VCProject : Project
	{
		public static Guid VCProjectTypeGuid = new Guid( "8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942" );

		public VCProject( string name, Guid guid, string filePath ) : base( name, guid, filePath ) { }

		private static string CombineFilter( string a, string b )
		{
			if ( string.IsNullOrEmpty( a ) )
				return b;

			return a + "/" + b;
		}

		private static string FilterUp( string filter )
		{
			int pos = filter.LastIndexOf( '/' );
			if (pos < 0 )
				return string.Empty;

			return filter.Substring( 0, pos );
		}

		private void LoadFiles( XmlElement files, string filter )
		{
			if ( files == null )
				return;

			foreach ( XmlNode node in files )
			{
				if ( node.NodeType != XmlNodeType.Element )
					continue;

				if ( node.Name == "Filter" )
					LoadFiles( node as XmlElement, CombineFilter( filter, node.Attributes["Name"].Value ) );
				else if ( node.Name == "File" )
					AddFile( node.Attributes["RelativePath"].Value, filter );
			}
		}

		private Dictionary<string, List<string>> addedFiles = new Dictionary<string, List<string>>();
		public void AddFileToVCProject( string filter, string filePath )
		{
			List<string> files = null;
			if ( !addedFiles.TryGetValue( filter.ToLower(), out files ) )
			{
				files = new List<string>();
				addedFiles.Add( filter.ToLower(), files );
			}
			files.Add( filePath );
		}

		private int InsertFiles( List<string> lines, int index, string filter )
		{
			List<string> files = null;
			if ( !addedFiles.TryGetValue( filter.ToLower(), out files ) )
				return index;

			string prefix = lines[index].Substring( 0, lines[index].IndexOf( '<' ) );
			foreach ( string file in files )
			{
				lines.Insert( index + 0, prefix + "<File" );
				lines.Insert( index + 1, prefix + string.Format( "\tRelativePath=\"{0}\"", file ) );
				lines.Insert( index + 2, prefix + "\t>" );
				lines.Insert( index + 3, prefix + "</File>" );
				index += 4;
			}

			addedFiles.Remove( filter.ToLower() );
			return index;
		}

		public void StoreVCProj()
		{
			if ( addedFiles.Count == 0 )
				return;

			List<string> lines = new List<string>();
			using ( TextReader reader = new StreamReader( FilePath ) )
			{
				string line = string.Empty;
				while ( ( line = reader.ReadLine() ) != null )
					lines.Add( line );
				reader.Close();
			}

			string filter = null;
			int firstFileLine = 0;
			for ( int i = 0; i < lines.Count; ++i )
			{
				if ( lines[i].IndexOf( "<Files>" ) >= 0 )
				{
					filter = string.Empty;
					i = InsertFiles( lines, i + 1, filter );
					firstFileLine = i;
				}
				else if ( filter == null )
					continue;

				if ( lines[i].TrimStart( ' ', '\t' ).StartsWith( "<Filter" ) && lines[i + 1].TrimStart( ' ', '\t' ).StartsWith( "Name=\"" ) )
				{
					filter = CombineFilter( filter, Regex.Match( lines[i + 1], "\\s*Name=\"([A-Za-z0-9_]+)\"" ).Groups[1].Value );
					i += 1;
					while ( lines[i].IndexOf( '>' ) < 0 )
						++i;
					i = InsertFiles( lines, i + 1, filter ) - 1;
				}
				if ( lines[i].IndexOf( "</Filter>", StringComparison.InvariantCultureIgnoreCase ) >= 0 )
					filter = FilterUp( filter );
			}

			using ( TextWriter writer = new StreamWriter( FilePath, false ) )
			{
				foreach ( string line in lines )
					writer.WriteLine( line );
				writer.Flush();
				writer.Close();
			}
		}

		protected override void ParseXml( XmlElement doc )
		{
			LoadFiles( doc.SelectSingleNode( "Files" ) as XmlElement, string.Empty );
		}

		public override void Move( string path, FixSln.Utils.FileMover mover )
		{
			base.Move( path, mover );

			Dictionary<string, List<string>> files = new Dictionary<string, List<string>>();
			foreach ( var file in this )
			{
				if ( string.IsNullOrEmpty( file.Filter ) )
					continue;

				string filePath = System.IO.Path.GetFullPath( System.IO.Path.Combine( Path, System.IO.Path.Combine( file.Path, file.Name ) ) );
				string toPath = System.IO.Path.Combine( file.Project.Path, file.Filter );

				if ( string.Compare( file.Filter, "Common", StringComparison.InvariantCultureIgnoreCase ) == 0 )
				{
					if ( file.Name.IndexOf( "stdafx", StringComparison.InvariantCultureIgnoreCase ) < 0 && string.Compare( file.Name, "specific.h", StringComparison.InvariantCultureIgnoreCase ) != 0 )
					{
						Log.TraceWarning( "\"{0}\": Invalid file under Common filter: \"{1}\"", Name, System.IO.Path.Combine( file.Path, file.Name ) );
						Utils.Utils.AddToDictionaryList( files, toPath, filePath );
					}
				}
				else
					Utils.Utils.AddToDictionaryList( files, toPath, filePath );
			}
			foreach ( var filter in files )
				mover.Move( filter.Value, filter.Key );
		}

		public override Guid TypeGuid { get { return VCProjectTypeGuid; } }
	}
}
