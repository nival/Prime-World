using System;
using System.Text.RegularExpressions;
using libdb.DB;

namespace DBCodeGen.VisualStudioSupport
{
	public class CodeFile
	{
		private const string TYPE_NAME_REGEXP = "([_A-Za-z][_A-Za-z0-9]*)\\.([_A-Za-z][_A-Za-z0-9]*)\\.([_A-Za-z][_A-Za-z0-9]*)";

		private readonly string project = string.Empty;
		private readonly string name = string.Empty;

    public string ForcedIncludeFile { get; private set; }

    public CodeFile( string project, string name ) { this.project = project; this.name = name; this.ForcedIncludeFile = string.Empty; }

    public CodeFile( string forcedInclude ) { this.ForcedIncludeFile = forcedInclude; }

    public static CodeFile CreateFile( Type type )
    {
      NoCodeAttribute noCodeAttr = TypeUtils.GetAttribute<NoCodeAttribute>( type, false );
      if ( null != noCodeAttr && !string.IsNullOrEmpty( noCodeAttr.IncludeFile ) )
      {
        return new CodeFile( noCodeAttr.IncludeFile );
      }

      Match typeNameMatch = Regex.Match( type.FullName, TYPE_NAME_REGEXP );
      if ( !typeNameMatch.Success )
        return null;

      return new CodeFile( typeNameMatch.Groups[1].Value, typeNameMatch.Groups[2].Value );
    }

    public static CodeFile CreateFile( string name )
    {
      return new CodeFile( string.Empty, name + ".auto" );
    }

		public string Project { get { return project; } }
		public string Name { get { return name; } }

		public override bool Equals( object obj )
		{
			CodeFile file = obj as CodeFile;
			if ( file != null )
				return string.Compare( file.Name, Name, true ) == 0 && string.Compare( file.Project, Project, true ) == 0;

			return base.Equals( obj );
		}

		public override int GetHashCode()
		{
			return Name.GetHashCode() ^ Project.GetHashCode();
		}

		public static bool operator ==( CodeFile file1, CodeFile file2 )
		{
			if ( (object)file1 == null )
				return (object)file2 == null;
			return file1.Equals( file2 );
		}

		public static bool operator !=( CodeFile file1, CodeFile file2 )
		{
			if ( (object)file1 == null )
				return (object)file2 != null;
			return !file1.Equals( file2 );
		}

		public static int Compare( CodeFile file1, CodeFile file2 )
		{
			int result = string.Compare( file1.Project, file2.Project, true );
			if ( result == 0 )
				return string.Compare( file1.Name, file2.Name, true );

			return result;
		}

		public static bool IsValidType( Type type )
		{
      return Regex.IsMatch( type.FullName, TYPE_NAME_REGEXP );;
		}

		public static bool TryGetProject( Type type, out string projectName )
		{
			projectName = string.Empty;
			Match typeNameMatch = Regex.Match( type.FullName, TYPE_NAME_REGEXP );
			if ( !typeNameMatch.Success )
				return false;

			projectName = typeNameMatch.Groups[1].Value;
			return true;
		}

		public static string GetProject( Type type )
		{
			string result = string.Empty;
			if ( !TryGetProject( type, out result ) )
				return string.Empty;

			return result;
		}
	}
}
