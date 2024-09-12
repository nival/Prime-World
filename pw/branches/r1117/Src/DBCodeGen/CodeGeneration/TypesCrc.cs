using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using DBCodeGen.VisualStudioSupport;
using DBCodeGen.Utils;
using libdb.DB;
using System.Security.Cryptography;

namespace DBCodeGen.CodeGeneration
{
  internal class TypesCrc
  {
    private class HashPattern
    {
      public string SrcAssembly = string.Empty;
      public string HashFileName = string.Empty;
      public string ProjectName = string.Empty;
      public string HashArray = string.Empty;
    }

    private static void CalculateTypeHash( StringBuilder typesCollector, Type type )
    {
      DBVersionAttribute version = TypeUtils.GetAttribute<DBVersionAttribute>( type, false );
      if ( version == null )
        return;

      typesCollector.Append( type.Name );
      typesCollector.Append( version.Version.ToString() );
    }

    private static byte[] CalculateHash( Dictionary<CodeFile, List<Type>> types )
    {
      List<Type> versionedTypes = new List<Type>();
      foreach ( var fileTypes in types.Values )
      {
        foreach ( var type in fileTypes )
        {
          if ( TypeUtils.HasAttribute<DBVersionAttribute>( type, false ) )
            versionedTypes.Add( type );
        }
      }
      versionedTypes.Sort( TypeUtils.Compare );

      StringBuilder typesCollector = new StringBuilder();
      foreach ( var type in versionedTypes )
        CalculateTypeHash( typesCollector, type );

      MD5 md5 = MD5.Create();
      return md5.ComputeHash( Encoding.UTF8.GetBytes( typesCollector.ToString() ) );
    }

    internal static void StoreHash( Dictionary<CodeFile, List<Type>> types, IEnumerable<string> files, string srcAssembly, Solution solution, bool dryRun )
    {
      byte[] hash = CalculateHash( types );

      HashPattern pattern = new HashPattern();
      pattern.SrcAssembly = srcAssembly;

      List<string> hashStr = new List<string>();
      foreach ( byte hashByte in hash )
        hashStr.Add( string.Format( "0x{0:X2}", hashByte ) );
      pattern.HashArray = String.Join( ", ", hashStr.ToArray() );

      foreach ( string file in files )
      {
        if ( string.Compare( Path.GetExtension( file ), ".h", true ) != 0 && string.Compare( Path.GetExtension( file ), ".cs", true ) != 0 )
        {
          pattern.HashFileName = Path.GetFileName( file );
          break;
        }
      }

      foreach ( string file in files )
      {
        if ( string.Compare( Path.GetExtension( file ), ".h", true ) != 0 && string.Compare( Path.GetExtension( file ), ".cs", true ) != 0 )
          StoreBinHash( hash, file );
        else
          StoreCodeHash( file, solution, pattern, dryRun );
      }
    }

    private static void StoreBinHash( byte[] hash, string fileName )
    {
      string fullFileName = Path.GetFullPath( fileName );
      Directory.CreateDirectory( Path.GetDirectoryName( fullFileName ) );
      using ( Stream file = new FileStream( fullFileName, FileMode.Create, FileAccess.Write ) )
      {
        file.Write( hash, 0, hash.Length );
        file.Flush();
        file.Close();
      }
    }

    private static void StoreCodeHash( string fileName, Solution solution, HashPattern pattern, bool dryRun )
    {
      Project project = null;
      if ( solution != null && !solution.IsEmpty )
      {
        string fullFilePath = Path.GetDirectoryName( Path.GetFullPath( Path.Combine( solution.SolutionPath, fileName ) ) );
        foreach ( Project proj in solution )
        {
          if ( string.Compare( fullFilePath, proj.ProjectPath, true ) == 0 )
          {
            project = proj;
            break;
          }
        }
      }

      if ( project == null )
        project = new NullProject( "Empty" );

      pattern.ProjectName = project.ProjectName;
      CodeWriter writer = project.CreateFile( Path.GetFileName( fileName ) );
      if ( string.Compare( Path.GetExtension( fileName ), ".h", true ) == 0 )
        writer.WriteLines( 0, PatternFormatter.Format( Patterns.Patterns.HashCheckCpp, pattern ) );
      else
        writer.WriteLines( 0, PatternFormatter.Format( Patterns.Patterns.HashCheckCs, pattern ) );

      writer.Close( dryRun );
    }
  }
}
