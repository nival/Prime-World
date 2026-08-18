using UnityEngine;

namespace Flash.Utils.Atlasses
{
  public class AtlassedTexture
  {
    public string ResourcesPath { get; private set; }
    public Rect Rect { get; private set; }
    public Vector2 Size { get; private set; }
    public Texture2D ParentAtlas { get; private set; }
    //public Texture2D ParentAtlas { get; private set; }

    public AtlassedTexture( string path, Rect rect, Vector2 size, Texture2D atlas )
    {
      ResourcesPath = path;
      Rect = rect;
      Size = size;
      ParentAtlas = atlas;
    }
  }
}