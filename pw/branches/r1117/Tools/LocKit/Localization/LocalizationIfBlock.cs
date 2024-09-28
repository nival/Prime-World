using System;
using System.Xml.Linq;

namespace LocKit.Localization
{
  /// <summary>
  /// Блок &lt;if&gt; файла локализации.
  /// </summary>
  public class LocalizationIfBlock
  {
    /// <summary>
    /// Шаблон текстовой подстановки if в исходный текст.
    /// </summary>
    internal const string IFPATTERN = "<if id=\"{0}\"/>";
    /// <summary>
    /// Шаблон как правильно выделить id из IFPATTERN.
    /// </summary>
    internal const string IFIDPATTERN = "id=\"{0}\"";

    public int Id { get; set; }
    public LocalizationFilePart ThenPart { get; set; }
    public LocalizationFilePart ElsePart { get; set; }

    /// <summary>
    /// Конструктор объекта.
    /// </summary>
    /// <param name="id">Уникальный идентификатор в пределах LocalizationFile.</param>
    public LocalizationIfBlock( int id )
    {
      Id = id;
    }

    /// <summary>
    /// Сериализация в XML.
    /// </summary>
    public XElement ToXML()
    {
      var result = new XElement( "if", new XAttribute( "id", Id ), new XElement( "then", ThenPart.ToXML() ) );
      if ( ElsePart != null )
        result.Add( new XElement( "else", ElsePart.ToXML() ) );
      return result;
    }

    /// <summary>
    /// Преобразование в строку.
    /// </summary>
    public override string ToString()
    {
      return ThenPart.ToString() + ElsePart ?? String.Empty;
    }

    /// <summary>
    /// Десериализация объекта из входного XML.
    /// </summary>
    public static LocalizationIfBlock ParseXML( XElement xml )
    {
      if ( xml.Name != "if" )
        throw new Exception( String.Format( "Wrong xml element '{0}'", xml.Name ) );

      LocalizationIfBlock result;
      try
      {
        result = new LocalizationIfBlock( Int32.Parse( xml.Attribute( "id" ).Value ) );
      }
      catch ( NullReferenceException ex )
      {
        throw new Exception( "'if' have no 'id' attribute.\nxml = " + xml.Value, ex );
      }

      var ifthen = xml.Element( "then" );
      if ( ifthen != null )
      {
        result.ThenPart = LocalizationFilePart.ParseXML( ifthen.Element( "prefix" ), ifthen.Element( "text" ), ifthen.Element( "suffix" ) );
      }

      var ifelse = xml.Element( "else" );
      if ( ifelse != null )
      {
        result.ElsePart = LocalizationFilePart.ParseXML( ifelse.Element( "prefix" ), ifelse.Element( "text" ), ifelse.Element( "suffix" ) );
      }

      return result;
    }
  }
}