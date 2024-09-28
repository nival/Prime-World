using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Diagnostics;

namespace DBCodeGen.SourceCompiler
{
  public class SearchFolders
  {
    private readonly List<string> searchFolders = new List<string>();

    public SearchFolders() { }

    public bool AddSearchFolder( string folderPath )
    {
      string fullFolderPath = Path.GetFullPath( folderPath );
      if ( !Directory.Exists( fullFolderPath ) )
      {
        Trace.TraceError( "Folder \"{0}\" not found", folderPath );
        return false;
      }

      if ( searchFolders.Exists( path => string.Compare( path, fullFolderPath, StringComparison.InvariantCultureIgnoreCase ) == 0 ) )
      {
        Trace.TraceWarning( "Search folder \"{0}\" defined twice", folderPath );
        return true;
      }

      searchFolders.Add( fullFolderPath );
      return true;
    }

    public bool AddSearchFolders( IEnumerable<string> foldersPaths )
    {
      foreach ( string folderPath in foldersPaths )
      {
        if ( !AddSearchFolder( folderPath ) )
          return false;
      }
      return true;
    }

    private bool TryGetFullFileName( string filePath, string fileName, out string fullFileName )
    {
      string relativeFileName = Path.Combine( filePath, fileName );
      if ( !string.IsNullOrEmpty( filePath ) && File.Exists( relativeFileName ) )
      {
        fullFileName = Path.GetFullPath( relativeFileName );
        return true;
      }

      foreach ( var searchFolder in searchFolders )
      {
        string tempFileName = Path.Combine( searchFolder, fileName );
        if ( File.Exists( tempFileName ) )
        {
          fullFileName = Path.GetFullPath( tempFileName );
          return true;
        }
      }

      fullFileName = fileName;
      return false;
    }

    public string GetFullFileName( string filePath, string fileName )
    {
      string fullFileName;
      if ( !TryGetFullFileName( filePath, fileName, out fullFileName ) )
        return string.Empty;

      return fullFileName;
    }
  }
}
