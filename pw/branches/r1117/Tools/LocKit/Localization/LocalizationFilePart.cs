using System;
using System.Xml.Linq;

namespace LocKit.Localization
{
  /// <summary>
  /// Класс, содержащий разбиение исходного текста на три части: prefix, text, suffix.
  /// </summary>
  public class LocalizationFilePart
  {
    public string Prefix { get; set; }
    public string Text { get; set; }
    public string Suffix { get; set; }

    /// <summary>
    /// Дописывает строку в которой содержится тег.
    /// </summary>
    public void AppendTag( string str )
    {
      if ( String.IsNullOrEmpty( Text ) && String.IsNullOrEmpty( Suffix ) )
      {
        Prefix += str;
      }
      else
      {
        Suffix += str;
      }
    }

    /// <summary>
    /// Сериализация в XML.
    /// </summary>
    public XElement[] ToXML()
    {
      return new[]
               {
                 new XElement("prefix", Prefix),
                 new XElement("text", Text),
                 new XElement("suffix", Suffix)
               };
    }

    /// <summary>
    /// Преобразование в строку.
    /// </summary>
    public override string ToString()
    {
      return Prefix + Text + Suffix;
    }

    /// <summary>
    /// Десериализация объекта из входного XML.
    /// </summary>
    public static LocalizationFilePart ParseXML( XElement prefix, XElement text, XElement suffix )
    {
      if ( prefix == null ) throw new ArgumentNullException( "prefix" );

      return new LocalizationFilePart
      {
        Prefix = prefix.Value,
        Text = text != null ? text.Value : null,
        Suffix = suffix != null ? suffix.Value : null
      };
    }
  }
}