using System.Collections.Generic;
using System.Text.RegularExpressions;
using Flash;
using UnityEngine;

namespace FlashView.Utils.FormatParser
{
  class FormatConverter
  {
    private readonly Dictionary<string, Style> _predefinedStyles;
    private readonly Dictionary<string, Texture2D> _predefinedImages;

    public FormatConverter( Dictionary<string, Style> predefinedStyles, Dictionary<string, Texture2D> predefinedImages )
    {
      _predefinedStyles = predefinedStyles ?? new Dictionary<string, Style>();
      _predefinedImages = predefinedImages ?? new Dictionary<string, Texture2D>();
    }

    public IEnumerable<FormatEntry> GetFormatingItems( Entry root, Style baseStyle )
    {
      FormatEntry formatEntry = GetFormatEntry( root, baseStyle );

      if ( formatEntry.Data != null && !formatEntry.Data.Equals( string.Empty ) )
        yield return formatEntry;

      foreach ( Entry entry in root.Children )
      {
        foreach ( FormatEntry item in GetFormatingItems( entry, formatEntry.Style ) )
        {
          yield return item;
        }
      }
    }

    //может возвращать FormatEntry с пустым текстом, это нужно чтобы передать baseStyle в рекурсии
    private FormatEntry GetFormatEntry( Entry entry, Style baseStyle )
    {
      if ( entry.EntryType == EntryType.Text )
        return new FormatEntry( baseStyle, entry.Text );


      //паттерн разбора аттрибутов тэга
      const string pattern = @"\s*(?<tag>[^: ]+)\s*(?:\:(?<ext>[^\s>]+))?\s*(?<attr>[^>]*)?";

      if ( !string.IsNullOrEmpty( entry.Text ) )
      {
        Match match = Regex.Match( entry.Text, pattern );

        if ( match.Success )
        {
          string tag = match.Groups["tag"].Value;
          string attr = match.Groups["attr"].Value;
          string ext = match.Groups["ext"].Value;

          string text;
          Texture2D texture;
          Style style = ParseStyle( baseStyle, tag, attr, ext, entry.NewLineNeeded, out text, out texture );

          if ( texture != null )
          {
            //если в текущей строке только одна картинка, то LineSpacing должен быть 0, т.е. он будет вычисляться по высоте картинки
            if ( entry.Parent != null && entry.Parent.Children.Count == 1 )
              style.LineSpacing = 0;

            return new FormatEntry( style, texture );
          }

          return new FormatEntry( style, text );
        }
      }

      //игнорируем все нераспознанные тэги
      if ( entry.EntryType != EntryType.Root )
        NivalCLI.CLI.Warning( "FormatConverter: Invalid tag detected '" + entry.Text + "'" );

      return new FormatEntry( baseStyle, string.Empty );
    }

    private Style ParseStyle( Style baseStyle, string tag, string attributes, string ext, bool newLineNeeded, out string text, out Texture2D texture )
    {
      Style style;

      text = string.Empty;
      texture = null;

      int number = 0;
      int.TryParse( ext, out number );

      if ( baseStyle != null )
        style = new Style( baseStyle );
      else
        style = Style.GenerateDefaultStyle();

      switch ( tag )
      {
      case "style":
        if ( !string.IsNullOrEmpty( ext ) )
        {
          style = GetPredefinedStyle( ext, baseStyle );
        }
        break;
      case "right":
        if ( newLineNeeded )
          text = "\n";
        style.Align = UnityEngine.TextAlignment.Right;
        break;
      case "left":
        if ( newLineNeeded )
          text = "\n";
        style.Align = UnityEngine.TextAlignment.Left;
        break;
      case "center":
        if ( newLineNeeded )
          text = "\n";
        style.Align = UnityEngine.TextAlignment.Center;
        break;
      case "f_right":
        if ( newLineNeeded )
          text = "\n";
        style.Align = UnityEngine.TextAlignment.Right;
        style.LineSpacing = 0;
        break;
      case "br":
        text = "\n";

        if ( number != 0 )
        {
          style.LineSpacing = number;
        }
        break;
      case "space":
        if ( !string.IsNullOrEmpty( attributes ) && attributes.Contains( "pixels" ) )
        {
          //расчитываем размер пробела в % от размера шрифта, получается что пробел у нас по размеру соответствует number px
          style.WordSpacing = ( number * 100 ) / style.FontSize;
          text = " ";
        }
        else
        {
          string spaces = string.Empty.PadLeft( number != 0 ? number : 1, ' ' );
          text = spaces;
        }

        break;
      case "image":
        texture = GetPredefinedImage( ext );
        if ( baseStyle.DisableImageScaling && texture != null )
          style.FontSize = texture.height;
        text = null;
        break;
      case "atom":
        style.Atom = true;
        break;
      }

      return style;
    }

    private Style GetPredefinedStyle( string styleName, Style baseStyle )
    {
      Style tmp = baseStyle ?? Style.GenerateDefaultStyle();

      if ( !_predefinedStyles.ContainsKey( styleName ) )
      {
        NivalCLI.CLI.Warning( "Invalid style name:'{0}'. Default style applied.", styleName );
        return new Style( tmp );
      }

      Style result = new Style( _predefinedStyles[styleName] );

      //эти параметры не задаются стилем и их надо выставлять в зависимотси от стиля baseStyle
      result.Align = tmp.Align;
      result.LetterSpacing = tmp.LetterSpacing;
      result.WordSpacing = tmp.WordSpacing;
      result.LineSpacing = tmp.LineSpacing;
      result.TabSpacing = tmp.TabSpacing;
      result.Paragraph = tmp.Paragraph;

      return result;
    }

    private Texture2D GetPredefinedImage( string imageName )
    {
      if ( !_predefinedImages.ContainsKey( imageName ) )
      {
        NivalCLI.CLI.Warning( "Invalid image name:'{0}'.", imageName );
        return null;
      }

      return _predefinedImages[imageName];
    }
  }
}
