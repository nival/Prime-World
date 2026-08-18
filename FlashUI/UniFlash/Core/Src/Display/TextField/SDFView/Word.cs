using System.Collections.Generic;

namespace Flash.SDFView
{
  internal struct Word
  {
    public bool Empty;

    public int Length;
    public CharType Type;
    public float Width;
    public float Height;
    public float BaseLine;
    public List<Char> Chars;
    public float VerticalAdvance;

    public void CopyMetricsFrom(ref Word other)
    {
      Type = other.Type;
      Height = other.Height;
      BaseLine = other.BaseLine;
      VerticalAdvance = other.VerticalAdvance;
    }
  }
}