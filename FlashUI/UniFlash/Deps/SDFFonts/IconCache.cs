using System;
using System.Collections.Generic;
using UnityEngine;

namespace SDFFonts
{
  public class IconCache
  {
    public const int TexWidth = 1024;
    public const int TexHeight = 1024;
    public const TextureFormat TexFormat = TextureFormat.ARGB32;
    public const int MarginX = 2;
    public const int MarginY = 2;

    private Texture2D _tex;
    private readonly Dictionary<Texture2D, Vector4> _uvs = new Dictionary<Texture2D, Vector4>(64);
    private int _storeX;
    private int _storeY;
    private int _rowY;

    public Texture2D Tex { get { return _tex; } }

    public IconCache()
    {
      InitTexture();
      ClearTexture();
    }

    public bool GetIcon(Texture2D icon, ref Vector2 uvMin, ref Vector2 uvMax)
    {
      if (icon == false)
        return false;

      Vector4 uvs;
      if (!_uvs.TryGetValue(icon, out uvs))
      {
        uvs = StoreIcon(icon);
        _uvs[icon] = uvs;
      }

      uvMin = new Vector2(uvs.x, uvs.w);
      uvMax = new Vector2(uvs.z, uvs.y);
      return true;
    }

    private void InitTexture()
    {
      _tex = new Texture2D(TexWidth, TexHeight, TexFormat, false);
      _tex.name = "IconTexture";
      _tex.filterMode = FilterMode.Bilinear;
      _tex.wrapMode = TextureWrapMode.Clamp;
    }

    private void ClearTexture()
    {
      Color[] pixels = _tex.GetPixels();
      for (int i = 0; i < pixels.Length; i++)
      {
        pixels[i] = new Color(0, 0, 0, 0);
      }
      _tex.SetPixels(pixels);
      _tex.Apply();

      _storeX = MarginX;
      _storeY = MarginY;
    }

    private Vector4 StoreIcon(Texture2D icon)
    {
      if (icon.width + MarginX + MarginX >= TexWidth)
      {
        Debug.LogError("Text icon is too big!!");
        return default(Vector4);
      }

      if (_storeX + icon.width + MarginX >= TexWidth)
      {
        _storeX = MarginX;
        _storeY = _storeY + _rowY;
      }

      if (_storeY + icon.height + MarginY >= TexHeight)
      {
        Debug.LogError("Atlas for text icons is full!!!");
        return default(Vector4);
      }

      Color[] colors = icon.GetPixels();
      _tex.SetPixels(_storeX, _storeY, icon.width, icon.height, colors);
      _tex.Apply();

      Vector4 result = new Vector4 {
        x = (float)_storeX / (float)TexWidth,
        y = (float)_storeY / (float)TexHeight,
        z = (float)(_storeX + icon.width) / (float)TexWidth,
        w = (float)(_storeY + icon.height) / (float)TexHeight,
      };

      _storeX += icon.width + MarginX;
      _rowY = Math.Max(_rowY, icon.height + MarginY);

      return result;
    }
  }
}
