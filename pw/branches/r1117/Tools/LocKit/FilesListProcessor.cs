using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;

namespace LocKit
{
  public static class FilesListProcessor
  {
    private static List<KeyValuePair<string, string>> ReadFilesList( string filesListFile )
    {
      List<KeyValuePair<string, string>> result = new List<KeyValuePair<string, string>>();
      string[] lines = File.ReadAllLines( filesListFile );
      foreach ( var line in lines )
      {
        string fileName = line.Trim();
        string destFolder = string.Empty;
        int eqPos = fileName.IndexOf( '=' );
        if ( eqPos >= 0 )
        {
          destFolder = fileName.Substring( eqPos + 1 ).Trim();
          fileName = fileName.Substring( 0, eqPos ).Trim();
        }
        result.Add( new KeyValuePair<string, string>( fileName, destFolder ) );
      }

      return result;
    }

    private static string GetDataFileName( string dataPath, KeyValuePair<string, string> file )
    {
      //return Path.Combine( dataPath, file.Key );
      return Path.Combine(Path.Combine(dataPath, file.Value), Path.GetFileName(file.Key));
    }

    private static string GetTranslateFileName( string translatePath, KeyValuePair<string, string> file )
    {
      //return Path.Combine( Path.Combine( translatePath, file.Value ), Path.GetFileName( file.Key ) );
      return Path.Combine(translatePath, Path.GetFileName(file.Key));
    }

    public static void CopyFilesFromData( string dataPath, string translatePath, string filesListFile )
    {
      List<KeyValuePair<string, string>> files = ReadFilesList( filesListFile );
      foreach ( var file in files )
      {
        string srcFile = GetDataFileName( dataPath, file );
        string destFile = GetTranslateFileName( translatePath, file );
        if ( !File.Exists( srcFile ) )
          Trace.TraceWarning( "File \"{0}\" not found (\"{1}\")", file.Key, srcFile );
        else
        {
          try
          {
            File.Copy( srcFile, destFile, true );
          }
          catch ( Exception e )
          {
            Trace.TraceWarning( "Cannot copy \"{0}\" to \"{1}\". {2}", srcFile, destFile, e.Message );
          }
        }
      }
    }

    public static void VerifyTranslatedFiles( string translatePath, string filesListFile, Dictionary<string, object> brokenFiles )
    {
      List<KeyValuePair<string, string>> files = ReadFilesList( filesListFile );
      foreach ( var file in files )
      {
        string srcFile = GetTranslateFileName( translatePath, file );
        if ( !File.Exists( srcFile ) )
        {
          Trace.TraceWarning( "File \"{0}\" not found (\"{1}\")", file.Key, srcFile );
          brokenFiles.Add( srcFile, null );
        }
      }
    }

    public static void UpdateFileInData( string dataPath, string translatePath, string filesListFile, string resultFileName, Dictionary<string, object> brokenFiles )
    {
      List<string> result = new List<string>();
      List<KeyValuePair<string, string>> files = ReadFilesList( filesListFile );
      foreach ( var file in files )
      {
        string srcFile = GetTranslateFileName( translatePath, file );
        string destFile = GetDataFileName( dataPath, file );

        if ( brokenFiles.ContainsKey( srcFile ) )
          continue;

        if ( !File.Exists( destFile ) )
          Trace.TraceInformation( "Data file \"{0}\" not found (\"{1}\")", file.Key, destFile );

        if ( !File.Exists( srcFile ) )
          Trace.TraceWarning( "File \"{0}\" not found (\"{1}\")", file.Key, srcFile );
        else
        {
          try
          {
            if ( !Directory.Exists( Path.GetDirectoryName( destFile ) ) )
              Directory.CreateDirectory( Path.GetDirectoryName( destFile ) );
            File.Copy( srcFile, destFile, true );
            result.Add( file.Key );
          }
          catch ( Exception e )
          {
            Trace.TraceWarning( "Cannot copy \"{0}\" to \"{1}\". {2}", srcFile, destFile, e.Message );
          }
        }
      }

      if ( !string.IsNullOrEmpty( resultFileName ) )
        File.WriteAllLines( resultFileName, result.ToArray() );
    }
  }
}
