using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using libdb.IO;

namespace libdb.DB
{
	public sealed class DBID : IComparable<DBID>, IComparable, IEquatable<DBID>
	{
		private const char dbidPartDivider = ':';
		private const string emptyDbidName = "{empty}";
		private const string dbidExtension = ".xdb";

		private readonly string fileName = string.Empty;
		private readonly string preparedFileName = string.Empty;//имя файла подготовленное для сравнения
		private readonly string id = string.Empty;
		private readonly int hashCode;

		public DBID( string _fileName, Guid _id )
		{
			if (!string.IsNullOrEmpty(_fileName))
				fileName = FileUtils.Combine(FileUtils.PathSeparatorChar.ToString(), FileUtils.FixFileName(_fileName));

			id = (_id == Guid.Empty) ? string.Empty : _id.ToString( "D" ).ToUpper();

			preparedFileName = PrepareFileName();

			// Подсчет хэша dbid таким же образом, как это сделано в libdb
			hashCode = GetHashCode( id.ToLower() ) ^ GetHashCode( preparedFileName );
		}

		public string FileName { get { return fileName; } }
		public string Id { get { return id; } }
		
		public bool IsInlined { get { return !string.IsNullOrEmpty( Id ); } }
		public bool IsEmpty { get { return string.IsNullOrEmpty( FileName ) && !IsInlined; } }

		public string Name { get { return IsInlined ? FileName + dbidPartDivider + Id : IsEmpty ? emptyDbidName : FileName; } }

    /// <summary>
    /// Возвращает имя таком же формате, как это реализовано в DBID.GetFormatted из libdb
    /// </summary>
    public string NameFormatted
    {
      get
      {
        string tmpfilename = FileName.Trim(FileUtils.PathSeparatorChar);
        if (!tmpfilename.EndsWith(".xdb"))
          tmpfilename += ".xdb";
        return IsInlined ? tmpfilename + dbidPartDivider + Id : tmpfilename;
      }
    }


		public override bool Equals( object obj )
		{
			DBID dbid = obj as DBID;
			if ( ReferenceEquals( dbid, null ) )
				return false;

			return Compare( this, dbid ) == 0;
		}

		public bool Equals( DBID _other )
		{
			return Compare( this, _other ) == 0;
		}

    private static int GetHashCode( string s )
    {
      int result = 0;
      foreach (char c in s)
        result = 5 * result + (byte)c;
      return result;
    }

    public override int GetHashCode()
    {
    	return hashCode;
    }

		/// <summary>
		/// Подготавливает fileName к сравнению в GetHashCode и в Compare
		/// </summary>
		private string PrepareFileName()
		{
			if ( string.IsNullOrEmpty( fileName ) )
				return fileName;

			string result = FileUtils.FixFileName( fileName ) + dbidExtension;
			return result.TrimStart( FileUtils.PathSeparatorChar ).ToLower();
		}

		int IComparable.CompareTo(object _obj)
		{
			if (_obj is DBID)
				return Compare(this, (DBID) _obj);

			throw new ArgumentException( "_obj is not a DBID" );
		}

		public int CompareTo(DBID _other)
		{
			return Compare(this, _other);
		}

		public override string ToString()
		{
			return Name;
		}

		public string GetFullFileName()
		{
			if ( IsEmpty )
				return string.Empty;

			return FileName + dbidExtension;
		}

		#region Usefull static properties and functions

		public static string Extension { get { return dbidExtension; } }

		private static DBID empty = new DBID( string.Empty, Guid.Empty );
		public static DBID Empty { get { return empty; } }

		public static int Compare( DBID dbidA, DBID dbidB )
		{
			if ( DBID.IsNullOrEmpty( dbidA ) )
				return DBID.IsNullOrEmpty( dbidB ) ? 0 : -1;
			else if ( DBID.IsNullOrEmpty( dbidB ) )
				return 1;

			int result = string.Compare( dbidA.preparedFileName , dbidB.preparedFileName );
			if ( result != 0 )
				return result;
			else
				return string.Compare( dbidA.Id, dbidB.Id, true );
		}

		public static bool IsNullOrEmpty( DBID dbid )
		{
			return ReferenceEquals( dbid,null ) || dbid.IsEmpty;
		}

		public static bool operator !=( DBID dbidA, DBID dbidB )
		{
			return Compare( dbidA, dbidB ) != 0;
		}

		public static bool operator ==( DBID dbidA, DBID dbidB )
		{
			return Compare( dbidA, dbidB ) == 0;
		}

		#endregion

		#region Form DBDI from name or from filename and inline attribute

		private static string FixFileName( string fileName )
		{
			if ( string.IsNullOrEmpty( fileName ) )
				return string.Empty;

			string result = FileUtils.FixFileName( fileName );
			if ( !FileUtils.IsPathSeparator( result[0] ) )
				result = FileUtils.PathSeparatorChar + result;

			if ( result.EndsWith( Extension, StringComparison.InvariantCultureIgnoreCase ) )
				return result.Substring( 0, result.Length - Extension.Length );

			return result;
		}

		public static DBID FromString( string dbid )
		{
			if ( string.IsNullOrEmpty( dbid ) || dbid == emptyDbidName )
				return DBID.Empty;

			int divPos = dbid.IndexOf( ":" );
			if ( divPos < 0 )
				return new DBID( FixFileName( dbid ), Guid.Empty );
			else
			{
				Guid id = Guid.Empty;
				try
				{
					id = new Guid( dbid.Substring( divPos + 1 ) );
				}
				catch
				{
				}
				return new DBID( FixFileName( dbid.Substring( 0, divPos ) ), id );
			}
		}

		public static DBID FromFileName( string fileName, bool inlined )
		{
			if ( string.IsNullOrEmpty( fileName ) )
				return DBID.Empty;

			return new DBID( FixFileName( fileName ), inlined ? Guid.NewGuid() : Guid.Empty );
		}

		public static DBID FromFileName( string fileName, Guid guid )
		{
			if ( string.IsNullOrEmpty( fileName ) )
				return DBID.Empty;

			return new DBID( FixFileName( fileName ), guid );
		}

		public static DBID FromDBID( DBID dbid, bool inlined )
		{
			if ( DBID.IsNullOrEmpty( dbid ) )
				return DBID.Empty;

			if ( !dbid.IsInlined && !inlined )
				return dbid;

			return FromFileName( dbid.FileName, inlined );
		}

		#endregion

		#region Generate unique DBID using pattern, path, attributes and so on

		private static Regex validNameRegex = new Regex( @"\G[_A-Za-z][-_A-Za-z0-9]*\Z" );

		public static bool TryCreateDBID( string path, string name, Type type, out DBID result )
		{
			result = DBID.Empty;
			if ( !validNameRegex.IsMatch( name ) )
				return false;

			string fileNameSuffix = string.Empty;
			UseTypeNameAttribute useTypeName = type == null ? null : TypeUtils.GetAttribute<UseTypeNameAttribute>( type, false );
			if ( useTypeName != null )
			{
				if ( string.IsNullOrEmpty( useTypeName.alias ) )
					fileNameSuffix = '.' + type.Name;
				else
					fileNameSuffix = '.' + useTypeName.alias;
			}

			result = new DBID( FileUtils.Combine( path, name + fileNameSuffix ), Guid.Empty );
			return !DataBase.IsExists( result );
		}

		public static DBID GenerateUnique( string path, string name, Type type )
		{
			string fileNameSuffix = string.Empty;
			UseTypeNameAttribute useTypeName = TypeUtils.GetAttribute<UseTypeNameAttribute>( type, false );
			if ( useTypeName != null )
			{
				if ( string.IsNullOrEmpty( useTypeName.alias ) )
					fileNameSuffix = '.' + type.Name;
				else
					fileNameSuffix = '.' + useTypeName.alias;
			}

			string resultName = NameUtils.GenerateUniqueName( path, name, fileNameSuffix, dbidToCheck => DataBase.IsExists( DBID.FromFileName( dbidToCheck, false ) ) );
			return DBID.FromFileName( resultName, false );
		}

		public static DBID GenerateUnique( DBID parent, string name, Type type )
		{
			string parentPath = FileUtils.GetFolderName( parent.FileName );
			string parentName = FileUtils.GetFileName( parent.FileName );

			int dotPos = parentName.LastIndexOf( '.' );
			if ( dotPos >= 0 )
				parentName = parentName.Substring( 0, dotPos );

			string combinedName = string.IsNullOrEmpty( parentName ) || string.IsNullOrEmpty( name ) ? parentName + name : parentName + '_' + name;

      return GenerateUnique( parentPath, combinedName, type );
		}

		#endregion

    public delegate bool ProcessBacklinkDelegate( DBID dbid );
    public void ProcessBacklinks( ProcessBacklinkDelegate doSomething )
    {
      if ( IsEmpty || doSomething == null )
        return;

      Dictionary<DBID, bool> allBacklinks = new Dictionary<DBID, bool>();
      allBacklinks[this] = true;
      List<DBID> backlinks = new List<DBID>();
      backlinks.Add( this );
      for ( int i = 0; i < backlinks.Count; ++i )
      {
        Dictionary<DBID, int> links = DataBase.Get<DBResource>( backlinks[i] ).GetBackLinks();
        foreach ( var item in links )
        {
          if ( !doSomething( item.Key ) )
            return;

          if ( !allBacklinks.ContainsKey( item.Key ) )
          {
            allBacklinks[item.Key] = true;
            backlinks.Add( item.Key );
          }
        }
      }
    }
	}
}
