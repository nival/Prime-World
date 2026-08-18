using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Resources = ResourcesManager.Resources;

namespace Flash
{
  public class FormatedText : IEnumerable<FormatEntry>
  {
    private readonly List<FormatEntry> _formatedData = new List<FormatEntry>();
    public FormatEntry this[int i]
    {
      get { return _formatedData[i]; }
      set
      {
        _formatedData[i] = value;
      }
    }
    public int Count { get { return _formatedData.Count; } }

    public FormatedText() { }

    public FormatedText( IEnumerable<FormatEntry> collection )
    {
      foreach ( FormatEntry entry in collection )
      {
        _formatedData.Add( entry );
      }
    }
    public void Add( Style style, object data )
    {
      if ( data is Texture2D )
      {
        ( (Style)style ).FontSize = ( (Texture2D)data ).height;
      }
      _formatedData.Add( new FormatEntry( style, data ) );
    }
    public IEnumerator<FormatEntry> GetEnumerator()
    {
      foreach ( FormatEntry formatEntry in _formatedData )
      {
        yield return formatEntry;
      }
    }
    IEnumerator IEnumerable.GetEnumerator()
    {
      return GetEnumerator();
    }
    public override string ToString()
    {
      string result = "";
      foreach ( FormatEntry entry in _formatedData )
      {
        result += entry.ToString();
        result += "\n----------------------------\n";
      }
      return result;
    }
  }

  public sealed class FormatEntry
  {
    private readonly Style _style;
    public Style Style
    {
      get { return _style; }
    }
    private readonly object _data;
    public object Data
    {
      get { return _data; }
    }

    public FormatEntry( Style style, object data )
    {
      _style = style;
      _data = data;
    }
    public override string ToString()
    {
      string result = "";
      result += _style.ToString();
      result += "\n";
      if ( _data is Texture2D )
        result += _data.ToString();
      else
      {
        string str = (string)_data;
        foreach ( char c in str )
        {
          if ( c == '\n' )
            result += "{SLESH_N}";
          else
          {
            result += c;
          }
        }
      }
      return result;
    }
  }

  public class Style
  {
    private const bool TAKE_FONT_FROM_STYLE = true;

    public static Style GenerateDefaultStyle()
    {
      return new Style( FontStorage.DefaultFont, 14, FontStyle.Normal,
      new Color( 221f / 255f, 221f / 255f, 221f / 255f ),
      Color.clear, UnityEngine.TextAlignment.Left, false, 0, 45, 120, 300, 0 );
    }

    private Font _font;
    public Font Font
    {
      get { return _font; }
      set
      {
        _font = value;

        if ( TAKE_FONT_FROM_STYLE )
        {
          RedefineFont();
        }
      }
    }
    private int _fontSize;
    public int FontSize
    {
      get { return _fontSize; }
      set
      {
        _fontSize = value;
        UpdateRatioValues();
      }
    }
    private int _baseLine; // from font storage
    public int BaseLine
    {
      get { return _baseLine; }
    }
    private FontStyle _fontStyle;
    public FontStyle FontStyle
    {
      get { return _fontStyle; }
      set
      {
        _fontStyle = value;

        if ( TAKE_FONT_FROM_STYLE )
        {
          RedefineFont();
        }
      }
    }
    /// <summary>
    /// Using for images scale to actual font size.
    /// False - image size is adapted to font size
    /// True - image size is constant
    /// </summary>
    public bool DisableImageScaling { get; set; }

    public float LetterSpacingValue { get; private set; }
    public float WordSpacingValue { get; private set; }
    public float TabSpacingValue { get; private set; }
    public float LineSpacingValue { get; private set; }
    public float LineIndentValue { get; private set; }

    private Color _color;
    public Color Color
    {
      get { return _color; }
      set { _color = value; }
    }
    private Color _glowColor;
    public Color GlowColor
    {
      get { return _glowColor; }
      set { _glowColor = value; }
    }
    private UnityEngine.TextAlignment _align;
    public UnityEngine.TextAlignment Align
    {
      get { return _align; }
      set { _align = value; }
    }
    private bool _atom;
    public bool Atom
    {
      get { return _atom; }
      set { _atom = value; }
    }
    private int _letterSpacing; // % _fontSize
    public int LetterSpacing
    {
      get { return _letterSpacing; }
      set {
        _letterSpacing = value;
#if !SDFFONT
        LetterSpacingValue = (float)(_letterSpacing * _fontSize) / 100f;
#endif
      }
    }
    private int _wordSpacing; // % _fontSize
    public int WordSpacing
    {
      get { return _wordSpacing; }
      set {
        _wordSpacing = value;
        WordSpacingValue = (float)(_wordSpacing * _fontSize) / 100f;
      }
    }
    private int _lineSpacing; // % _fontSize
    public int LineSpacing
    {
      get { return _lineSpacing; }
      set {
        _lineSpacing = value;
        LineSpacingValue = (float)(_lineSpacing * _fontSize) / 100f;
      }
    }
    private int _tabSpacing; // % _fontSize
    public int TabSpacing
    {
      get { return _tabSpacing; }
      set {
        _tabSpacing = value;
        TabSpacingValue = (float)(_tabSpacing * _fontSize) / 100f;
      }
    }
    private int _paragraph; // % _fontSize
    public int Paragraph
    {
      get { return _paragraph; }
      set {
        _paragraph = value;
        LineIndentValue = (float)(_paragraph * _fontSize) / 100f;
      }
    }

    public Style( 
      Font font,
      int fontSize, 
      FontStyle fontStyle, 
      Color color, 
      Color glowColor, 
      UnityEngine.TextAlignment align,
      bool atom, 
      int letterSpacing, 
      int wordSpacing, 
      int lineSpacing, 
      int tabSpacing, 
      int paragraph )
    {
      _font = font;
      _fontSize = fontSize;
      _fontStyle = fontStyle;
      _color = color;
      _glowColor = glowColor;
      _align = align;
      _atom = atom;
      _letterSpacing = letterSpacing;
      _wordSpacing = wordSpacing;
      _lineSpacing = lineSpacing;
      _tabSpacing = tabSpacing;
      _paragraph = paragraph;

      if ( TAKE_FONT_FROM_STYLE )
        RedefineFont();

      UpdateRatioValues();
    }
    public Style( Style textStyle )
      : this( textStyle.Font, textStyle.FontSize, textStyle.FontStyle, textStyle.Color, textStyle.GlowColor,
                textStyle.Align, textStyle.Atom, textStyle.LetterSpacing, textStyle.WordSpacing,
                textStyle.LineSpacing, textStyle.TabSpacing, textStyle.Paragraph )
    {
    }

    public void SetBaseLine( int baseLine )
    {
      _baseLine = baseLine;
    }
    public override string ToString()
    {
      return string.Format( "FontSize - {0}, FontStyle - {1}, Align - {2}, Atom - {3}, LineSpacing - {4} , LetterSpacing - {5}",
       this.FontSize, this.FontStyle, this.Align, this.Atom, this.LineSpacing, this.LetterSpacing ) + " <<<<<<<";
    }

    private void RedefineFont()
    {
      string fontName = _font.name;
      switch ( _fontStyle )
      {
      case FontStyle.Normal:
        break;
      case FontStyle.Bold:
        fontName += " Bold";
        break;
      case FontStyle.Italic:
        fontName += " Italic";
        break;
      case FontStyle.BoldAndItalic:
        fontName += " Bold Italic";
        break;
      }

      Font font = Resources.Load( FlashEnv.FONTS_PATH + fontName ) as Font;

      if ( font == null )
      {
        Debug.LogWarning( "WARNING! Font " + fontName + " not found in FormatEntry Style." );
      }
      else
      {
        _font = font;
      }
    }

    private void UpdateRatioValues()
    {
#if SDFFONT
      LetterSpacingValue = SDFFonts.FontManager.OverrideLetterSpacing * (float)_fontSize;
#else
      LetterSpacingValue = (float)(_letterSpacing * _fontSize) / 100f;
#endif
      WordSpacingValue = (float)(_wordSpacing * _fontSize) / 100f;
      LineSpacingValue = (float)(_lineSpacing * _fontSize) / 100f;
      TabSpacingValue = (float)(_tabSpacing * _fontSize) / 100f;
      LineIndentValue = (float)(_paragraph * _fontSize) / 100f;
    }
  }
}