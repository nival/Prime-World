using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;

namespace LocKit.ExcelUtils
{
	static class ExcelXmlUtility
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
						Table table = new Table( xmlNode.Attributes["ss:Name"].Value, nColumns, nRows, null );
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
                    XmlNode xmlData = xmlCell["Data"] ?? xmlCell["ss:Data"];
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
		  xmlTable.Attributes.Append(xmlDoc.CreateAttribute("ss", "ExpandedRowCount", "urn:schemas-microsoft-com:office:spreadsheet"))
        .Value = (table.UseHeader ? table.Rows + 1 : table.Rows).ToString();
			xmlTable.Attributes.Append( xmlDoc.CreateAttribute( "x", "FullColumns", "urn:schemas-microsoft-com:office:excel" ) ).Value = "1";
			xmlTable.Attributes.Append( xmlDoc.CreateAttribute( "x", "FullRows", "urn:schemas-microsoft-com:office:excel" ) ).Value = "1";
      xmlTable.Attributes.Append(xmlDoc.CreateAttribute("ss:StyleID", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "sCell";

		  for (int i = 0; i < table.Columns; i++)
		  {
		    XmlNode xmlColumn = xmlDoc.CreateElement("Column");
		    xmlColumn.Attributes.Append(xmlDoc.CreateAttribute("ss:Width", "urn:schemas-microsoft-com:office:spreadsheet"))
		      .Value = (i == 0 ? 200 : 400).ToString();
		    xmlTable.AppendChild(xmlColumn);
		  }

      if (table.UseHeader)
      {
        XmlNode header = xmlDoc.CreateElement("Row");
        header.Attributes.Append(xmlDoc.CreateAttribute("ss:StyleID", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "sHeader";
        xmlTable.AppendChild(header);
        for (int i = 0; i < table.Columns; i++)
        {
          XmlNode headerCell = xmlDoc.CreateElement("Cell");
          XmlNode headerData = xmlDoc.CreateElement("Data");
          headerCell.AppendChild(headerData);
          headerData.Attributes.Append(xmlDoc.CreateAttribute("ss:Type", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "String";
          headerData.AppendChild(xmlDoc.CreateTextNode(table.GetHeader(i)));
          header.AppendChild(headerCell);
        }
      }

			for ( int nRow = 0; nRow < table.Rows; ++nRow )
			{
				XmlNode xmlRow = xmlDoc.CreateElement( "Row" );
        xmlRow.Attributes.Append(xmlDoc.CreateAttribute("ss:StyleID", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "sCell";
				xmlTable.AppendChild( xmlRow );
				for ( int nCol = 0; nCol < table.Columns; ++nCol )
				{
					XmlNode xmlCell = xmlDoc.CreateElement( "Cell" );
					xmlRow.AppendChild( xmlCell );
					if ( !String.IsNullOrEmpty(table[nCol, nRow]) )
					{
						XmlNode xmlData = xmlDoc.CreateElement( "Data" );
						xmlCell.AppendChild( xmlData );
						xmlData.Attributes.Append( xmlDoc.CreateAttribute( "ss", "Type", "urn:schemas-microsoft-com:office:spreadsheet" ) ).Value = IsNumber( table[nCol, nRow] ) ? "Number" : "String";
            if (table[nCol, nRow].Contains(Environment.NewLine))
              xmlData.AppendChild(xmlDoc.CreateCDataSection(table[nCol, nRow]));
            else
              xmlData.AppendChild( xmlDoc.CreateTextNode( table[nCol, nRow] ) );
					}
				}
			}

			return xmlNodeWorkSheet;
		}

    private static XmlNode CreateStyles(XmlDocument xmlDoc)
    {
      XmlNode xmlStyles = xmlDoc.CreateElement("Styles");

      XmlNode xmlStyle, innerStyle;

      xmlStyle = xmlDoc.CreateElement("Style");
      xmlStyle.Attributes.Append(xmlDoc.CreateAttribute("ss:ID", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "sCell";
      innerStyle = xmlDoc.CreateElement("Alignment");
      innerStyle.Attributes.Append(xmlDoc.CreateAttribute("ss:Vertical", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "Bottom";
      innerStyle.Attributes.Append(xmlDoc.CreateAttribute("ss:WrapText", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "1";
      xmlStyle.AppendChild(innerStyle);
      xmlStyles.AppendChild(xmlStyle);

      xmlStyle = xmlDoc.CreateElement("Style");
      xmlStyle.Attributes.Append(xmlDoc.CreateAttribute("ss:ID", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "sHeader";
      innerStyle = xmlDoc.CreateElement("Font");
      innerStyle.Attributes.Append(xmlDoc.CreateAttribute("ss:Color", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "#000000";
      innerStyle.Attributes.Append(xmlDoc.CreateAttribute("ss:Bold", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "1";
      xmlStyle.AppendChild(innerStyle);
      innerStyle = xmlDoc.CreateElement("Interior");
      innerStyle.Attributes.Append(xmlDoc.CreateAttribute("ss:Color", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "#FFFF99";
      innerStyle.Attributes.Append(xmlDoc.CreateAttribute("ss:Pattern", "urn:schemas-microsoft-com:office:spreadsheet")).Value = "Solid";
      xmlStyle.AppendChild(innerStyle);
      xmlStyles.AppendChild(xmlStyle);

      return xmlStyles;
    }

	  public static void WriteFile( string fileName, Table[] tables )
		{
			XmlDocument xmlDoc = new XmlDocument();
			xmlDoc.Prefix = String.Empty;

			XmlNode xmlNodeWorkbook = xmlDoc.CreateElement( "Workbook" );
			xmlDoc.AppendChild( xmlNodeWorkbook );
			xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns" ) ).Value = "urn:schemas-microsoft-com:office:spreadsheet";
			xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:o" ) ).Value = "urn:schemas-microsoft-com:office:office";
			xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:x" ) ).Value = "urn:schemas-microsoft-com:office:excel";
			xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:ss" ) ).Value = "urn:schemas-microsoft-com:office:spreadsheet";
			xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:html" ) ).Value = "http://www.w3.org/TR/REC-html40";

	    XmlNode xmlStyles = CreateStyles(xmlDoc);
      if (xmlStyles != null)
        xmlNodeWorkbook.AppendChild(xmlStyles);

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
