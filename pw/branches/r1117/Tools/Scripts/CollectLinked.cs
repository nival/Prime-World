/*
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
*/

using System.Collections;
using System.Collections.Generic;
using System.IO;
using EditorLib;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;

namespace Scripts
{
  public class CollectLinked
  {
    public class LinksCollector
    {
      private readonly Dictionary<DBID, bool> ptrs = new Dictionary<DBID, bool>();
      private readonly Dictionary<DBID, bool> allPtrs = new Dictionary<DBID, bool>();
      private readonly Dictionary<string, bool> files = new Dictionary<string, bool>();

      public bool Visitor( ref object obj, DBFieldInfo field )
      {
        if ( obj.GetType() == typeof( string ) && TypeUtils.HasAttribute<DstFileAttribute>( field, true ) )
        {
          var file = (string)obj;
          if ( DataBase.FileSystem.GetFileInfo( file ).IsFileExists )
          {
            if ( !files.ContainsKey( file ) )
              files.Add( file, true );
          }
        }
        else if ( obj is TextRef )
        {
          var file = ( (TextRef)obj ).FileName;
          if ( DataBase.FileSystem.GetFileInfo( file ).IsFileExists )
          {
            if ( !files.ContainsKey( file ) )
              files.Add( file, true );
          }
        }

        return true;
      }

      public bool Depth( object obj, ref int depth )
      {
        if ( !( obj is DBPtrBase ) )
          return true;

        var ptr = (DBPtrBase)obj;
        var dbid = DBID.FromDBID( ptr.DBId, false );
        if ( !dbid.IsEmpty && !ptrs.ContainsKey( dbid ) )
          ptrs.Add( dbid, true );

        if ( allPtrs.ContainsKey( ptr.DBId ) )
          return false;

        allPtrs.Add( ptr.DBId, true );
        return true;
      }

      public string[] GetDstFiles()
      {
        List<string> files = new List<string>( this.files.Keys );
        files.Sort();
        return files.ToArray();
      }

      public DBID[] GetPtrs()
      {
        List<DBID> dbids = new List<DBID>( ptrs.Keys );
        dbids.Sort( DBID.Compare );
        return dbids.ToArray();
      }
    }

    private void CopyFile( IFileSystem fileSystem, string fileName, string dstFileName )
    {
      byte[] bytes = FileUtils.ReadFile( fileSystem, fileName );
      string path = Path.GetDirectoryName( Path.GetFullPath( dstFileName ) );
      if ( !Directory.Exists( path ) )
        Directory.CreateDirectory( path );
      File.WriteAllBytes( dstFileName, bytes );
    }

    public IEnumerable Main( IEditorCommonApplication application, string[] args )
    {
      if ( args.Length < 1 || args.Length > 2 )
      {
        Log.TraceWarning( "Usage: CollectLinked.cs <root> [<folder_to_copy>]" );
        yield return false;
      }

      DBPtr<DBResource> ptr = DataBase.Get<DBResource>( DBID.FromString( args[0] ) );
      if ( ptr == null || ptr.Get() == null )
      {
        Log.TraceWarning( "Cannot load resource {0}", args[0] );
        yield return false;
      }

      LinksCollector collector = new LinksCollector();
      FieldsWalker.VisitFields( ptr.Get(), collector.Visitor, collector.Depth );

      foreach ( var dbid in collector.GetPtrs() )
      {
        Log.TraceMessage( string.Format( "{0}", dbid ) );
        if ( args.Length > 1 )
          CopyFile( application.FileSystem, dbid.GetFullFileName(), args[1] + dbid.GetFullFileName() );
      }
      foreach ( var file in collector.GetDstFiles() )
      {
        Log.TraceMessage( string.Format( "{0}", file ) );
        if ( args.Length > 1 )
          CopyFile( application.FileSystem, file, args[1] + file );
      }

      yield return true;
    }
  }
}
