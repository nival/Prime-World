using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using System.Xml.Linq;

namespace LocKit.Localization
{
  /// <summary>
  /// Объект, сериализующийся в файл для локализации.
  /// </summary>
  public class LocalizationFile
  {
    public string Filename { get; set; }
    public LocalizationFilePart Body { get; set; }
    public List<LocalizationIfBlock> Ifs { get; set; }

    /// <summary>
    /// Конструктор объекта.
    /// </summary>
    /// <param name="filename">Имя физического файла, которому соответствует объект.</param>
    public LocalizationFile( string filename )
    {
      if ( filename == null )
        throw new ArgumentNullException( "filename" );
      Filename = filename;
    }

    /// <summary>
    /// Сериализация в XML.
    /// </summary>
    public XElement ToXML()
    {
      var result = new XElement( "file", new XAttribute( "name", Filename ) );
      if ( Body != null )
      {
        result.Add( Body.ToXML() );
        if ( Ifs != null )
          result.Add( new XElement( "ifs", Ifs.Select( i => i.ToXML() ) ) );
      }
      return result;
    }

    /// <summary>
    /// Преобразование в строку.
    /// </summary>
    public override string ToString()
    {
      string result = Body.ToString();

      // Замена строчек <if id=".."/> реальными ифами.
      // Хреновина, но как вычленять id из строки без дикого хардкода, пока не придумал.
      var rx = new Regex( String.Format( LocalizationIfBlock.IFPATTERN, @"\d+" ) );
      var rxid = new Regex( String.Format( LocalizationIfBlock.IFIDPATTERN, @"\d+" ) );
      while ( rx.IsMatch( result ) )
      {
        string ifStr = rx.Match( result ).Value;
        string ifIdStr = rxid.Match( ifStr ).Value;
        int ifId = Int32.Parse( ifIdStr.Remove( 0, ifIdStr.IndexOf( '"' ) + 1 ).TrimEnd( '"' ) );

        result = result.Replace( String.Format( LocalizationIfBlock.IFPATTERN, ifId ), Ifs.Find( i => i.Id == ifId ).ToString() );
      }

      // Замена всех переносов строк на \r\n
      result = result.Replace( "\r", String.Empty ).Replace( "\n", Environment.NewLine ).Replace( "&#10;", Environment.NewLine );

      return result;
    }

    /// <summary>
    /// Десериализация объекта из входного XML.
    /// </summary>
    /// <param name="xml">XML объект.</param>
    public static LocalizationFile ParseXML( XElement xml )
    {
      if ( xml.Name != "file" )
        throw new Exception( String.Format( "Wrong xml element '{0}'", xml.Name ) );

      LocalizationFile result;
      try
      {
        result = new LocalizationFile( xml.Attribute( "name" ).Value );
      }
      catch ( NullReferenceException ex )
      {
        throw new Exception( "'File' have no 'name' attribute!", ex );
      }

      result.Body = LocalizationFilePart.ParseXML( xml.Element( "prefix" ), xml.Element( "text" ), xml.Element( "suffix" ) );

      if ( xml.Element( "ifs" ) != null )
      {
        result.Ifs = new List<LocalizationIfBlock>();
        foreach ( var elem in xml.Element( "ifs" ).Elements() )
        {
          result.Ifs.Add( LocalizationIfBlock.ParseXML( elem ) );
        }
      }

      return result;
    }
  }
}