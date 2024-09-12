using System.Text;
using System.IO;
using System.Collections.Generic;
using libdb.IO;
using System;

namespace libdb.DB
{
	public static class GeneratedCodeUtilities
	{
		public static string GetOnlyFileName( string fileName )
		{
			string onlyFileName = FileUtils.GetFileName( fileName );
			int dotPos = onlyFileName.IndexOf( '.' );
			if ( dotPos < 0 )
				return onlyFileName;

			return onlyFileName.Substring( 0, dotPos );
		}

		public static string GenerateRelativePath( DBID dbid, string extension, params string[] args )
		{
      string name = string.Empty;
      if ( args.Length > 0 )
      {
        foreach ( var arg in args )
          name += arg;
      }
      else
      {
        name = FileUtils.GetFileNameWithoutExtension( dbid.FileName );
        if ( dbid.IsInlined )
          name += "_" + dbid.Id.Replace( "-", string.Empty ).ToLower();
      }

      return FileUtils.FixFolderName( FileUtils.GetParentFolderPath( dbid.FileName ) ) + name + "." + extension;
		}

    public static bool CanSetParent( DBResource resource, DBPtrBase parent )
    {
      if ( parent == null || parent.Get<DBResource>() == null )
        return true;

      DBResource p = parent.Get<DBResource>();
      DBFieldInfo parentField = TypeUtils.GetField( resource.GetType(), "__parent", false );
      if ( parentField == null )
        return true;

      while ( p != null )
      {
        if ( resource == p )
        {
          libdb.Diagnostics.Log.TraceError( "Setting parent {0} will create cyclic reference.", parent.DBId.ToString() );
          return false;
        }

        if ( p.DBId.FileName == resource.DBId.FileName )
        {
          libdb.Diagnostics.Log.TraceError( "Object {0} should not be inlined into its parent {1}. ", resource.DBId.ToString(), parent.DBId.ToString() );
          return false;
        }

        DBPtrBase parentPtr = (DBPtrBase)parentField.GetValue( p );
        p = parentPtr == null ? null : parentPtr.Get<DBResource>();
      }

      return true;
    }
  }
}
