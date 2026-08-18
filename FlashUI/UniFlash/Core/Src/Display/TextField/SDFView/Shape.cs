using UnityEngine;

namespace Flash.SDFView
{
  internal class Shape
  {
    public bool IsIcon;
    public Texture2D Texture;
    public int Item;
    public int ItemsCount;
    public Vector3[] Vertices;
    public Vector2[] UVs;
    public Color[] Colors;
    public Vector4[] Tangents;
    public int[] Triangles;
  }
}