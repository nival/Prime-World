using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text.RegularExpressions;
using libdb.DB;

namespace DBCodeGen.Utils
{
	public class PatternFormatter
	{
		private string[] pattern = null;
		private string[] formattedPattern = null;

		protected PatternFormatter( string _pattern )
		{
			pattern = _pattern.Split( new string[] { "\r\n" }, StringSplitOptions.None );
		}

		private delegate object GetValueOperator<TField>( TField field ) where TField : MemberInfo;
		private delegate Type GetTypeOperator<TField>( TField field ) where TField : MemberInfo;
		private static int CollectVariables<TField>( IEnumerable<TField> fields, Dictionary<string, string[]> vars, GetValueOperator<TField> getValue, GetTypeOperator<TField> getType ) where TField : MemberInfo
		{
			int result = 0;
			foreach ( TField field in fields )
			{
				object value = null;
				try { value = getValue( field ); } catch { }
				if ( value == null )
					continue;

				string name = field.Name.ToLower();
				if ( vars.ContainsKey( name ) )
					continue;

				Type type = getType( field );
				if ( TypeUtils.IsSubclassOf( type, typeof( IEnumerable<string> ) ) )
					vars.Add( name, new List<string>( value as IEnumerable<string> ).ToArray() );
				else
					vars.Add( name, new string[] { value.ToString() } );

				++result;
			}

			return result;
		}

		private static IEnumerable<string> FormatLine( string line, Dictionary<string, string[]> vars )
		{
			MatchCollection varsMatches = Regex.Matches( line, @"\$\(([A-Za-z_][A-Za-z0-9_]*)\)" );
			if ( varsMatches == null || varsMatches.Count == 0 )
				return new string[]{ line };

			// replace single strings
			string multiVar = string.Empty;
			string[] multiVarValue = null;
			Dictionary<string, string> replaces = new Dictionary<string, string>();
			foreach ( Match match in varsMatches )
			{
				string[] value = null;
				if ( match.Groups.Count != 2 || replaces.ContainsKey( match.Groups[0].Value ) || !vars.TryGetValue( match.Groups[1].Value.ToLower(), out value ) )
					continue;

				if ( value == null || value.Length == 0 )
				{
					multiVar = match.Groups[0].Value;
					multiVarValue = null;
					//replaces.Add( match.Groups[0].Value, string.Empty );
				}
				else if ( value.Length == 1 )
					replaces.Add( match.Groups[0].Value, value[0] );
				else if ( string.IsNullOrEmpty( multiVar ) || multiVarValue == null )
				{
					multiVar = match.Groups[0].Value;
					multiVarValue = value;
				}
			}

			string resultLine = line;
			foreach ( KeyValuePair<string, string> replace in replaces )
				resultLine = resultLine.Replace( replace.Key, replace.Value );

			if ( string.IsNullOrEmpty( multiVar ) /*|| multiVarValue == null*/ )
				return new string[]{ resultLine };

			// replace multi string
			List<string> resultList = new List<string>();
			if ( multiVarValue != null )
			{
				foreach ( string value in multiVarValue )
					resultList.Add( resultLine.Replace( multiVar, value ) );
				//resultList.Add( string.Empty );
			}


			return resultList;
		}

		protected void Update()
		{
			Dictionary<string, string[]> vars = new Dictionary<string, string[]>();

			CollectVariables( GetType().GetFields( BindingFlags.FlattenHierarchy | BindingFlags.Instance | BindingFlags.Public ), vars,
				field => field.GetValue( this ), field => field.FieldType );

			CollectVariables( GetType().GetProperties( BindingFlags.FlattenHierarchy | BindingFlags.Instance | BindingFlags.Public ), vars,
				property => property.GetValue( this, null ), property => property.PropertyType );

			List<string> result = new List<string>();
			foreach ( string line in pattern )
				result.AddRange( FormatLine( line, vars ) );

			formattedPattern = result.ToArray();
		}

		public string[] FormattedPattern { get { return formattedPattern; } }

		public static string[] Format( string pattern, params object[] args )
		{
			Dictionary<string, string[]> vars = new Dictionary<string, string[]>();
			foreach ( object arg in args )
			{
				CollectVariables( arg.GetType().GetFields( BindingFlags.FlattenHierarchy | BindingFlags.Instance | BindingFlags.Public ), vars,
					field => field.GetValue( arg ), field => field.FieldType );

				CollectVariables( arg.GetType().GetProperties( BindingFlags.FlattenHierarchy | BindingFlags.Instance | BindingFlags.Public ), vars,
					property => property.GetValue( arg, null ), property => property.PropertyType );
			}

			List<string> result = new List<string>();
			foreach ( string line in pattern.Split( new string[] { "\r\n" }, StringSplitOptions.None ) )
				result.AddRange( FormatLine( line, vars ) );

			return result.ToArray();
		}
	}
}
