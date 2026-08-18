using System;
using System.Collections.Generic;
using UnityEngine;
using Object = UnityEngine.Object;

namespace Flash.Utils.Atlasses
{
  public sealed class AtlasData : IDisposable
  {
    private bool _disposed = false;

    public Texture2D Atlas { get; private set; }
    public Dictionary<int, Rect> Rects { get; private set; }
    public Dictionary<int, Vector2> Sizes { get; private set; }

    public AtlasData( Texture2D atlas, Dictionary<int, Rect> rects, Dictionary<int, Vector2> sizes )
    {
      Atlas = atlas;
      Rects = rects;
      Sizes = sizes;
    }

    public void Dispose()
    {
      if ( !_disposed )
      {
        if ( !Application.isEditor )
          Object.Destroy( Atlas );

        Atlas = null;
        Rects = null;
        Sizes = null;

        _disposed = true;
      }
    }
  }
}
