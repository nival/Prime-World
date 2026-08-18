using UnityEngine;

namespace Flash
{
  internal class View_TextField_Context
  {
    public const int EXTENT = 1;

    // Style
    public Color Color { get; set; }
    public Color GlowColor { get; set; }
    public int FontSize { get; set; }
    public int BaseLine { get; set; }
    public UnityEngine.TextAlignment Align { get; set; }
    public bool Atom { get; set; }
    public int LetterSpacing { get; set; }
    public int WordSpacing { get; set; }
    public int LineSpacing { get; set; }
    public int TabSpacing { get; set; }
    public int Paragraph { get; set; }

    public int X { get; set; }
    public int Y { get; set; }
    private int _lineLineSpacing;

    public int LineLineSpacing
    {
      get { return _lineLineSpacing; }
      set
      {
        _prevLineSpacing = _lineLineSpacing;
        _lineLineSpacing = value;
      }
    }

    private int _lineBaseLine;

    public int LineBaseLine
    {
      get { return _lineBaseLine; }
      set
      {
        _prevBaseLine = _lineBaseLine;
        _lineBaseLine = value;
      }
    }

    private int _prevLineSpacing;

    public int PrevLineSpacing
    {
      get { return _prevLineSpacing; }
    }

    private int _prevBaseLine;

    public int PrevBaseLine
    {
      get { return _prevBaseLine; }
    }

    private Style _currentStyle;

    public Style CurrentStyle
    {
      get { return _currentStyle; }
      set { _currentStyle = value; }
    }

    private bool _newWord = true;

    public bool NewWord
    {
      get { return _newWord; }
      set { _newWord = value; }
    }

    public int TriangleOffset { get; set; }
    private int _extent = EXTENT;

    public int Extent
    {
      get { return _extent; }
      set { _extent = value; }
    }

    public void SetContext(Style style)
    {
      Color = style.Color;
      GlowColor = style.GlowColor;
      FontSize = style.FontSize;
      BaseLine = style.BaseLine;
      Align = style.Align;
      Atom = style.Atom;
      LetterSpacing = (int) (FontSize*style.LetterSpacing/100.0F);
      if (LetterSpacing == 0)
        LetterSpacing = 1;
      WordSpacing = (int) (FontSize*style.WordSpacing/100.0F);
      if (WordSpacing == 0)
        WordSpacing = 1;
      LineSpacing = (int) (FontSize*style.LineSpacing/100.0F);
      TabSpacing = (int) (FontSize*style.TabSpacing/100.0F);
      if (TabSpacing == 0)
        TabSpacing = 1;
      Paragraph = (int) (FontSize*style.Paragraph/100.0F);
    }

    public void Clear()
    {
      X = 0;
      Y = 0;
      _lineLineSpacing = 0;
      _lineBaseLine = 0;
      _prevLineSpacing = 0;
      _prevBaseLine = 0;
      _currentStyle = null;
      _newWord = true;
      TriangleOffset = 0;
      _extent = EXTENT;
    }
  }
}