using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Web;
using EditorLib.FieldProcessor;
using libdb.Diagnostics;

namespace EditorLib.Utils
{
	internal static class TextHelpers
	{
		public static List<List<string>> ParseHtmlTable( string text )
		{
			var result = new List<List<string>>();

			if ( string.IsNullOrEmpty( text ) )
				return result;

			var lastRow = new List<string>();

			MatchCollection matches = Regex.Matches( text, @"<tr[^>]*>(.*?)</tr>", RegexOptions.IgnoreCase | RegexOptions.Singleline );

			foreach ( Match m in matches )
			{
				MatchCollection cells = Regex.Matches( m.Groups[1].Value, @"<td[^>]*>(.*?)</td>", RegexOptions.IgnoreCase | RegexOptions.Singleline );

				foreach ( Match cell in cells )
				{
					string cellText = cell.Groups[1].Value.Replace("\r", "").Replace("\n", "");
					//т.к. у ячеек задан стиль white-space:normal; заменяем все неодинартыне пробелы одинарными
					cellText = Regex.Replace( cellText, @"(?<!'mso-spacerun:yes'>)\s{2,}(?!</span>|style)", " " );
					cellText = Regex.Replace( cellText, @"<\s*br[^>]*>", "\r\n" );//заменяем <br> на перенос строки
					cellText = Regex.Replace(cellText, "<[^>]*>", "");//удаляем все оставшиеся теги
					cellText = HttpUtility.HtmlDecode( cellText );

					lastRow.Add( cellText );
				}

				result.Add( lastRow );
				lastRow = new List<string>();
			}

			return result;
		}

		public static string CreatHtmlTable (List<List<string>> table)
		{
			var result = new StringBuilder();

			result.Append("<table>");

			foreach (List<string> row in table)
			{
				result.Append( "<tr>" );
				
				foreach (var cell in row)
				{
					string text = HttpUtility.HtmlEncode(cell).Replace("\r\n", "<br/>");
					text = Regex.Replace(text, @"(\s{2,})", "<span style='mso-spacerun:yes'>$1</span>");
					result.AppendFormat( "<td>{0}</td>", text );
				}

				result.Append( "</tr>" );
			}

			result.Append( "</table>" );

			return result.ToString();
		}

		public static string CreateTextTable( List<List<string>> table )
		{
			var sb = new StringBuilder();

			foreach ( List<string> row in table )
			{
				for ( int i = 0; i < row.Count; i++ )
				{
					string text = row[i].Replace( "\"", "\"\"" );
					sb.AppendFormat( "\"{0}\"{1}", text, ( i == row.Count - 1 ) ? Environment.NewLine : "\t" );
				}
			}

			return sb.ToString();
		}

		public static string ConvertValueToString( object _value, IEditorWinApplication _application )
		{
			if ( _value == null )
				return string.Empty;

			IStringConvertor sc = _application.Application.Extensions.CreateStringConverter( _value.GetType(), _application );

			if ( sc != null )
			{
				ITypeDescriptorContext context = new FakeDescriptorContext( _value );
				return sc.ConvertToString( context, Thread.CurrentThread.CurrentCulture, _value );
			}

			return Convert.ToString( _value );
		}
		
		public static bool CanConvertFromString( Type _type, IEditorWinApplication _application )
		{
			IStringConvertor sc = _application.Application.Extensions.CreateStringConverter( _type, _application );

			if ( sc != null )
				return true;
			
			TypeConverter converter = TypeDescriptor.GetConverter( _type );
			
			if ( converter.CanConvertFrom( typeof( string ) ) )
				return true;

			return false;
		}

		public static bool TryGetValueFromString( string _str, Type _type, object _instance, IEditorWinApplication _application, out object _result )
		{
			_result = null;

			if ( !CanConvertFromString( _type, _application ) )
				return false;

			try
			{
				IStringConvertor sc = _application.Application.Extensions.CreateStringConverter( _type, _application );

				if ( sc != null )
				{
					ITypeDescriptorContext context = new FakeDescriptorContext( _instance );
					_result = sc.ConvertFromString( context, Thread.CurrentThread.CurrentCulture, _str );
					return true;
				}


				TypeConverter converter = TypeDescriptor.GetConverter( _type );

				if ( converter != null && converter.IsValid( _str ) && converter.CanConvertFrom( typeof( string ) ) )
				{
					_result = converter.ConvertFrom( _str );
					return true;
				}

				if ( _type.IsEnum )
				{
					_result = Enum.Parse( _type, _str, true );
					return true;
				}
			}
			catch ( Exception err )
			{
				Log.TraceWarning( err.Message );
				return false;
			}

			return false;
		}
	}
}
