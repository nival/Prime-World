using System.Collections.Generic;
using libdb.IO;

namespace EditorLib
{
	public static class NameUtils
	{
		public static string GenerateName( string root, string name, string extension, params string[] suffixes )
		{
			root = FileUtils.FixFolderName( root );
			string paramsString = string.Join(
				"_",
				new List<string>( suffixes ).
					FindAll( suffix => !string.IsNullOrEmpty( suffix ) ).
					ConvertAll( suffix => suffix.Trim( '_' ) ).
					FindAll( suffix => !string.IsNullOrEmpty( suffix ) ).ToArray()
				);

			bool nameEmpty = string.IsNullOrEmpty( name );
			bool extEmpty = string.IsNullOrEmpty( extension );

			if ( string.IsNullOrEmpty( paramsString ) )
			{
				if ( !nameEmpty && !extEmpty )
				{
					return root + name + '.' + extension;
				}
				else if ( !nameEmpty && extEmpty )
				{
					return root + name;
				}
				else if ( nameEmpty && !extEmpty )
				{
					return root + '_' + '.' + extension;
				}
				else
				{
					return root + '_';
				}
			}
			else
			{
				if ( !nameEmpty && !extEmpty )
				{
					return root + name + '_' + paramsString + '.' + extension;
				}
				else if ( !nameEmpty && extEmpty )
				{
					return root + name + '_' + paramsString;
				}
				else if ( nameEmpty && !extEmpty )
				{
					return root + paramsString + '.' + extension;
				}
				else
				{
					return root + paramsString;
				}
			}
		}
	}
}
