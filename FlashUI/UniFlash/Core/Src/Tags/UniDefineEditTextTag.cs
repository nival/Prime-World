using System.Globalization;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using Flash.Utils;
using SwfDotNet.IO.Tags;
using UnityEngine;


namespace Flash
{
  [System.Serializable]
  public class UniDefineEditTextTag : UniBaseTag, ISerializable
  {
    //Error on parsing. Everytime 2 pixels offset for x. PF-59107
    //Watching inside swfdotnet is required
    public const int SWFDOTNET_PX_OFFSET = 2;
    private string _text;
    public string Text
    {
      get { return _text; }
    }
    private bool _multiLine;
    public bool MultiLine
    {
      get { return _multiLine; }
    }
    private Color _textColor;
    public Color TextColor
    {
      get { return _textColor; }
    }
    private int _fontId;
    public int FontId
    {
      get { return _fontId; }
    }
    private int _fontSize;
    public int FontSize
    {
      get { return _fontSize; }
    }
    private float _lineSpacing = 1;
    public float LineSpacing
    {
      get { return _lineSpacing; }
    }
    private int _letterSpacing;
    public int LetterSpacing
    {
      get { return _letterSpacing; }
    }
    private bool _readOnly = true;
    public bool ReadOnly
    {
      get { return _readOnly; }
      set { _readOnly = value; }
    }
    private TextAlignment _align;
    public TextAlignment Align
    {
      get { return _align; }
    }
    private int _maxLenght = 0;
    public int MaxLenght
    {
      get { return _maxLenght; }
    }

    public override void GetObjectData( SerializationInfo info, StreamingContext context )
    {
      base.GetObjectData( info, context );

      Flash.SerializeHelpers.Pack( info, "_text", _text );
      Flash.SerializeHelpers.Pack( info, "_multiLine", _multiLine );
      Flash.SerializeHelpers.Pack( info, "_textColor", _textColor );
      Flash.SerializeHelpers.Pack( info, "_fontId", _fontId );
      Flash.SerializeHelpers.Pack( info, "_fontSize", _fontSize );
      Flash.SerializeHelpers.Pack( info, "_lineSpacing", _lineSpacing );
      Flash.SerializeHelpers.Pack( info, "_letterSpacing", _letterSpacing );
      Flash.SerializeHelpers.Pack( info, "_readOnly", _readOnly );
      Flash.SerializeHelpers.Pack( info, "_align", _align );
      Flash.SerializeHelpers.Pack( info, "_maxLenght", _maxLenght );
    }

    public UniDefineEditTextTag( SerializationInfo info, StreamingContext context )
      : base( info, context )
    {
      Flash.SerializeHelpers.Unpack( info, "_text", out _text );
      Flash.SerializeHelpers.Unpack( info, "_multiLine", out _multiLine );
      Flash.SerializeHelpers.Unpack( info, "_textColor", out _textColor );
      Flash.SerializeHelpers.Unpack( info, "_fontId", out _fontId );
      Flash.SerializeHelpers.Unpack( info, "_fontSize", out _fontSize );
      Flash.SerializeHelpers.Unpack( info, "_lineSpacing", out _lineSpacing );
      Flash.SerializeHelpers.Unpack( info, "_letterSpacing", out _letterSpacing );
      Flash.SerializeHelpers.Unpack( info, "_readOnly", out _readOnly );
      Flash.SerializeHelpers.Unpack( info, "_align", out _align );
      Flash.SerializeHelpers.Unpack( info, "_maxLenght", out _maxLenght );
    }

    public UniDefineEditTextTag( BaseTag baseTag, UniSwf owner )
      : base( owner )
    {
      DefineEditTextTag editTextTag = baseTag as DefineEditTextTag;
      _text = editTextTag.InitialText;
      _multiLine = editTextTag.Multiline;

      _readOnly = editTextTag.ReadOnly;
      _fontId = editTextTag.FontId;
      _maxLenght = editTextTag.MaxLenght;

      if ( editTextTag.FontHeight > 0 )
        _fontSize = (int)( editTextTag.FontHeight * FlashToUnityConverter.TWIPS_TO_PIXELS );

      if ( editTextTag.HasLayout )
        _lineSpacing += editTextTag.Leading * FlashToUnityConverter.TWIPS_TO_PIXELS / _fontSize;

      _localBounds.LeftTop = FlashToUnityConverter.ConvertPosition( editTextTag.Rect.XMin, editTextTag.Rect.YMin );
      _localBounds.RightBottom = FlashToUnityConverter.ConvertPosition( editTextTag.Rect.XMax, editTextTag.Rect.YMax );

      if ( editTextTag.Html )
        ParseHtml();

      _textColor = FlashToUnityConverter.ConvertColor( editTextTag.TextColor );

      switch ( editTextTag.Align )
      {
      case 0:
        _align = TextAlignment.TopLeft;
        break;
      case 1:
        _align = TextAlignment.TopRight;
        break;
      case 2:
        _align = TextAlignment.TopCenter;
        break;
      case 3:
        _align = TextAlignment.Justify;
        break;
      default:
        break;
      }
    }

    private void ParseHtml()
    {
      Match result = Regex.Match( _text, @"letterSpacing\s*=\s*""?(?<dig>-?[\d.]+)""?" );

      if ( result.Success )
      {
        string digit = result.Groups["dig"].Value;
        _letterSpacing = Mathf.RoundToInt( float.Parse( digit, CultureInfo.InvariantCulture ) );
      }

      _text = Regex.Replace( _text, "<br>", "\n" );
      _text = Regex.Replace( _text, @"</p>", "\n" );
      _text = Regex.Replace( _text, @"<[^>]*>", string.Empty );
      _text = _text.TrimEnd( '\n', '\r' );
    }
  }
}
