using System;
using System.Collections.Generic;
using System.Text;
using libdb.IO;

namespace libdb.DB
{
	public static class NameUtils
	{
		public delegate bool IsUniqueName( string name );

		/// <summary>
		/// Generate unique name in format &lt;root&gt;/&lt;name&gt;[[_]&lt;index&gt;]&lt;suffix&gt;.
		/// If &lt;name&gt; is empty it will be replaces with '_'.
		/// '_' will be added before &lt;index&gt; if &lt;name&gt; doesn't end with '_'
		/// </summary>
		public static string GenerateUniqueName( string root, string name, string suffix, IsUniqueName isUniqueName )
		{
			int index = 0;
			string prefix = string.Empty;
			string prefixWithDiv = string.Empty;

			if ( string.IsNullOrEmpty( name ) )
			{
				prefix = "_";
				prefixWithDiv = "_";
			}
			else
			{
				int newIndex = 0;
				int lastDivPos = name.LastIndexOf( '_' );
				if ( lastDivPos > 0 && lastDivPos < name.Length - 1 && int.TryParse( name.Substring( lastDivPos + 1 ), out newIndex ) )
				{
					prefix = name.Substring( 0, lastDivPos );
					prefixWithDiv = prefix + "_";
				}
				else
				{
					prefix = name;
					prefixWithDiv = lastDivPos == name.Length - 1 ? prefix : prefix + "_";
				}
			}

			string result = index == 0 ? FileUtils.Combine( root, prefix + suffix ) : FileUtils.Combine( root, prefixWithDiv + index.ToString() + suffix );
			while ( isUniqueName( result ) )
			{
				++index;
				result = FileUtils.Combine( root, prefixWithDiv + index.ToString() + suffix );
			}

			return result;
		}

		public static string ExtractNameOnly( string fullName )
		{
			if ( string.IsNullOrEmpty( fullName ) )
				return string.Empty;

			int lastSlashPos = fullName.Length;

			return string.Empty;
		}
	}
}
