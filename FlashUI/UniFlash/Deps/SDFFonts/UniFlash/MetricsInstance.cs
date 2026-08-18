using Flash;
using UnityEngine;

namespace SDFFonts.UniFlash
{
  public class MetricsInstance : IFontMetrics
  {
    private readonly char _char;
    private readonly Texture2D _atlas;
    private readonly Vector2 _uvMin;
    private readonly Vector2 _uvMax;
    private readonly float _scale;
    private readonly MetricsExt _ext;

    public MetricsInstance(MetricsInstance other, int kerning)
    {
      _char = other._char;
      _atlas = other._atlas;
      _uvMin = other._uvMin;
      _uvMax = other._uvMax;
      _scale = other._scale;
      _ext = other._ext;
      _ext.Kerning = (float)kerning * _scale;
    }

    public MetricsInstance(Glyph glyph, float scale)
    {
      _char = glyph.Char;
      _atlas = glyph.Atlas;
      _uvMin = glyph.UvMin;
      _uvMax = glyph.UvMax;
      _scale = scale;
      _ext.FontSize = (float)glyph.FontSize * scale;
      _ext.Size = new Vector2((float)glyph.Width * _scale, (float)glyph.Height * _scale);
      _ext.Offset = new Vector2((float)glyph.XOffset * _scale, (float)glyph.YOffset * _scale);
      _ext.Advance = new Vector2((float)glyph.XAdvance * _scale, (float)glyph.YAdvance * _scale);
      _ext.LineHeight = (float)glyph.LineHeight * _scale;
      _ext.BaseLine = (float)glyph.BaseLine * _scale;
    }

    public MetricsInstance(Texture2D atlas, Vector2 uvMin, Vector2 uvMax, Vector2 size, Vector2 offset, Vector2 advance)
    {
      _char = '\0';
      _atlas = atlas;
      _scale = 1f;
      _uvMin = uvMin;
      _uvMax = uvMax;
      _ext.Size = size;
      _ext.Offset = offset;
      _ext.Advance = advance;
    }

    public MetricsInstance(Texture2D atlas, Vector2 uvMin, Vector2 uvMax, MetricsExt ext)
    {
      _char = '\u0080';
      _atlas = atlas;
      _scale = 1f;
      _uvMin = uvMin;
      _uvMax = uvMax;
      _ext = ext;
    }

    public override string ToString()
    {
      if (_char != '\0')
        return string.Format("MetricInstance for '{0}' x{1} scale", _char, _scale);
      else
        return string.Format("MetricInstance for icon x{0} scale", _scale);
    }

#region IFontMetrics

    public Texture2D Tex { get { return _atlas; } }
    public Vector2 UvMin { get { return _uvMin; } }
    public Vector2 UvMax { get { return _uvMax; } }

    public MetricsExt Ext { get { return _ext; } }
    public float FWidth { get { return _ext.Advance.x; } }

    // Obsolete
    public int Kern { get { return 0; } }
    public int Floor { get { return 0; } }
    public int Height { get { return 0; } }
    public int Width { get { return 0; } }

#endregion
  }
}