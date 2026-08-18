using System;
using System.Runtime.Serialization;
using UnityEngine;

namespace Flash
{
  [Serializable]
  internal sealed class LayoutSolver : ISerializable
  {
    private int nextX = FontStorage.GLYPH_MARGIN;
    private int nextY = FontStorage.GLYPH_MARGIN;
    private int maxY = 0;

    public LayoutSolver()
    {
    }

    private LayoutSolver( SerializationInfo info, StreamingContext context )
    {
      SerializeHelpers.Unpack( info, "nextX", out nextX );
      SerializeHelpers.Unpack( info, "nextY", out nextY );
      SerializeHelpers.Unpack( info, "maxY", out maxY );
      SerializeHelpers.Unpack( info, "_closed", out _closed );
    }

    void ISerializable.GetObjectData( SerializationInfo info,
      StreamingContext context )
    {
      SerializeHelpers.Pack( info, "nextX", nextX );
      SerializeHelpers.Pack( info, "nextY", nextY );
      SerializeHelpers.Pack( info, "maxY", maxY );
      SerializeHelpers.Pack( info, "_closed", _closed );
    }

    private bool _closed = false;
    public bool Closed
    {
      get { return _closed; }
    }

    public void Clear()
    {
      nextX = FontStorage.GLYPH_MARGIN;
      nextY = FontStorage.GLYPH_MARGIN;
      maxY = 0;
      _closed = false;
    }

    public bool TryPutChar( Texture2D buffer, ref int xOut, ref int yOut, Metrics metric )
    {
      if ( nextX + buffer.width + FontStorage.GLYPH_MARGIN > FontStorage.DEFAULT_TEX_SIZE )
      {
        if ( nextY + maxY + FontStorage.GLYPH_MARGIN > FontStorage.DEFAULT_TEX_SIZE )
        {
          _closed = true;
          return false;
        }

        nextY += maxY;
        nextX = FontStorage.GLYPH_MARGIN;
        maxY = 0;
      }

      if ( nextX + buffer.width > FontStorage.DEFAULT_TEX_SIZE || nextY + buffer.height > FontStorage.DEFAULT_TEX_SIZE )
      {
        _closed = true;
        return false;
      }

      xOut = nextX;
      yOut = nextY;

      maxY = Math.Max( maxY, buffer.height + FontStorage.GLYPH_MARGIN );
      nextX += ( buffer.width + FontStorage.GLYPH_MARGIN );

      return true;
    }
  }
}


