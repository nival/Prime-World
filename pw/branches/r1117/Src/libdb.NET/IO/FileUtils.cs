using System;
using System.IO;
using libdb.DB;
using System.Text;

namespace libdb.IO
{
	public static class FileUtils
	{
		public static char PathSeparatorChar { get { return '/'; } }
		public static string PathSeparatorString { get { return "/"; } }
		public static char AltPathSeparatorChar { get { return '\\'; } }
		public static readonly char[] pathSeparatorChars = new[] {PathSeparatorChar, AltPathSeparatorChar};
		#region Path and file names utils

		public static bool IsPathSeparator( char c ) { return c == PathSeparatorChar || c == AltPathSeparatorChar; }
		
		public static string FixFileName( string fileName )
		{
			if ( string.IsNullOrEmpty( fileName ) )
				return string.Empty;

			char[] resultFileName = fileName.ToCharArray();
			int shift = 0;
			int length = resultFileName.Length;
			bool lastCharIsSeparator = false;
			for ( int i = 0; i + shift < length; )
			{
				if ( resultFileName[i + shift] == PathSeparatorChar || resultFileName[i + shift] == AltPathSeparatorChar )
				{
					if ( !lastCharIsSeparator )
					{
						lastCharIsSeparator = true;
						resultFileName[i] = PathSeparatorChar;
						++i;
					}
					else
					{
						++shift;
					}
				}
				else
				{
					resultFileName[i] = resultFileName[i+shift];
					++i;
					lastCharIsSeparator = false;
				}
			}

			string result =  new string( resultFileName, 0, length - shift );
			return result;
		}

		public static string FixFolderName( string dirName )
		{
			string result = FixFileName( dirName );
			if ( !string.IsNullOrEmpty( result ) && result[result.Length - 1] != PathSeparatorChar )
				result += PathSeparatorChar;

			return result;
		}

		public static string GetFolderName( string path )
		{
			if ( string.IsNullOrEmpty( path ) )
				return string.Empty;

			string result = FixFileName( path );
			if ( IsPathSeparator( result[result.Length - 1] ) )
				return result;

			int separatorPos = result.LastIndexOf( PathSeparatorChar );
			if ( separatorPos <= 0 )
				return string.Empty;
			else
				return result.Substring( 0, separatorPos );
		}

		/// <summary>
		/// Extract full path to root folder for file or folder
		/// </summary>
		/// <param name="path">Path to object to extract name</param>
		/// <returns></returns>
		public static string GetParentFolderPath( string path )
		{
			if ( string.IsNullOrEmpty( path ) )
				return string.Empty;

			string result = FixFileName( path );

      int lastIndex = result[result.Length - 1] == PathSeparatorChar ? result.Length - 2 : result.Length - 1;
      int separatorPos = result.LastIndexOf( PathSeparatorChar, lastIndex );
			if ( separatorPos < 0 )
				return string.Empty;
			else
				return result.Substring( 0, separatorPos + 1 );
		}

		/// <summary>
		/// Extract name of root folder for file or folder
		/// </summary>
		/// <param name="path">Path to object to extract name</param>
		/// <returns></returns>
		public static string GetParentFolderName( string path )
		{
			if ( string.IsNullOrEmpty( path ) )
				return string.Empty;

			string tmp = path;
			int lastSep = tmp.LastIndexOf( PathSeparatorChar );
			if ( lastSep < 0 )
				lastSep = 0;
			tmp = tmp.Substring(0,lastSep);
			int prevSep = tmp.LastIndexOf( PathSeparatorChar );
			if ( prevSep < 0 )
				prevSep = 0;

			return path.Substring(prevSep,lastSep-prevSep);
		}

		public static string GetFileName( string path )
		{
			if ( string.IsNullOrEmpty( path ) )
				return string.Empty;

			string result = FixFileName( path );
			if ( IsPathSeparator( result[result.Length - 1] ) )
				return string.Empty;

			int separatorPos = result.LastIndexOf( PathSeparatorChar );
			if ( separatorPos < 0 )
				return path;
			
			return result.Substring( separatorPos + 1 );
		}

		public static string GetFileNameWithoutExtension( string path )
		{
			string fileName = GetFileName( path );
			if ( string.IsNullOrEmpty( fileName ) )
				return string.Empty;

			int dotPos = fileName.IndexOf( '.' );
			if ( dotPos < 0 )
				return fileName;
			
			return fileName.Substring( 0, dotPos );
		}

		public static string Combine( string path1, string path2 )
		{
			string result = string.Empty;
			if ( string.IsNullOrEmpty( path1 ) && string.IsNullOrEmpty( path2 ) )
				return string.Empty;
			else if ( string.IsNullOrEmpty( path1 ) || (path2.Length > 3 && path2[1] == ':' && IsPathSeparator( path2[2] )) )
				result = path2;
			else if ( string.IsNullOrEmpty( path2 ) )
				result = path1;
			else
				result = path1 + PathSeparatorChar + path2;

			return FixFileName( result );
		}

		/// <summary>
		/// Проверяет пути к файлам или папкам на идентичность. Строки приводятся в унифицированный вид перед сравнением.
		/// Нельзя сравнивать относительный путь с абсолютным - будет false всегда. 
		/// </summary>
		/// <returns>true - paths are identical</returns>
		public static bool ComparePathsInAnyForms( string path1, string path2 )
		{
			return UnifyPathForComparison(path1) ==UnifyPathForComparison(path2);
		}

		public static string UnifyPathForComparison( string path)
		{
			return FixFileName( path ).ToLower().Trim().Trim( pathSeparatorChars );
		}
		
		#endregion

		public static string GenerateUniqueFileName( IFileSystem fileSystem, string path, string fileName, string extension )
		{
			return NameUtils.GenerateUniqueName( path, fileName, extension, checkFileName => fileSystem.GetFileInfo( checkFileName ).IsFileExists );
		}

		public static bool CopyFile( IFileSystem fileSystem, string fromFullPath, string toFullPath )
		{
			if ( string.Compare( FixFileName( fromFullPath ), FixFileName( toFullPath ), true ) == 0 )
				return true;

			using(Stream fileFrom = fileSystem.OpenFile( fromFullPath ))
			{
        if( fileFrom == null )
          return false;

        using(Stream fileTo = fileSystem.CreateFile( toFullPath ))
        {
          if( fileTo == null )
          {
            fileFrom.Close();
            return false;
          }
         
          byte[] buffer = new byte[65536];
          for( int bytesReaden = fileFrom.Read( buffer, 0, buffer.Length ); bytesReaden > 0; bytesReaden = fileFrom.Read( buffer, 0, buffer.Length ) )
            fileTo.Write( buffer, 0, bytesReaden ); 
        }
			}

			return true;
		}

		public static bool RenameFile( IFileSystem fileSystem, string fromFullPath, string toFullPath )
		{
			if ( string.Compare( FixFileName( fromFullPath ), FixFileName( toFullPath ), true ) == 0 )
				return true;

			fileSystem.DeleteFile( toFullPath );

			if ( !CopyFile( fileSystem, fromFullPath, toFullPath ) )
				return false;

			fileSystem.DeleteFile( fromFullPath );

			return true;
		}

		public static bool CopyRealFile( string fromFullPath, IFileSystem fileSystem, string toFullPath )
		{
			Stream fileFrom = new FileStream( fromFullPath, FileMode.Open, FileAccess.Read );
			if ( fileFrom == null )
				return false;

			Stream fileTo = fileSystem.CreateFile( toFullPath );
			if ( fileTo == null )
			{
				fileFrom.Close();
				return false;
			}

			byte[] buffer = new byte[65536];
			for ( int bytesReaden = fileFrom.Read( buffer, 0, buffer.Length ); bytesReaden > 0; bytesReaden = fileFrom.Read( buffer, 0, buffer.Length ) )
				fileTo.Write( buffer, 0, bytesReaden );

			fileFrom.Close();
			fileTo.Close();

			return true;
		}

    public static string CopyFileToTemp(IFileSystem fileSystem, string fileName)
    {
      string resultFileName = Path.Combine(Path.GetTempPath(), Path.GetFileName(fileName));
      
      //... а дальше списать с CopyRealFile
      using(Stream fileTo = new FileStream(resultFileName, FileMode.OpenOrCreate, FileAccess.Write))
      {
        if( fileTo == null )
          return string.Empty;

        using( Stream fileFrom = fileSystem.OpenFile( fileName ) )
        {
          if( fileFrom == null )
          {
            fileTo.Close();
            return string.Empty;
          }

          byte[] buffer = new byte[65536];
          for( int bytesReaden = fileFrom.Read( buffer, 0, buffer.Length ); bytesReaden > 0; bytesReaden = fileFrom.Read( buffer, 0, buffer.Length ) )
            fileTo.Write( buffer, 0, bytesReaden );
        }

        fileTo.Flush();
      }

      return resultFileName;
    }

		public static byte[] ReadFile( IFileSystem fileSystem, string fileName )
		{
		  byte[] result = new byte[0];

			if ( !fileSystem.GetFileInfo( fileName ).IsFileExists )
        return result;

			using(Stream file = fileSystem.OpenFile( fileName ))
			{
        if( file == null )
          return new byte[0];

        using(BinaryReader reader = new BinaryReader( file ))
        {
          result = reader.ReadBytes( (int)file.Length );
        }
			}

			return result;
		}

		public static string GetRelativePath( string absolutePath, string relativeTo )
		{
			string[] absoluteDirectories = FixFileName( absolutePath ).Split( PathSeparatorChar );
			string[] relativeDirectories = FixFileName( relativeTo ).Split( PathSeparatorChar );

			//Get the shortest of the two paths
			int length = Math.Min( absoluteDirectories.Length, relativeDirectories.Length );

			//Use to determine where in the loop we exited
			int lastCommonRoot = 0;
			for ( lastCommonRoot = 0; lastCommonRoot < length; ++lastCommonRoot )
			{
				if ( string.Compare( absoluteDirectories[lastCommonRoot], relativeDirectories[lastCommonRoot], StringComparison.InvariantCultureIgnoreCase ) != 0 )
					break;
			}

			if ( lastCommonRoot == 0 )
				return relativeTo;

			StringBuilder relativePath = new StringBuilder();

			//Add on the ..
			for ( int i = lastCommonRoot; i < absoluteDirectories.Length; ++i )
				relativePath.Append( ".." + PathSeparatorChar );

			//Add on the folders
			for ( int i = lastCommonRoot; i < relativeDirectories.Length - 1; ++i )
				relativePath.Append( relativeDirectories[i] + PathSeparatorChar );

			if ( relativePath.Length == 0 )
				relativePath.Append( "." + PathSeparatorChar );
			relativePath.Append( relativeDirectories[relativeDirectories.Length - 1] );

			return relativePath.ToString();
		}

    public static string GetSrcFileValue( DBFieldInfo srcFileField, DBID ownerDbid, string fileName )
    {
      SrcFileAttribute srcFile = TypeUtils.GetAttribute<SrcFileAttribute>( srcFileField, true );
      if ( srcFile == null || string.IsNullOrEmpty( srcFile.SourceFolder ) )
        return FileUtils.FixFileName( FileUtils.Combine( ownerDbid.FileName, Path.GetFileName( fileName ) ) );
      else
        return FileUtils.FixFileName( FileUtils.Combine( srcFile.SourceFolder, Path.GetFileName( fileName ) ) );
    }
	}
}
