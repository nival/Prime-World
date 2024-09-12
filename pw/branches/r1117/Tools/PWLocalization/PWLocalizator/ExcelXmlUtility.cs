using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;

namespace PWLocalizator
{
	public static class ExcelXmlUtility
	{
		private static bool IsNumber( string str )
		{
			if ( str == null )
				return false;

			bool dotFound = false;
			foreach ( char c in str.ToCharArray() )
			{
				if ( c == '.' )
				{
					if ( dotFound )
						return false;
					dotFound = true;
				}
				else if ( c < '0' || c > '9' )
					return false;
			}
			return true;
		}

		public static Table[] ReadFile( string fileName )
		{
			List<Table> tables = new List<Table>();
			XmlDocument xmlDoc = new XmlDocument();
			using ( FileStream streamFile = new FileStream( fileName, System.IO.FileMode.Open, System.IO.FileAccess.Read, System.IO.FileShare.ReadWrite ) )
			{
				xmlDoc.Load( streamFile );
				streamFile.Close();
			}
			XmlNode xmlWorkbook = xmlDoc["Workbook"];
			for ( XmlNode xmlNode = xmlWorkbook.FirstChild; xmlNode != null; xmlNode = xmlNode.NextSibling )
			{
				if ( xmlNode.Name == "Worksheet" )
				{
					XmlNode xmlTable = xmlNode["Table"];
					if ( xmlTable != null )
					{
						int nColumns = Convert.ToInt32( xmlTable.Attributes["ss:ExpandedColumnCount"].Value );
						int nRows = Convert.ToInt32( xmlTable.Attributes["ss:ExpandedRowCount"].Value );
						Table table = new Table( xmlNode.Attributes["ss:Name"].Value, nColumns, nRows );
						int nRow = 0;
						for ( XmlNode xmlRow = xmlTable.FirstChild; xmlRow != null; xmlRow = xmlRow.NextSibling )
						{
							if ( xmlRow.Name == "Row" )
							{
								int nCell = 0;
								for ( XmlNode xmlCell = xmlRow.FirstChild; xmlCell != null; xmlCell = xmlCell.NextSibling )
								{
									if ( xmlCell.Name == "Cell" )
									{
										XmlNode xmlIndex = xmlCell.Attributes["ss:Index"];
										if ( xmlIndex != null )
											nCell = Convert.ToInt32( xmlIndex.Value ) - 1;
										XmlNode xmlData = xmlCell["Data"];
										if ( xmlData != null )
										{
											table[nCell, nRow] = xmlData.InnerText;
										}
										nCell++;
									}
								}
								nRow++;
							}
						}
						tables.Add( table );
					}
				}
			}

			return tables.ToArray();
		}

		private static XmlNode CreateWorkbook( XmlDocument xmlDoc, Table table )
		{
			XmlNode xmlNodeWorkSheet = xmlDoc.CreateElement( "Worksheet" );
			xmlNodeWorkSheet.Attributes.Append( xmlDoc.CreateAttribute( "ss", "Name", "urn:schemas-microsoft-com:office:spreadsheet" ) ).Value = table.Name;

			XmlNode xmlTable = xmlDoc.CreateElement( "Table" );
			xmlNodeWorkSheet.AppendChild( xmlTable );
			xmlTable.Attributes.Append( xmlDoc.CreateAttribute( "ss", "ExpandedColumnCount", "urn:schemas-microsoft-com:office:spreadsheet" ) ).Value = table.Columns.ToString();
			xmlTable.Attributes.Append( xmlDoc.CreateAttribute( "ss", "ExpandedRowCount", "urn:schemas-microsoft-com:office:spreadsheet" ) ).Value = table.Rows.ToString();
			xmlTable.Attributes.Append( xmlDoc.CreateAttribute( "x", "FullColumns", "urn:schemas-microsoft-com:office:excel" ) ).Value = "1";
			xmlTable.Attributes.Append( xmlDoc.CreateAttribute( "x", "FullRows", "urn:schemas-microsoft-com:office:excel" ) ).Value = "1";

			for ( int nRow = 0; nRow < table.Rows; ++nRow )
			{
				XmlNode xmlRow = xmlDoc.CreateElement( "Row" );
				xmlTable.AppendChild( xmlRow );
				for ( int nCol = 0; nCol < table.Columns; ++nCol )
				{
					XmlNode xmlCell = xmlDoc.CreateElement( "Cell" );
					xmlRow.AppendChild( xmlCell );
					if ( table[nCol, nRow] != null && table[nCol, nRow].Length > 0 )
					{
						XmlNode xmlData = xmlDoc.CreateElement( "Data" );
						xmlCell.AppendChild( xmlData );
						xmlData.Attributes.Append( xmlDoc.CreateAttribute( "ss", "Type", "urn:schemas-microsoft-com:office:spreadsheet" ) ).Value = IsNumber( table[nCol, nRow] ) ? "Number" : "String";
						xmlData.AppendChild( xmlDoc.CreateTextNode( table[nCol, nRow] ) );
					}
				}
			}

			return xmlNodeWorkSheet;
		}

		public static void WriteFile( string fileName, Table[] tables )
		{
			XmlDocument xmlDoc = new XmlDocument();
			xmlDoc.Prefix = "";

			XmlNode xmlNodeWorkbook = xmlDoc.CreateElement( "Workbook" );
			xmlDoc.AppendChild( xmlNodeWorkbook );
			xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns" ) ).Value = "urn:schemas-microsoft-com:office:spreadsheet";
			xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:o" ) ).Value = "urn:schemas-microsoft-com:office:office";
			xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:x" ) ).Value = "urn:schemas-microsoft-com:office:excel";
			xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:ss" ) ).Value = "urn:schemas-microsoft-com:office:spreadsheet";
			xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:html" ) ).Value = "http://www.w3.org/TR/REC-html40";

			foreach ( Table table in tables )
			{
				XmlNode xmlNodeWorksheet = CreateWorkbook( xmlDoc, table );
				xmlNodeWorkbook.AppendChild( xmlNodeWorksheet );
			}

			using ( XmlTextWriter xmlWriter = new XmlTextWriter( new FileStream( fileName, FileMode.Create ), System.Text.Encoding.Unicode ) )
			{
				xmlWriter.Indentation = 2;
				xmlWriter.IndentChar = ' ';
				xmlWriter.Formatting = Formatting.Indented;
				xmlDoc.Save( xmlWriter );
				xmlWriter.Flush();
				xmlWriter.Close();
			}
		}
	}
}
