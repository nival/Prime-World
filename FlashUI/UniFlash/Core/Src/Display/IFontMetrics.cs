using UnityEngine;

namespace Flash
{
  public interface IFontMetrics
  {
    int Width { get; }
    int Height { get; }
    int Floor { get; }
    int Kern { get; }

    float FWidth { get; }

    Texture2D Tex { get; }
    Vector2 UvMin { get; }
    Vector2 UvMax { get; }

    MetricsExt Ext { get; }
  }
}