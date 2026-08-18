namespace Flash.SDFView
{
  internal struct Char
  {
    public int Index;
    public int FragmentIndex;
    public char Ch;
    public int LineIndex;
    public int LinePosition;
    public CharType Type;
    public float X;
    public float Y;
    public float Width;
    public float FinalWidth;
    public IFontMetrics Metric;
    public Style Style;
  }
}