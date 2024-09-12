using System;
using System.Collections.Specialized;
using System.IO;
using System.Text;

namespace PWLocalizator
{
	public static class TextRefProcessor
	{
		public static NameValueCollection CollectTextRefs( string srcFolder)
		{
			var result =  new NameValueCollection();

			string[] files = Directory.GetFiles( srcFolder, "*.txt", SearchOption.AllDirectories );

			foreach (string file in files)
			{
				string refFile = file.Replace( srcFolder, "" ).TrimStart('/', '\\');
				string refText = File.ReadAllText( file );		

				result.Add( refFile, refText );
			}

			return result;
		}

		public static void UpdateTextRefs(string srcFolder, NameValueCollection data, bool updateEmpty)
		{
			foreach (string key in data.Keys)
			{
				string refFile = Path.Combine(srcFolder, key);
				string refText = data[key];

				if(!updateEmpty && string.IsNullOrEmpty(refText))
					continue;

				File.WriteAllText( refFile, refText, Encoding.Unicode );
			}
		}

		public static void CreateExcelFile( string file, NameValueCollection data )
		{
			Table table = new Table("TextRefs", 3, data.Count);

			for ( int i = 0; i < data.Keys.Count; ++i )
			{
				string refFile = data.Keys[i];
				string refText = data[refFile];

				table[0, i] = refFile;
				table[1, i] = refText;
			}

			ExcelXmlUtility.WriteFile(file, new[]{table});
		}

		public static NameValueCollection ReadExcelFile(string file)
		{
			var result = new NameValueCollection();

			Table[] tables = ExcelXmlUtility.ReadFile(file);

			if ( tables.Length == 0 )
				return result;

			Table table = tables[0];

			if(table.Columns < 3)
			  throw new FormatException( string.Format( "Incorrect File format: '{0}'. Expected 3 columns but only {1} found", file, table.Columns ) );

			if(table.Rows == 0)
				return result;

			for ( int i = 0; i < table.Rows; ++i )
			{
				string refFile = table[0, i];
				string refText = table[2, i];

				result.Add(refFile, refText);
			}

			return result;
		}
	}
}
