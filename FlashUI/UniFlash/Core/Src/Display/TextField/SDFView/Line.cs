using System.Collections.Generic;

namespace Flash.SDFView
{
  internal struct Line
  {
    public bool Empty;
    public int Length;
    public List<Word> Words;
    public int Spaces;

    public Flash.TextAlignment Alignment;
    public bool FirstLine;
    public bool CanBeJustified;
    public bool Additional;

    public float Y;
    public float Width;
    public float Height;
    public float BaseLine;
    public float FirstLineIndent;
    public float VerticalAdvance;
  }
}