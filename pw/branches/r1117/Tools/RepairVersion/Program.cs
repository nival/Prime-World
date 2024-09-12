using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;

namespace copycontent
{
  class Program
  {
    private static void CopyFolder( string source, string dest )
    {
      Console.WriteLine( "Collecting files in \"{0}\"...", source );
      List<KeyValuePair<string, long>> files = new List<KeyValuePair<string, long>>();
      List<string> folders = new List<string>();
      folders.Add( source );
      while ( folders.Count > 0 )
      {
        string path = folders[0];
        folders.RemoveAt( 0 );
        foreach ( var filePath in Directory.GetFiles( path ) )
          files.Add( new KeyValuePair<string, long>( filePath.Substring( source.Length ), 0 ) );
        foreach ( var dirPath in Directory.GetDirectories( path ) )
          folders.Add( dirPath );
      }
      Console.WriteLine( "  Found \"{0}\" files...", files.Count );

      for ( int i = 0; i < files.Count; ++i )
      {
        string sourcePath = Path.Combine( source, files[i].Key );
        files[i] = new KeyValuePair<string, long>( files[i].Key, new FileInfo( sourcePath ).Length );
        Console.WriteLine( "  \"{0}\", {1}...", files[i].Key, files[i].Value );
        string fullFilePath = Path.Combine( dest, files[i].Key );
        if ( !Directory.Exists( Path.GetDirectoryName( fullFilePath ) ) )
          Directory.CreateDirectory( Path.GetDirectoryName( fullFilePath ) );
        File.Copy( sourcePath, fullFilePath );
      }

      Console.WriteLine( "  Store descriptor..." );
      XmlDocument xml = new XmlDocument();
      xml.AppendChild( xml.CreateElement( "Files" ) );
      foreach ( var file in files )
      {
        XmlElement fileNode = xml.DocumentElement.AppendChild( xml.CreateElement( "File" ) ) as XmlElement;
        XmlAttribute sizeAttribute = fileNode.Attributes.Append( xml.CreateAttribute( "Size" ) );
        sizeAttribute.Value = file.Value.ToString();
        fileNode.InnerText = file.Key;
      }
      xml.Save( Path.Combine( dest, "files" ) );
    }

    [STAThread]
    static void Main( params string[] args )
    {
      foreach ( var dirPath in Directory.GetDirectories( args[0] ) )
      {
        string dirName = Path.GetFileName( dirPath );
        int version = 0;
        if ( int.TryParse( dirName, out version ) && Directory.Exists( Path.Combine( dirPath, "IncrementalVcdiff_Source" ) ) )
        {
          if ( version > 10 )
            CopyFolder( Path.GetFullPath( Path.Combine( dirPath, "IncrementalVcdiff_Source" ) ) + Path.DirectorySeparatorChar, Path.GetFullPath( Path.Combine( args[1], version.ToString() ) ) );
        }
      }
    }
  }
}
