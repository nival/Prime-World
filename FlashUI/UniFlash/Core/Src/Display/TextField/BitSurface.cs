using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace Flash
{
  public sealed class BitSurface : IEnumerable<bool>
  {
    private readonly BitArray _surface;
    private readonly int _width;
    public int Width
    {
      get { return _width; }
    }
    private readonly int _height;
    public int Height
    {
      get { return _height; }
    }

    public BitSurface( int width, int height )
    {
      _width = width;
      _height = height;
      _surface = new BitArray( width * height, true ); // all free
    }
    public bool this[int i, int j]
    {
      get
      {
        return _surface.Get( i + j * _width );
      }
      set
      {
        _surface.Set( i + j * _width, value );
      }
    }
    public bool GetSafe( int i, int j )
    {
      if ( i < 0 || i > _width - 1 || j < 0 || j > _height - 1 )
        return true;

      return this[i, j];
    }
    public void SetSafe( int i, int j, bool val )
    {
      if ( i < 0 || i > _width - 1 || j < 0 || j > _height - 1 )
        return;

      this[i, j] = val;
    }
    public void FillArea( int i, int j, int width, int height, bool val )
    {
      for ( int y = j; y < ( j + height ); ++y )
      {
        for ( int x = i; x < ( i + width ); ++x )
        {
          this[x, y] = val;
        }
      }
    }
    public void FillAreaSafe( int i, int j, int width, int height, bool val )
    {
      int iw = i + width;
      int jh = j + height;

      for ( int y = j; y < jh; ++y )
      {
        for ( int x = i; x < iw; ++x )
        {
          if ( x < 0 || x > _width - 1 || y < 0 || y > _height - 1 )
            continue;
          this[x, y] = val;
        }
      }
    }
    public IEnumerator<bool> GetEnumerator()
    {
      return _surface.Cast<bool>().GetEnumerator();
    }
    IEnumerator IEnumerable.GetEnumerator()
    {
      return GetEnumerator();
    }
  }
}


